# ReleaseGuard — Michael Morris — Sprint 1 Individual Report Contribution

> **For inclusion in the team's instructor-provided `sprint_report_template.md`.** This is not the final team report and does not claim team meetings took place.

## What's New (User Facing)
- Standalone User Registration: validates credentials, rejects duplicate usernames, and persists hashed password records.
- Standalone User Login: authenticates registered users and rejects invalid credentials.

## Work Summary (Developer Facing)
I developed a standalone C++ authentication component to add registration and login functionality without changing existing team source files. The implementation uses credential validation, salted password hashing, a saved account file, an interactive demonstration, and automated tests. I compiled and tested it in Ubuntu, including successful registration and login, invalid credentials, duplicate registration, and reloading account data. I submitted the changes through a fork because I initially lacked write access, and [Pull Request #9](https://github.com/Folie-et-Triste/ReleaseGuard/pull/9) was merged into the team's repository on October 15. The module has not yet been integrated with the main ReleaseGuard program.

## Completed Work / Issue Links
- [#10 — User Registration](https://github.com/Folie-et-Triste/ReleaseGuard/issues/10): standalone implementation and local tests completed.
- [#3 — Log In Feature](https://github.com/Folie-et-Triste/ReleaseGuard/issues/3): standalone implementation and local tests completed.
- [PR #9 — Authentication code, tests, and documentation](https://github.com/Folie-et-Triste/ReleaseGuard/pull/9): merged October 15.

**Sprint timing caveat:** The PR was opened and merged after the official October 12 sprint end. The team must confirm whether these changes count toward the Sprint 1 completed-feature target; the GitHub board most recently showed both issues in Code Review rather than Done.

## Unfinished Work and Blockers
- Integration of the standalone authentication component into the original `ReleaseGuard/main.cpp` and existing account code is still pending.
- Initially, I could not upload directly to the team's repository or edit the GitHub Project; I used a fork and PR, then updated my board cards after receiving access.
- Team confirmation of the two issues' definition of Done remains pending.

## Test Evidence
In Ubuntu, I compiled `AuthService.cpp` with the test program and interactive demo. The automated suite printed:

```text
PASS: registration, duplicate checks, validation, login, persistence, password hashing
```

I also verified registration success, login success, duplicate-username rejection, and incorrect-password rejection through the interactive demo. Actual screenshots are available from the test session and should be inserted into the team's slides/video; do not recreate terminal results.

## Code Files for Review
- [AuthService.cpp](https://github.com/Folie-et-Triste/ReleaseGuard/blob/main/AuthService.cpp)
- [AuthService.h](https://github.com/Folie-et-Triste/ReleaseGuard/blob/main/AuthService.h)
- [auth_tests.cpp](https://github.com/Folie-et-Triste/ReleaseGuard/blob/main/auth_tests.cpp)
- [auth_demo.cpp](https://github.com/Folie-et-Triste/ReleaseGuard/blob/main/auth_demo.cpp)

## Responsible Use of AI
I used ChatGPT for assistance with drafting the C++ authentication code, creating test cases, and preparing documentation. I verified the resulting work by compiling it in Ubuntu, running the automated test suite, and manually checking expected success and failure cases. Human review and team approval remain necessary for integration and acceptance.

## Sprint Review and Retrospective — Team Input Required
**Review meeting outcomes:** To be completed with actual team decisions.  
**What went well:** To be discussed with the team.  
**What did not go well:** To be discussed with the team.  
**Proposed improvements (not yet agreed retrospective action items):**
1. Grant repository and GitHub Project access before sprint implementation starts.
2. Agree on component interfaces early to reduce integration problems.
3. Schedule review, acceptance testing, and status updates before the sprint ends.

**Video link and three historical Kanban screenshots:** Must be added to the team submission using genuine evidence. The current board screenshot does not stand in for the beginning/middle sprint screenshots.
