#include "user.h"

class wrapper{
    private:
    std::unordered_map<std::string, std::string> userList;
    



    public:
    bool fillUser();
    std::unordered_map<std::string, std::string> getList();
    bool newUser(std::string name, std::string pass);
    bool logIn(std::string name, std::string);
};

bool wrapper::fillUser(){  //requires file be in a USER::PASSWORD format
std::ifstream userFile("userfile.txt");
std::string tempName = "";
std::string tempPass = "";

while(userFile){
std::getline(userFile,tempName, ':');
std::getline(userFile,tempPass);
userList.insert({tempName,tempPass});

}

}


bool wrapper::newUser(std::string name, std::string pass){
   std::ofstream userFile("userfile.txt" , std::ios::app);
   userList.insert({name, pass});
   userFile << name << ";" << pass;
}

bool wrapper::logIn(std::string name, std::string pass){
    if(userList[name] == pass){
        return true;}
        else{return false;}
    }

