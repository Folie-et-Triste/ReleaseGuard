# Proposed Sprint 1 GitHub issue updates

## Registration (new issue if not already tracked)
**Proposed ID:** RG-AUTH-01 | **Priority:** High | **Assignee:** Michael Morris (confirm) | **Effort estimate:** 2-3 hours

**User story:** As a new team member, I want to register an account so I can access ReleaseGuard.

**Acceptance criteria:**
- [ ] Register a unique username and a password with at least 8 characters.
- [ ] Reject duplicate/invalid usernames.
- [ ] Save credentials as salted password hashes, not plaintext.
- [ ] Persist and reload a registered user across program restarts.
- [ ] Demonstrate the standalone feature and run tests.

## Login (update existing GitHub Issue #3)
https://github.com/Folie-et-Triste/ReleaseGuard/issues/3

**Proposed ID:** RG-AUTH-02 | **Priority:** High | **Assignee:** Michael Morris (confirm) | **Effort estimate:** 1-2 hours

**User story:** As a registered user, I want to log in using my credentials so only a valid user can access the prototype.

**Acceptance criteria:**
- [ ] Accept correct credentials.
- [ ] Reject incorrect passwords and unknown usernames.
- [ ] Reload saved accounts from file.
- [ ] Demonstrate standalone login and run tests.

**Status caveat:** Feature is a standalone prototype until integrated with the team's main application. Do not close/issues mark Done until team confirms its definition of Done and relevant review/testing are completed.
