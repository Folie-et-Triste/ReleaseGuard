#include "release.h"
#include <regex>
class REPL{
public:
static const std::regex start;
static const std::regex release;
static const std::regex bugs;
static const std::regex test;
static const std::regex check;


};

void lowercase(std::string input){
    for (auto&x : input){
        x = tolower(x);
    }
}
/*std::string getUser(){
    std::string line = "";

    while(line != "exit"){
   
    std::cout << "Enter username\n";
    if (!std::getline(std::cin, line)) {
       std::cout <<  "Error: Enter username or exit to quit \n";
            continue;
        }

        // Trim leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) 
        line = line.substr(start);
        return line;
    }
    return nullptr;
        
}
std::string getPass(){
      std::string line = "";

    while(line != "exit"){
   
    std::cout << "Enter password\n";
    if (!std::getline(std::cin, line)) {
       std::cout <<  "Error: Enter password or exit to quit\n";
            continue;
        }

        // Trim leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) 
        line = line.substr(start);
        return line;
    }
    return nullptr;
}*/

release makeRelease(){
    std::string input;
    std::smatch matches;
    std::cout << "Enter Version";
    std::getline(std::cin,input);
    release entry(input);
    while(input != "finish"){
        std::cout << "Add bugs <title> <severity> or type 'finish'";
        if (!std::getline(std::cin, input)) {
            std::cout << "Error, try again ";
            continue; 
        }

       if (regex_search(input,matches,REPL::bugs) && regex_match(input,REPL::bugs)){
        bug newbug(matches[1],matches[2],false);
        entry.addBug(newbug);

        }
        else{
            std::cout << "Error, incorrect input";
        }
    }input = "";
    while(input != "finish"){
   
       std::cout << "Add tests <title> or type 'finish'";
        if (!std::getline(std::cin, input)) {
            std::cout << "Error, try again ";
            continue; 
        }

       if (regex_search(input,matches,REPL::test)&& regex_match(input,REPL::test)){
        testResult newtest(matches[1],false);
        entry.addTest(newtest);

        }else{
            std::cout << "Error, incorrect input";
        }
        }input = "";
    while(input != "finish"){
         std::cout << "Add checklist item <title> or type 'finish'";
        if (!std::getline(std::cin, input)) {
            std::cout << "Error, try again ";
            continue; 
        }

       if (regex_search(input,matches,REPL::check)&& regex_match(input,REPL::test)){
        checklistItem newcheck(matches[1],false);
        entry.addChecklistItem(newcheck);

        }else{
            std::cout << "Error, incorrect input";
        }
    }
    return entry;
}
// Release management menu: add bugs/tests/checklist items, mark them done,
// and run the readiness check from inside the REPL.
void manageRelease(release &entry){
    std::string line;
    while(true){
        std::cout << "\nRelease " << entry.getVersion() << " [" << entry.getStatus() << "]\n";
        std::cout << "Commands: bug, test, checklist, list, resolve, pass, complete, check, done\n";
        if(!std::getline(std::cin, line)) return;
        size_t start = line.find_first_not_of(" \t");
        if(start == std::string::npos) continue;
        line = line.substr(start);
        lowercase(line);

        if(line == "done") return;

        else if(line == "bug"){
            bug b;
            std::cout << "Title: ";       std::getline(std::cin, b.title);
            std::cout << "Severity (Critical/Major/Minor): "; std::getline(std::cin, b.severity);
            std::cout << "Assignee: "; std::getline(std::cin, b.assignee);
            b.resolved = false;
            entry.addBug(b);
            std::cout << "Bug added.\n";
        }
        else if(line == "test"){
            testResult t;
            std::cout << "Test name: "; std::getline(std::cin, t.name);
            t.passed = false;
            entry.addTest(t);
            std::cout << "Test added (failing until passed).\n";
        }
        else if(line == "checklist"){
            checklistItem c;
            std::cout << "Description: "; std::getline(std::cin, c.description);
            c.complete = false;
            entry.addChecklistItem(c);
            std::cout << "Checklist item added.\n";
        }
        else if(line == "list"){
            std::vector<bug> bs = entry.getBugs();
            std::vector<testResult> ts = entry.getTests();
            std::vector<checklistItem> cs = entry.getChecklist();
            std::cout << "Bugs:\n";
            for(size_t i=0;i<bs.size();i++)
                std::cout << "  [" << i << "] " << bs[i].title << " (" << bs[i].severity
                          << ", " << bs[i].assignee << ") "
                          << (bs[i].resolved ? "resolved" : "open") << "\n";
            std::cout << "Tests:\n";
            for(size_t i=0;i<ts.size();i++)
                std::cout << "  [" << i << "] " << ts[i].name << " "
                          << (ts[i].passed ? "pass" : "fail") << "\n";
            std::cout << "Checklist:\n";
            for(size_t i=0;i<cs.size();i++)
                std::cout << "  [" << i << "] " << cs[i].description << " "
                          << (cs[i].complete ? "done" : "incomplete") << "\n";
        }
        else if(line == "resolve"){
            std::cout << "Bug index: "; std::string n; std::getline(std::cin, n);
            entry.resolveBug((size_t)std::stoi(n));
            std::cout << "Bug marked resolved.\n";
        }
        else if(line == "pass"){
            std::cout << "Test index: "; std::string n; std::getline(std::cin, n);
            entry.passTest((size_t)std::stoi(n));
            std::cout << "Test marked passed.\n";
        }
        else if(line == "complete"){
            std::cout << "Checklist index: "; std::string n; std::getline(std::cin, n);
            entry.completeChecklistItem((size_t)std::stoi(n));
            std::cout << "Checklist item marked complete.\n";
        }
        else if(line == "check"){
            entry.updateStatus();
            std::cout << "Status: " << entry.getStatus() << "\n";
            std::vector<std::string> bl = entry.getBlockers();
            if(bl.empty()){
                std::cout << "All readiness rules passed. OK to approve.\n";
            } else {
                std::cout << "Approval blocked by:\n";
                for(size_t i=0;i<bl.size();i++) std::cout << "  - " << bl[i] << "\n";
            }
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }
}