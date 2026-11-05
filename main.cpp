#include <sstream>
#include "AuthService.h"
#include "REPL.h"
#include "persistence.h"
#include "activity.h"
int main(){
    bool logIn = false;
    std::string currentUser;
    std::string line;
    std::string filePath = "accounts.txt";
     AuthService Auth(filePath);
    while (logIn == false) {
        std::cout << "Register or Log in ";
        if (!std::getline(std::cin, line)) {
            std::cout << "Error, try again ";
            continue; 
        }

        // Trim leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);
        lowercase(line);
        if (line == "quit" || line == "exit") {
            std::cout << "Goodbye!" << std::endl;
            exit(0);
        }
        
        // Parse command: <algorithm> <field>
        std::istringstream iss(line);
        std::string input;
        iss >> input;
        

        if (input.empty()){
            std::cout << "You must register or log in to continue" << std::endl;
            std::cout << "  Or type 'quit' to exit." << std::endl;
            continue;
        }

        // Validate algorithm name
        if (input != "register" && input != "log") {
            std::cout << "Unknown input: " << input << std::endl;
            std::cout << "Valid commands: register, log in"
                      << std::endl;
            continue;
        }

    
        std::string message = "";
        if (input == "register"){
            std::string username = getUser();
            std::string pass = getPass(); 
        
        if(Auth.registerUser(username,pass,message)){
            std::cout << message;
            continue;

        }else{
            std::cout << message <<"\n Try Again or type exit";
            continue;
        }
    
        }
        if(input == "log"){
            std::string username = getUser();
            std::string pass = getPass();
            logIn = (Auth.login(username, pass, message));
            std::cout << message;
            if (logIn) { currentUser = username; logActivity(currentUser, "logged in"); }
                

             
        }




        std::cout << std::endl;
    }
    std::vector<release> releases = loadReleases();
    while(logIn == true){
        std::cout << "\nCommands: new, load, dashboard, history, logout\n";
        if (!std::getline(std::cin, line)) {
            std::cout << "Error, try again ";
            continue;
        }

        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);
        lowercase(line);

        if (line == "quit" || line == "exit") {
            std::cout << "Goodbye!" << std::endl;
            exit(0);
        }
        if (line == "logout") {
            logActivity(currentUser, "logged out");
            logIn = false;
            std::cout << "Logged out.\n";
            continue;
        }
        if (line == "new") {
            std::cout << "Enter version of release: ";
            std::string version;
            std::getline(std::cin, version);
            release entry(version);
            manageRelease(entry);
            releases.push_back(entry);
            saveReleases(releases);
            logActivity(currentUser, "created release " + version);
            continue;
        }
        if (line == "load") {
            if (releases.empty()) { std::cout << "No saved releases.\n"; continue; }
            std::cout << "Saved releases:\n";
            for (size_t i = 0; i < releases.size(); i++)
                std::cout << "  [" << i << "] " << releases[i].getVersion()
                          << " [" << releases[i].getStatus() << "]\n";
            std::cout << "Index to open: ";
            std::string n; std::getline(std::cin, n);
            size_t idx = (size_t)std::stoi(n);
            if (idx < releases.size()) { manageRelease(releases[idx]); saveReleases(releases); logActivity(currentUser, "opened release " + releases[idx].getVersion()); }
            else std::cout << "Invalid index.\n";
            continue;
        }
        if (line == "dashboard") {
            if (releases.empty()) { std::cout << "No releases yet.\n"; continue; }
            std::cout << "Release Dashboard:\n";
            for (size_t i = 0; i < releases.size(); i++)
                std::cout << "  " << releases[i].getVersion()
                          << " [" << releases[i].getStatus() << "] - "
                          << releases[i].getBlockers().size() << " unresolved issue(s)\n";
            continue;
        }
        if (line == "history") { printActivity(); continue; }
        std::cout << "Unknown input: " << line << "\n";
        std::cout << "Valid commands: new, load, dashboard, history, logout\n";
    }
    return 0;
}

