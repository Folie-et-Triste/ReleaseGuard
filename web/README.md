# ReleaseGuard Web

A web version of ReleaseGuard. It tracks the defects, test results, and checklist items for a release and decides whether the release is ready to ship, with a graphical interface, real login, and persistent storage.

## What it does

- Register and log in. Passwords are stored as salted PBKDF2 hashes, not plain text.
- Create a release and manage it: add defects with a severity and assignee, record test results, and add checklist items.
- The server runs the readiness check. A release is Not Ready while any critical defect is unresolved, any test is failing, or any checklist item is incomplete, and it lists each blocker.
- Approve or reject a release. The server blocks approval until the release is ready, and a rejection records a reason.
- Data persists to a file, so it survives a restart and is shared between everyone using the server.
- An activity log records who did what and when.

## Technology

- Backend: Node.js with the built-in `http` and `crypto` modules. No external dependencies.
- Storage: a JSON file (`data.json`).
- Frontend: a single HTML page with vanilla JavaScript, styled after GitHub's Primer design.

## Run locally

Requires Node.js 18 or newer.

```
npm start
```

Then open http://localhost:3000. The server reads its port from the `PORT` environment variable and defaults to 3000.

## Run with Docker

```
docker build -t releaseguard-web .
docker run -p 3000:3000 releaseguard-web
```

Then open http://localhost:3000.

To keep data across container restarts, mount a volume for the data file:

```
docker run -p 3000:3000 -v $(pwd)/data:/app/data -e DATA_FILE=/app/data/data.json releaseguard-web
```

## API

All endpoints under `/api`. Endpoints other than register and login require an `Authorization: Bearer <token>` header, where the token comes from register or login.

| Method | Path | Purpose |
| --- | --- | --- |
| POST | /api/register | Create an account, returns a token |
| POST | /api/login | Log in, returns a token |
| GET | /api/releases | List releases with state and open-check count |
| POST | /api/releases | Create a release |
| GET | /api/releases/:id | One release with its items and readiness |
| POST | /api/releases/:id/bugs | Add a defect |
| POST | /api/releases/:id/tests | Add a test |
| POST | /api/releases/:id/checklist | Add a checklist item |
| POST | /api/releases/:id/bugs/:bid/resolve | Resolve a defect |
| POST | /api/releases/:id/tests/:tid/pass | Mark a test passing |
| POST | /api/releases/:id/checklist/:cid/complete | Complete a checklist item |
| POST | /api/releases/:id/approve | Approve (blocked unless ready) |
| POST | /api/releases/:id/reject | Reject with a reason |
| GET | /api/activity | Activity log |

## Files

- `server.js` runs the HTTP server, the API, and the storage.
- `public/index.html` is the whole front end.
- `package.json` defines the start script.
- `Dockerfile` builds the container image.

## Notes

- Session tokens are kept in memory, so everyone is signed out when the server restarts. The stored data (users, releases, activity) is not affected.
- The readiness rule matches the original C++ ReleaseGuard logic.
