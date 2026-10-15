# ReleaseGuard — Michael Morris: Demo Script and Screenshot Plan

**Format:** Screenshots and test results (not a live demo).  
**Approximate speaking time:** 1–2 minutes plus questions.

## Suggested narration

"My contribution is a standalone authentication prototype for ReleaseGuard. I added user registration and user login without modifying the code my teammates had already created. Registration checks that usernames are valid and not already in use, requires a password of at least eight characters, and saves password hashes instead of plaintext passwords. Login checks the saved account against the entered password and rejects invalid credentials.

For verification, I prepared automated tests covering account creation, duplicate registration, input validation, successful and failed login, saving and reloading accounts, and password hashing. Here are the test results [display a screenshot you captured after running the tests]. The prototype isn't integrated into the main ReleaseGuard interface yet, so that integration would need to be coordinated with the team.

I also contributed to the collaboration UML diagram. It shows the manager requesting a release review through the review interface, which talks to the controller. The controller checks the FixRequest's readiness before approval can proceed. This matters because the system should block approval when a release is not ready."

## Screenshots to capture yourself
1. The terminal command running `auth_tests` and the actual PASS message (only if you successfully run it locally).
2. The registration demonstration accepting a new test account and rejecting a duplicate username.
3. The login demonstration accepting a correct test password and rejecting an incorrect password.
4. The GitHub pull request showing your new files and review status: https://github.com/Folie-et-Triste/ReleaseGuard/pull/9
5. The team's collaboration diagram from the existing UML PDF (use the actual submitted diagram, not a recreated one).

## Build and run instructions
From the **new** `authentication/` folder, with a C++17 compiler and OpenSSL development libraries installed:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic AuthService.cpp auth_tests.cpp -lcrypto -o auth_tests
./auth_tests
g++ -std=c++17 -Wall -Wextra -pedantic AuthService.cpp auth_demo.cpp -lcrypto -o auth_demo
./auth_demo
```

Use only fictional demo credentials. Do not claim local tests succeeded unless you actually ran them. The automated tests passed in the preparation environment, but your own screenshots must show your own run.

## AI disclosure (brief)
"I used ChatGPT to help write the authentication prototype, plan tests, and draft documentation. I checked the code with automated tests and reviewed its scope. The team remains responsible for validating and integrating the final code."

## Important scope note
Your collaboration UML contribution addresses **release approval**, not login. Do not suggest the UML diagram represents the authentication prototype directly.
