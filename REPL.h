#include "release.h"

void lowercase(std::string input){
    for (auto&x : input){
        x = tolower(x);
    }
}
std::string getUser(){
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
}
/*release makeRelease(){
    std::string input;
    std::cout << "Enter Version";
    std::getline(std::cin,input);
    release entry(input);
    while(input != "finish"){
        std::cout << "Add bug, test, checklist, or finish";
        if (!std::getline(std::cin, input)) {
            std::cout << "Error, try again ";
            continue; 
        }

        // Trim leading whitespace
        size_t start = input.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        input = input.substr(start);
        lowercase(input);
        if (input == "finish") {
            break;
        }
        if( input == "bug"){
            std::cout << "Enter <Title> <Serverity>";
            std::getline(std::cin, input);
            std::istringstream iss(input);
        std::string title, serv;
        iss >>title >> serv;
        bug newbug(title,serv,false);
        entry.addBug(newbug);
        }
        if(input == "test"){
            std::cout << "Enter <name>";
            std::getline(std::cin,input);
            testResult newTest(input);
            entry.addTest(newTest);

        }
        if (input == "checklist"){
            std::cout << "Enter <Discription>";
            std::getline(std::cin,input);
            checklistItem newCheck(input);
            entry.addChecklistItem(newCheck);
        }
    }
    return entry;
}*/
