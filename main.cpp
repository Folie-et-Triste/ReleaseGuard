#include <sstream>
#include "AuthService.h"
#include "REPL.h"
#include "persistence.h"
const std::regex REPL::start("([A-Za-z]*) (\\w*) (\\w*)");
const std::regex REPL::release("([a-z]*) (\\w*)");
const std::regex REPL::bugs("([a-z]*) (Critcal|Major|Minor)");
const std::regex REPL::test("([a-z]*) ([a-z]*)");
const std::regex REPL::check("([a-z]*) ([a-z]*)");
std::smatch matches;
std::vector<release> currentReleases;
int main(){
    std::string currentUser;
    bool logIn = false;
    std::string message;
    std::string line;
    std::string filePath = "accounts.txt";
     AuthService Auth(filePath);
    while (logIn == false) {
        std::cout << "Register or Login ";
        std::cout <<"Format: <Choice> <Username> <Password>";
        if (!std::getline(std::cin, line)) {
            std::cout << "Error, try again ";
            continue; 
        }

        
        if (line == "quit" || line == "exit") {
            std::cout << "Goodbye!" << std::endl;
            exit(0);
        }
        std::regex_search(line,matches,REPL::start);
        if(matches.size()){
          std::string input = matches[1];
          lowercase(input);
           if(input == "login"){
            logIn = (Auth.login(matches[2], matches[3] , message));
            std::cout << message;
            continue;
           }else if(input == "register"){
          
            logIn = Auth.registerUser(matches[2],matches[3],message);
            std::cout << message;
            continue;
 
        }else{
            std::cout << "enter valid command";
            continue;
        }} std::cout << std::endl;
    }
    while(logIn == true){
        currentUser = matches[2];
       std::cout << "\nEnter Commands: \n new <Release Name>\nsave\nload\nlogout\nquit\n";
       
        if (!std::getline(std::cin, line)) {
            std::cout << "Error, try again ";
            continue; 
        }
        lowercase(line);
        std::regex_search(line,matches,REPL::release);
        if(matches.size() == 0){
            if (line == "quit" || line == "exit") {
            std::cout << "Goodbye!" << std::endl;
            exit(0);
        }else if(line == "logout"){
            logIn = false;
        }else if(line == "save"){
            saveReleases(currentReleases);
            std::cout << "Saved Current Releases";
        }else if(line == "load"){
            currentReleases = loadReleases();
            std::cout << "Loadded Releases";
        }
        }else{
            if(matches[1] == "new"){
                std::string releaseName = matches[2];
               currentReleases.push_back(makeRelease());

            }
            
        }
    

        
        
    }
    return 0;
}
