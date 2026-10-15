#include <iostream>
#include <string>
#include <vector>

// Release Readiness feature (Issue #5: Readiness review)
// Added as a new file; does not modify existing team code.

class bug{
    public:
    std::string title;
    std::string severity;   // "Critical", "Major", or "Minor"
    bool resolved;
};

class testResult{
    public:
    std::string name;
    bool passed;
};

class checklistItem{
    public:
    std::string description;
    bool complete;
};

class release{
    private:
    std::string version;
    std::string status;
    std::vector<bug> bugs;
    std::vector<testResult> tests;
    std::vector<checklistItem> checklist;

    public:
    release(std::string ver);
    void addBug(bug b);
    void addTest(testResult t);
    void addChecklistItem(checklistItem c);
    bool checkReadinessRules();
    void updateStatus();
    std::string getStatus();
    std::string getVersion();
    std::vector<std::string> getBlockers();
};

release::release(std::string ver){
    version = ver;
    status = "Draft";
}

void release::addBug(bug b){ bugs.push_back(b); }
void release::addTest(testResult t){ tests.push_back(t); }
void release::addChecklistItem(checklistItem c){ checklist.push_back(c); }

// A release is ready only if there are no unresolved critical bugs,
// every test passed, and every checklist item is complete.
bool release::checkReadinessRules(){
    for(size_t i = 0; i < bugs.size(); i++)
        if(bugs[i].severity == "Critical" && !bugs[i].resolved) return false;
    for(size_t i = 0; i < tests.size(); i++)
        if(!tests[i].passed) return false;
    for(size_t i = 0; i < checklist.size(); i++)
        if(!checklist[i].complete) return false;
    return true;
}

void release::updateStatus(){
    if(checkReadinessRules()) status = "Ready";
    else status = "Not Ready";
}

std::string release::getStatus(){ return status; }
std::string release::getVersion(){ return version; }

// Returns a readable list of everything blocking the release.
std::vector<std::string> release::getBlockers(){
    std::vector<std::string> out;
    for(size_t i = 0; i < bugs.size(); i++)
        if(bugs[i].severity == "Critical" && !bugs[i].resolved)
            out.push_back("Unresolved critical bug: " + bugs[i].title);
    for(size_t i = 0; i < tests.size(); i++)
        if(!tests[i].passed)
            out.push_back("Failing test: " + tests[i].name);
    for(size_t i = 0; i < checklist.size(); i++)
        if(!checklist[i].complete)
            out.push_back("Incomplete checklist item: " + checklist[i].description);
    return out;
}
