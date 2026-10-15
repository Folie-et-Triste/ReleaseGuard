#pragma once
#include <string>
#include <unordered_map>

// Independent Sprint 1 prototype. Does not include or alter teammate code.
class AuthService {
public:
    explicit AuthService(std::string filePath);
    bool registerUser(const std::string& username, const std::string& password, std::string& message);
    bool login(const std::string& username, const std::string& password, std::string& message) const;
    bool load(std::string& message);
private:
    struct Account { std::string salt; std::string digest; };
    std::string path_;
    std::unordered_map<std::string, Account> accounts_;
    static std::string derive(const std::string& password, const std::string& salt);
    static std::string hex(const unsigned char* bytes, std::size_t len);
    static bool validUsername(const std::string& username);
    bool persist(std::string& message) const;
};
