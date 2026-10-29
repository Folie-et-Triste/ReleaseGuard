#ifndef RELEASE_H
#define RELEASE_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "AuthService.cpp"


class bug {
public:
    std::string title;
    std::string severity;   // "Critical", "Major", or "Minor"
    bool resolved;
};

class testResult {
public:
    std::string name;
    bool passed;
};

class checklistItem {
public:
    std::string description;
    bool complete;
};

class release {
private:
    std::string version;
    std::string status;        // "Draft", "Submitted", "Ready", "Approved", "Rejected"
    std::string requestedBy;   // Developer who created the release request
    std::string description;   // Release notes / summary
    std::string requestDate;   // Timestamp of submission
    std::vector<bug> bugs;
    std::vector<testResult> tests;
    std::vector<checklistItem> checklist;

    std::string reviewedBy;
    std::string rejectionReason;

public:
    release(std::string ver);
    
    // Release Request creation and submission
    void submitReleaseRequest(std::string developerName, std::string desc);
    
    // Getters for release request info
    std::string getRequestedBy();
    std::string getDescription();
    std::string getRequestDate();
    std::string getReviewedBy();
    std::string getRejectionReason();
    
    // Domain operations
    void addBug(bug b);
    void addTest(testResult t);
    void addChecklistItem(checklistItem c);
    bool checkReadinessRules();
    void updateStatus();

    void approveRelease(std::string reviewerName);
    void rejectRelease(std::string reviewerName, std::string reason);
    
    std::string getStatus();
    std::string getVersion();
    std::vector<std::string> getBlockers();

    void resolveBug(size_t index);
    void passTest(size_t index);
    void completeChecklistItem(size_t index);

    std::vector<bug> getBugs();
    std::vector<testResult> getTests();
    std::vector<checklistItem> getChecklist();
};

release::release(std::string ver) {
    version = ver;
    status = "Draft";
    requestedBy = "Unassigned";
    description = "No description provided.";
    requestDate = "N/A";
}

void release::submitReleaseRequest(std::string developerName, std::string desc) {
    requestedBy = developerName;
    description = desc;
    status = "Submitted";
    
    // Generate current timestamp
    std::time_t now = std::time(nullptr);
    char buf[100];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now))) {
        requestDate = std::string(buf);
    } else {
        requestDate = "Unknown Date";
    }
}

std::string release::getRequestedBy() { return requestedBy; }
std::string release::getDescription() { return description; }
std::string release::getRequestDate() { return requestDate; }
std::string release::getReviewedBy() { return reviewedBy; }
std::string release::getRejectionReason() { return rejectionReason; }

void release::addBug(bug b) { bugs.push_back(b); }
void release::addTest(testResult t) { tests.push_back(t); }
void release::addChecklistItem(checklistItem c) { checklist.push_back(c); }

// A release is ready only if there are no unresolved critical bugs,
// every test passed, and every checklist item is complete.
bool release::checkReadinessRules() {
    for (size_t i = 0; i < bugs.size(); i++)
        if (bugs[i].severity == "Critical" && !bugs[i].resolved) return false;
    for (size_t i = 0; i < tests.size(); i++)
        if (!tests[i].passed) return false;
    for (size_t i = 0; i < checklist.size(); i++)
        if (!checklist[i].complete) return false;
    return true;
}

void release::updateStatus() {
    if (checkReadinessRules()) status = "Ready";
    else status = "Not Ready";
}

std::string release::getStatus() { return status; }
std::string release::getVersion() { return version; }

// Returns a readable list of everything blocking the release.
std::vector<std::string> release::getBlockers() {
    std::vector<std::string> out;
    for (size_t i = 0; i < bugs.size(); i++)
        if (bugs[i].severity == "Critical" && !bugs[i].resolved)
            out.push_back("Unresolved critical bug: " + bugs[i].title);
    for (size_t i = 0; i < tests.size(); i++)
        if (!tests[i].passed)
            out.push_back("Failing test: " + tests[i].name);
    for (size_t i = 0; i < checklist.size(); i++)
        if (!checklist[i].complete)
            out.push_back("Incomplete checklist item: " + checklist[i].description);
    return out;
}

void release::approveRelease(std::string reviewerName) {
    // Solo se puede aprobar si pasa las reglas de readiness (o esta en Submitted/Ready)
    if (!checkReadinessRules()) {
        std::cout << "Error: Cannot approve release with active blockers.\n";
        return;
    }
    
    status = "Approved";
    reviewedBy = reviewerName;
    rejectionReason = "N/A";
    std::cout << "Release " << version << " has been APPROVED by " << reviewerName << ".\n";
}

void release::rejectRelease(std::string reviewerName, std::string reason) {
    if (reason.empty()) {
        std::cout << "Error: A reason must be provided to reject a release.\n";
        return;
    }
    
    status = "Rejected";
    reviewedBy = reviewerName;
    rejectionReason = reason;
    std::cout << "Release " << version << " has been REJECTED by " << reviewerName << ".\n";
std::vector<bug> release::getBugs() { return bugs; }
std::vector<testResult> release::getTests() { return tests; }
std::vector<checklistItem> release::getChecklist() { return checklist; }

void release::resolveBug(size_t index) {
    if (index < bugs.size()) bugs[index].resolved = true;
}
void release::passTest(size_t index) {
    if (index < tests.size()) tests[index].passed = true;
}
void release::completeChecklistItem(size_t index) {
    if (index < checklist.size()) checklist[index].complete = true;
}

#endif // RELEASE_H
