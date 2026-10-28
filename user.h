#include <iostream>
#include <unordered_map>
#include <string.h>
#include <fstream>
class  user{
    private:
    
    user(std::string newName, std::string newPass);
    
    public:
    std::string name;
    std::string password;
    bool logIn();
    bool signOut();
    

};

class teamMem : public user {};



class Admin : public user{};

user::user(std::string newName, std::string newPass){
    name = newName;
    password = newPass;
}

