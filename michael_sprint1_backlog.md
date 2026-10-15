# ReleaseGuard — Michael Morris: Sprint 1 Backlog Contributions

**Sprint 1:** September 15–October 12, 2026  
**Contributor:** Michael Morris  
**Pull request:** https://github.com/Folie-et-Triste/ReleaseGuard/pull/9  
**Scope:** Standalone authentication addition; no modifications to existing team code.

> **Timing note:** The pull request was opened October 14 (US Pacific), after the Sprint 1 end date. Ask the team/instructor how to classify the late contribution in the official Sprint 1 report. Do not claim this code was merged or completed by October 12.

| ID | User story | Priority | Proposed effort | GitHub tracking |
| --- | --- | --- | --- | --- |
| RG-AUTH-01 | As a new member, I want to register an account so I can access ReleaseGuard. | High | 2–3 hours (planning estimate; not actual time) | Create new issue; link PR #9 |
| RG-AUTH-02 | As a registered member, I want to log in with my credentials so I can access the system. | High | 1–2 hours (planning estimate; not actual time) | Existing issue #3: https://github.com/Folie-et-Triste/ReleaseGuard/issues/3; link PR #9 |

## RG-AUTH-01 — Registration acceptance criteria
- [ ] User can create an account with a unique, valid username and password of at least 8 characters.
- [ ] Invalid or duplicate usernames are rejected.
- [ ] Passwords are stored as salted hashes rather than plaintext.
- [ ] Accounts persist and can be reloaded.
- [ ] Local screenshot/test evidence is collected and a teammate reviews the PR.

## RG-AUTH-02 — Login acceptance criteria
- [ ] Correct credentials succeed.
- [ ] Incorrect password and unknown username fail.
- [ ] Login still works after loading previously saved accounts.
- [ ] Local screenshot/test evidence is collected and a teammate reviews the PR.

## Current implementation / evidence
The feature code is proposed in PR #9 as an **independent demonstration**, not integrated into the team's existing `main.cpp` or `wrapper.h`. An automated test run in the preparation environment returned:

```text
PASS: registration, duplicate checks, validation, login, persistence, password hashing
```

Michael has **not yet confirmed running the tests on his own computer**, and the PR has not been verified as merged. GitHub board status and Sprint 1 completion status should be verified with the team before marking these items Done.
