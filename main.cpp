#include <sstream>
#include "AuthService.h"
#include "REPL.h"
#include "persistence.h"
#include "activity.h"
const std::regex REPL::start("([A-Za-z]*) (\\w*) (\\w*)");
const std::regex REPL::release("([a-z]*) (\\w*)");
const std::regex REPL::bugs("([a-z]*) (Critcal|Major|Minor)");
const std::regex REPL::test("([a-z]*) ([a-z]*)");
const std::regex REPL::check("([a-z]*) ([a-z]*)");
std::smatch matches;
std::vector<release> currentReleases;

int main(){
    bool logIn = false;
    std::string message;
    std::string currentUser;
    std::string line;
    std::string filePath = "accounts.txt";
    AuthService Auth(filePath);

    while (logIn == false) {
        std::cout << "Register or Login ";
        std::cout << "Format: <Choice> <Username> <Password>\n";
        if (!std::getline(std::cin, line)) { std::cout << "Error, try again "; continue; }
        if (line == "quit" || line == "exit") { std::cout << "Goodbye!" << std::endl; exit(0); }
        std::regex_search(line, matches, REPL::start);
        if(matches.size()){
            std::string input = matches[1];
            lowercase(input);
            if(input == "login"){
                logIn = Auth.login(matches[2], matches[3], message);
                std::cout << message;
                if(logIn) currentUser = matches[2];
                continue;
            } else if(input == "register"){
                logIn = Auth.registerUser(matches[2], matches[3], message);
                std::cout << message;
                if(logIn) currentUser = matches[2];
                continue;
            } else {
                std::cout << "enter valid command";
                continue;
            }
        }
        std::cout << std::endl;
    }

    logActivity(currentUser, "logged in");
    currentReleases = loadReleases();

    while(logIn == true){
        std::cout << "\nEnter Commands:\n new <ReleaseName>\n dashboard\n history\n save\n load\n logout\n quit\n";
        if (!std::getline(std::cin, line)) { std::cout << "Error, try again "; continue; }
        lowercase(line);
        std::smatch cmd;
        std::regex_search(line, cmd, REPL::release);
        if(cmd.size() == 0){
            if (line == "quit" || line == "exit") { std::cout << "Goodbye!" << std::endl; exit(0); }
            else if(line == "logout"){ logActivity(currentUser, "logged out"); logIn = false; }
            else if(line == "save"){ saveReleases(currentReleases); std::cout << "Saved current releases\n"; }
            else if(line == "load"){ currentReleases = loadReleases(); std::cout << "Loaded releases\n"; }
            else if(line == "dashboard"){
                std::cout << "\nRelease Dashboard\n";
                if(currentReleases.empty()) std::cout << "  No releases yet.\n";
                for(size_t i=0;i<currentReleases.size();i++){
                    std::string st = currentReleases[i].getStatus();
                    if(st != "Approved" && st != "Rejected") currentReleases[i].updateStatus();
                    std::cout << "  " << currentReleases[i].getVersion()
                              << "  [" << currentReleases[i].getStatus() << "]"
                              << "  unresolved issues: " << currentReleases[i].getBlockers().size() << "\n";
                }
            }
            else if(line == "history"){ printActivity(); }
            else { std::cout << "enter valid command\n"; }
        } else {
            if(cmd[1] == "new"){
                std::string releaseName = cmd[2];
                release entry(releaseName);
                logActivity(currentUser, "created release " + releaseName);
                manageRelease(entry);
                currentReleases.push_back(entry);
                saveReleases(currentReleases);
                std::cout << "Release saved.\n";
            } else {
                std::cout << "enter valid command\n";
            }
        }
    }
    return 0;
}