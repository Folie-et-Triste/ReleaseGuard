# ReleaseGuard

A command line tool that helps a team decide whether a software release is ready to ship. It tracks the bugs, test results, and checklist items for a release and reports whether the release is ready, listing anything that is still blocking it.

## What it does

- Register and log in. Passwords are stored as salted hashes, not plain text.
- Create a release and manage it from a menu: add bugs with a severity and assignee, record test results, and add checklist items.
- Run a readiness check. A release is Not Ready while any critical bug is unresolved, any test has failed, or any checklist item is incomplete. When it is Not Ready, the app lists each blocker.
- Approve or reject a release. Approval is allowed only when the readiness check passes, and a rejection records a reason.
- Save and load releases to a file, so work is kept between runs.
- View a dashboard of all releases with their status and a count of unresolved issues.
- View an activity history of who did what and when.

## Requirements

- A C++17 compiler (g++).
- OpenSSL, used for password hashing. On macOS the Makefile finds Homebrew's OpenSSL automatically. On Linux, install the OpenSSL development package (for example, `libssl-dev`).

## Build

Build the application:

```
make
```

Build the standalone demos:

```
make demos
```

Remove the built binaries:

```
make clean
```

## Run

```
./main
```

## Using the app

At the first prompt, register or log in. The format is one line with three words:

```
register yourname yourpassword
login yourname yourpassword
```

Once logged in, the available commands are:

```
new <ReleaseName>    create a release and open its menu
dashboard            list every release with status and unresolved count
history              show the activity log
save                 save all releases to file
load                 load releases from file
logout               log out
quit                 exit
```

Name a release without dots, for example `new v120`, because the input parser stops at a dot.

Inside a release, the menu commands are:

```
bug          add a bug (title, severity, assignee)
test         add a test (starts as failing)
checklist    add a checklist item (starts incomplete)
list         show all items with their index numbers
resolve      mark a bug resolved by index
pass         mark a test passed by index
complete     mark a checklist item complete by index
check        run the readiness check and show any blockers
approve      approve the release if it is ready
reject       reject the release with a reason
done         save and return to the main menu
```

## Files

- `main.cpp` runs the login and command loops.
- `REPL.h` holds the in-release menu (`manageRelease`).
- `release.h` defines the release, bug, test, and checklist types and the readiness rules.
- `AuthService.cpp` and `AuthService.h` handle registration and login.
- `persistence.h` saves and loads releases to `releases.txt`.
- `activity.h` writes and reads the activity log in `activity.txt`.
- `releaseDemo.cpp` and `requestDemo.cpp` are standalone demos of the core logic.

## Data files

The app writes `accounts.txt`, `releases.txt`, and `activity.txt` in the working directory. These are ignored by git.

## Continuous integration

A GitHub Actions workflow builds the application and the demos on every push and pull request.
