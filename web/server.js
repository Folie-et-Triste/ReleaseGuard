// ReleaseGuard web server. Zero external dependencies: Node built-ins only.
// Serves the single-page front end and a JSON API, with file-backed storage.
const http = require("http");
const fs = require("fs");
const path = require("path");
const crypto = require("crypto");

const PORT = process.env.PORT || 3000;
const DATA_FILE = process.env.DATA_FILE || path.join(__dirname, "data.json");
const PUBLIC_DIR = path.join(__dirname, "public");

// ---- Storage ----
function emptyData() { return { users: {}, releases: [], activity: [], seq: 0 }; }
function load() {
  try { return JSON.parse(fs.readFileSync(DATA_FILE, "utf8")); }
  catch (e) { return emptyData(); }
}
function save(d) { fs.writeFileSync(DATA_FILE, JSON.stringify(d, null, 2)); }
let db = load();
const nextId = () => ++db.seq;

// ---- Auth (PBKDF2, same idea as the C++ AuthService) ----
const tokens = new Map(); // token -> username (in memory; cleared on restart)
function hashPassword(password, salt) {
  return crypto.pbkdf2Sync(password, salt, 200000, 32, "sha256").toString("hex");
}
function makeToken(user) { const t = crypto.randomBytes(24).toString("hex"); tokens.set(t, user); return t; }
function userFromReq(req) {
  const h = req.headers["authorization"] || "";
  const t = h.startsWith("Bearer ") ? h.slice(7) : "";
  return tokens.get(t) || null;
}
function logActivity(user, action) {
  db.activity.unshift({ when: Date.now(), who: user, action });
  if (db.activity.length > 500) db.activity.pop();
}

// ---- Domain: readiness rule (mirrors release.h) ----
function blockers(r) {
  const out = [];
  r.bugs.forEach(b => { if (b.severity === "Critical" && !b.resolved) out.push({ kind: "Defect", text: "Unresolved critical bug: " + b.title }); });
  r.tests.forEach(t => { if (!t.passed) out.push({ kind: "Test", text: "Failing test: " + t.name }); });
  r.checklist.forEach(c => { if (!c.done) out.push({ kind: "Checklist", text: "Incomplete item: " + c.text }); });
  return out;
}
function stateOf(r) {
  if (r.decision && r.decision.type === "approved") return "done";
  if (r.decision && r.decision.type === "rejected") return "closed";
  return blockers(r).length === 0 ? "ok" : "hold";
}
function releaseView(r) {
  return { ...r, state: stateOf(r), blockers: blockers(r), openCount: blockers(r).length };
}

// ---- HTTP helpers ----
function sendJson(res, code, obj) {
  const body = JSON.stringify(obj);
  res.writeHead(code, { "Content-Type": "application/json; charset=utf-8" });
  res.end(body);
}
function readBody(req) {
  return new Promise((resolve) => {
    let data = ""; req.on("data", c => { data += c; if (data.length > 1e6) req.destroy(); });
    req.on("end", () => { try { resolve(data ? JSON.parse(data) : {}); } catch (e) { resolve({}); } });
  });
}
const MIME = { ".html": "text/html; charset=utf-8", ".css": "text/css", ".js": "text/javascript", ".svg": "image/svg+xml", ".ico": "image/x-icon" };
function serveStatic(req, res) {
  let rel = decodeURIComponent(req.url.split("?")[0]);
  if (rel === "/") rel = "/index.html";
  const file = path.join(PUBLIC_DIR, path.normalize(rel).replace(/^(\.\.[/\\])+/, ""));
  if (!file.startsWith(PUBLIC_DIR)) { res.writeHead(403); return res.end("Forbidden"); }
  fs.readFile(file, (err, buf) => {
    if (err) { res.writeHead(404); return res.end("Not found"); }
    res.writeHead(200, { "Content-Type": MIME[path.extname(file)] || "application/octet-stream" });
    res.end(buf);
  });
}

// ---- Routes ----
async function api(req, res, url) {
  const parts = url.split("/").filter(Boolean); // ["api", ...]
  const method = req.method;
  const seg = parts.slice(1); // after "api"

  // Auth endpoints
  if (seg[0] === "register" && method === "POST") {
    const { username, password } = await readBody(req);
    if (!username || !/^[A-Za-z0-9_-]{3,32}$/.test(username)) return sendJson(res, 400, { error: "Username must be 3-32 letters, digits, _ or -" });
    if (!password || password.length < 8) return sendJson(res, 400, { error: "Password must be at least 8 characters" });
    if (db.users[username]) return sendJson(res, 409, { error: "Username already exists" });
    const salt = crypto.randomBytes(16).toString("hex");
    db.users[username] = { salt, digest: hashPassword(password, salt) };
    logActivity(username, "registered"); save(db);
    return sendJson(res, 200, { token: makeToken(username), user: username });
  }
  if (seg[0] === "login" && method === "POST") {
    const { username, password } = await readBody(req);
    const u = db.users[username];
    if (!u || hashPassword(password || "", u.salt) !== u.digest) return sendJson(res, 401, { error: "Invalid username or password" });
    logActivity(username, "logged in"); save(db);
    return sendJson(res, 200, { token: makeToken(username), user: username });
  }

  // Everything below needs auth
  const user = userFromReq(req);
  if (!user) return sendJson(res, 401, { error: "Not signed in" });

  if (seg[0] === "activity" && method === "GET")
    return sendJson(res, 200, db.activity);

  if (seg[0] === "releases") {
    if (seg.length === 1 && method === "GET")
      return sendJson(res, 200, db.releases.map(releaseView));
    if (seg.length === 1 && method === "POST") {
      const { version, desc } = await readBody(req);
      if (!version) return sendJson(res, 400, { error: "Version is required" });
      const r = { id: nextId(), version, desc: desc || "No description", requestedBy: user, decision: null, bugs: [], tests: [], checklist: [] };
      db.releases.unshift(r); logActivity(user, "opened release " + version); save(db);
      return sendJson(res, 200, releaseView(r));
    }
    const r = db.releases.find(x => x.id === Number(seg[1]));
    if (!r) return sendJson(res, 404, { error: "Release not found" });

    if (seg.length === 2 && method === "GET") return sendJson(res, 200, releaseView(r));

    const body = await readBody(req);
    const sub = seg[2], id = Number(seg[3]), act = seg[4];
    if (sub === "bugs" && !id && method === "POST") {
      r.bugs.push({ id: nextId(), title: body.title || "Untitled", severity: body.severity || "Minor", assignee: body.assignee || "", resolved: false });
      logActivity(user, 'linked defect "' + (body.title || "") + '" to ' + r.version);
    } else if (sub === "tests" && !id && method === "POST") {
      r.tests.push({ id: nextId(), name: body.name || "test", passed: false });
      logActivity(user, "added test " + (body.name || "") + " to " + r.version);
    } else if (sub === "checklist" && !id && method === "POST") {
      r.checklist.push({ id: nextId(), text: body.text || "Item", done: false });
      logActivity(user, "added checklist item to " + r.version);
    } else if (sub === "bugs" && act === "resolve" && method === "POST") {
      const b = r.bugs.find(x => x.id === id); if (b) { b.resolved = true; logActivity(user, 'resolved defect "' + b.title + '" on ' + r.version); }
    } else if (sub === "tests" && act === "pass" && method === "POST") {
      const t = r.tests.find(x => x.id === id); if (t) { t.passed = true; logActivity(user, "passed test " + t.name + " on " + r.version); }
    } else if (sub === "checklist" && act === "complete" && method === "POST") {
      const c = r.checklist.find(x => x.id === id); if (c) { c.done = true; logActivity(user, 'completed "' + c.text + '" on ' + r.version); }
    } else if (sub === "approve" && method === "POST") {
      if (stateOf(r) !== "ok") return sendJson(res, 409, { error: "Release is not ready" });
      r.decision = { by: user, type: "approved", reason: "" }; logActivity(user, "approved release " + r.version);
    } else if (sub === "reject" && method === "POST") {
      r.decision = { by: user, type: "rejected", reason: body.reason || "" }; logActivity(user, "rejected release " + r.version);
    } else {
      return sendJson(res, 400, { error: "Unknown action" });
    }
    save(db);
    return sendJson(res, 200, releaseView(r));
  }
  return sendJson(res, 404, { error: "Unknown endpoint" });
}

const server = http.createServer((req, res) => {
  const url = req.url.split("?")[0];
  if (url.startsWith("/api/")) {
    api(req, res, url).catch(e => sendJson(res, 500, { error: "Server error" }));
  } else {
    serveStatic(req, res);
  }
});
server.listen(PORT, () => console.log("ReleaseGuard web server on http://localhost:" + PORT));
