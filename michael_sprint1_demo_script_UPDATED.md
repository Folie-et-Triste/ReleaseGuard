# ReleaseGuard — Michael Morris — Demo Script and Screenshot Plan

**Format:** Display actual Ubuntu screenshots/test output and the team's existing UML collaboration diagram.  
**Speaking time:** Approximately 1–2 minutes for this individual segment; coordinate timing with the team.

## What to say

“My part of ReleaseGuard was to add user registration and user login as a separate C++ authentication prototype. I kept the existing team files unchanged. Registration validates the username and password, rejects duplicate accounts, and saves a salted password hash instead of storing the password directly. Login checks the entered credentials against saved account records and rejects incorrect passwords.

I compiled the feature in Ubuntu and ran automated tests. They passed for account creation, duplicate and invalid registration, valid and invalid login, password storage, and persistence after reloading. I also ran the menu-based demonstration and captured the results. Here are the screenshots showing registration, login, and rejection cases. The code is merged through Pull Request #9, but it still needs to be integrated into the team's main ReleaseGuard interface.

I contributed the collaboration UML diagram for the release-approval workflow. It shows the manager interacting with the review interface, which contacts a controller to check a FixRequest's readiness before approval. That prevents approval from moving forward without passing the required readiness checks.

I used ChatGPT to help with code drafting, tests, and documentation. I checked the generated work by compiling and running tests and reviewing the output. AI assistance did not replace team code review or final responsibility for the project.”

## What to display, in order
1. Screenshot of Ubuntu `./auth_tests` showing the PASS message.
2. Ubuntu demo screenshot showing a successful registration and login.
3. Ubuntu demo screenshot showing incorrect-password and duplicate-account rejection.
4. [Merged PR #9](https://github.com/Folie-et-Triste/ReleaseGuard/pull/9) and the [Kanban board](https://github.com/users/Folie-et-Triste/projects/2/views/1).
5. Existing collaboration diagram in `DiagramsAssignmentTeam10 (2).pdf` (approval workflow, not an authentication diagram).

## Commands used (run from repository root)
```bash
g++ -std=c++17 AuthService.cpp auth_tests.cpp -lcrypto -o auth_tests
./auth_tests
g++ -std=c++17 AuthService.cpp auth_demo.cpp -lcrypto -o auth_demo
./auth_demo
```
Use fictional demo passwords, because the console program echoes entered passwords.
