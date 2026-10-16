# ReleaseGuard — Michael Morris — Sprint 1 Backlog Contribution

**Team:** 10  
**Sprint window:** September 15–October 12, 2026  
**Contribution submitted:** October 14–15, after the planned sprint end  
**Merged PR:** https://github.com/Folie-et-Triste/ReleaseGuard/pull/9

| ID | GitHub issue | User story | Priority | Estimate (board units) | Evidence/status |
|---|---|---|---|---|---|
| RG-AUTH-01 | [#10 Registration](https://github.com/Folie-et-Triste/ReleaseGuard/issues/10) | As a new user, I want to register with a username and password so I can access ReleaseGuard. | High | 2 | Standalone prototype locally tested; PR merged; board last observed Code Review |
| RG-AUTH-02 | [#3 Login](https://github.com/Folie-et-Triste/ReleaseGuard/issues/3) | As a registered user, I want to sign in with valid credentials so I can use ReleaseGuard. | High | 2 | Standalone prototype locally tested; PR merged; board last observed Code Review |

*Estimates are the values visible on the board; confirm whether your team uses hours or story points.*

## Registration acceptance criteria and evidence
- [x] Accept a valid username and a password containing at least 8 characters.
- [x] Reject duplicate usernames and invalid input.
- [x] Store password-derived hashes with per-account salts rather than plaintext passwords.
- [x] Reload account data across program runs.
- [x] Pass automated tests and demonstrate successful registration and rejection cases in Ubuntu.
- [ ] Team acceptance/integration review completed (confirm separately; standalone prototype only).

## Login acceptance criteria and evidence
- [x] Accept valid credentials.
- [x] Reject incorrect passwords and unknown usernames.
- [x] Authenticate an account after reloading saved data.
- [x] Pass automated tests and demonstrate positive and negative cases in Ubuntu.
- [ ] Team acceptance/integration review completed (confirm separately; standalone prototype only).

## Scope and timing
The feature files are standalone at the repository root and do not alter the existing `ReleaseGuard/main.cpp`, `user.h`, or `wrapper.h`. Local tests passed; integration into the main executable is future work. PR #9 was merged on October 15, after the October 12 Sprint 1 end date. The team should record this accurately when deciding what counts toward its Sprint 1 completion target.
