# ReleaseGuard — Michael Morris: Sprint Report Notes (Draft)

**These are individual contribution notes, NOT a completed team Sprint 1 report.** The team has not yet conducted its Sprint Review or Sprint Retrospective.

## What's New (User Facing)
- Proposed standalone user registration, including validation and duplicate-username checks.
- Proposed standalone user login that checks supplied credentials against saved password hashes.

## Work Summary (Developer Facing) — Individual contribution
I prepared a separate C++ authentication prototype so I could add registration and login capabilities without editing my teammates' code. The implementation includes account-file persistence, salted password hashing, validation checks, a sample console demonstration, and automated tests. I submitted these additions for team review in [PR #9](https://github.com/Folie-et-Triste/ReleaseGuard/pull/9). The prototype still needs team review and integration into ReleaseGuard's existing interface.

## Difficulties / Blockers — Confirm before using as personal experience
- **Confirmed:** I could not upload directly into the team's repository, so I submitted my work from a fork as a pull request.
- **Confirmed:** I could not access the Kanban board yet, which delayed updating the cards and collecting board screenshots.
- **Possible development difficulty — only include if accurate:** Keeping registration and login consistent with the existing user-file format required extra attention.
- **Possible development difficulty — only include if accurate:** Testing duplicate usernames, incorrect passwords, and persistence took extra debugging/checks.

Do not portray either possible difficulty as something that actually happened unless confirmed.

## Completed Issues / User Stories
- **Pending team verification.** Existing login issue: https://github.com/Folie-et-Triste/ReleaseGuard/issues/3
- Registration GitHub issue: **not yet provided / may need creation**.
- Pull request: https://github.com/Folie-et-Triste/ReleaseGuard/pull/9 (**opened October 14, after the October 12 Sprint 1 end; not verified merged**).

## Unfinished Work / Incomplete Issues
- The standalone authentication prototype has not been integrated into the team's original application.
- PR review and merge are pending verification.
- Issue assignment, Kanban status, and team sprint categorization remain to be confirmed.

## Test Evidence
An automated test run in the preparation environment produced:

```text
PASS: registration, duplicate checks, validation, login, persistence, password hashing
```

Local screenshots and a personal test run by Michael: **not yet confirmed**.

## Code Files for Review
New files proposed in PR #9, including:
- `authentication/AuthService.h`
- `authentication/AuthService.cpp`
- `authentication/auth_tests.cpp`
- `authentication/auth_demo.cpp`

Review the actual PR files before posting direct file links in the final team report.

## Responsible Use of AI
ChatGPT assisted with **both implementation and documentation**, including generating a standalone authentication prototype, test cases, and draft sprint materials. The work requires human review; automated test output does not establish that the code is production-ready or integrated with the team application. The team is accountable for the final submission.

## Retrospective Summary — Not Yet Conducted
**What went well:** To be discussed by the team.  
**What to improve:** To be discussed by the team.  
**Next-sprint actions (proposals only; NOT agreed team action items):**
1. Resolve GitHub Project access earlier so everyone can update their issues.
2. Agree on the authentication interface before integration into shared code.
3. Schedule code review and test verification before the sprint deadline.

## Timing / Submission Checks
- The defined Sprint 1 period was September 15–October 12, 2026; the PR was created October 14 local time.
- Team Sprint Review: **not held yet** (per user).
- Team Sprint Retrospective: **not held yet** (per user).
- Demo video link: **pending**.
- Kanban start/mid/end screenshots: **pending real evidence**; do not fabricate historical progress.
