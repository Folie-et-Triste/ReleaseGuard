#include <sstream>
#include "AuthService.h"
#include "REPL.h"
int main(){
    bool logIn = false;
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
                

             
        }




        std::cout << std::endl;
    }
    while(logIn == true){
     std::cout << "NEW Release, LOAD previous,or LOG out";
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
        if (line == "log"){
            logIn = false;
        }

       
        std::istringstream iss(line);
        std::string input;
        iss >> input;
        

        if (input.empty()){
            std::cout << "Enter NEW, LOAD, or LOG OUT" << std::endl;
            std::cout << "  Or type 'quit' to exit." << std::endl;
            continue;
        }

        // Validate algorithm name
        if (input != "new" && input != "log"&& input != "load") {
            std::cout << "Unknown input: " << input << std::endl;
            std::cout << "Valid commands: new, log in,load"
                      << std::endl;
            continue;
        }
        if (input == "new"){
            std::cout << "Enter Version of release.\n";
            std::getline(std::cin,line);
            release entry(line);

        }
    }

    return 0;
}

