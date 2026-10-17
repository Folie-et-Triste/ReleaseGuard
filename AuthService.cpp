#pragma once
#include "AuthService.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

AuthService::AuthService(std::string filePath) : path_(std::move(filePath)) {}

std::string AuthService::hex(const unsigned char* bytes, std::size_t len) {
    std::ostringstream out;
    for (std::size_t i = 0; i < len; ++i) out << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i];
    return out.str();
}

bool AuthService::validUsername(const std::string& name) {
    return name.size() >= 3 && name.size() <= 32 &&
           std::all_of(name.begin(), name.end(), [](unsigned char c) { return std::isalnum(c) || c == '_' || c == '-'; });
}

std::string AuthService::derive(const std::string& password, const std::string& salt) {
    unsigned char result[32];
    if (PKCS5_PBKDF2_HMAC(password.c_str(), (int)password.size(),
                          reinterpret_cast<const unsigned char*>(salt.data()), (int)salt.size(),
                          200000, EVP_sha256(), sizeof(result), result) != 1)
        throw std::runtime_error("Unable to hash password");
    return hex(result, sizeof(result));
}

bool AuthService::load(std::string& message) {
    std::ifstream file(path_);
    if (!file.is_open()) {
        std::ifstream check(path_);
        // An absent database is acceptable for the first run.
        accounts_.clear();
        message = "No account file found; starting empty";
        return true;
    }
    std::unordered_map<std::string, Account> loaded;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto a = line.find(':');
        auto b = line.find(':', a == std::string::npos ? 0 : a + 1);
        if (a == std::string::npos || b == std::string::npos ||
            !validUsername(line.substr(0, a)) || line.substr(a + 1, b - a - 1).size() != 32 ||
            line.substr(b + 1).size() != 64 || loaded.count(line.substr(0,a))) {
            message = "Invalid account file format";
            return false;
        }
        loaded.emplace(line.substr(0, a), Account{line.substr(a + 1, b - a - 1), line.substr(b + 1)});
    }
    if (file.bad()) { message = "Could not read account file"; return false; }
    accounts_ = std::move(loaded);
    message = "Accounts loaded";
    return true;
}

bool AuthService::persist(std::string& message) const {
    std::ofstream file(path_, std::ios::trunc);
    if (!file) { message = "Could not open account file for saving"; return false; }
    for (const auto& item : accounts_)
        file << item.first << ':' << item.second.salt << ':' << item.second.digest << '\n';
    file.flush();
    if (!file) { message = "Could not save account file"; return false; }
    return true;
}

bool AuthService::registerUser(const std::string& username, const std::string& password, std::string& message) {
    if (!validUsername(username)) { message = "Username must be 3-32 letters, digits, underscores or hyphens"; return false; }
    if (password.size() < 8) { message = "Password must be at least 8 characters"; return false; }
    if (accounts_.count(username)) { message = "Username already exists"; return false; }
    unsigned char bytes[16];
    if (RAND_bytes(bytes, sizeof(bytes)) != 1) { message = "Unable to generate salt"; return false; }
    Account account{hex(bytes, sizeof(bytes)), ""};
    try { account.digest = derive(password, account.salt); }
    catch (const std::exception& e) { message = e.what(); return false; }
    accounts_[username] = account;
    if (!persist(message)) { accounts_.erase(username); return false; }
    message = "Account created";
    return true;
}

bool AuthService::login(const std::string& username, const std::string& password, std::string& message) const {
    auto it = accounts_.find(username);
    if (it == accounts_.end()) { message = "Invalid username or password"; return false; }
    try {
        const std::string candidate = derive(password, it->second.salt);
        // Constant-time comparison of fixed-length password digests.
        unsigned int difference = 0;
        for (std::size_t i = 0; i < candidate.size(); ++i)
            difference |= (unsigned char)candidate[i] ^ (unsigned char)it->second.digest[i];
        if (candidate.size() != it->second.digest.size() || difference != 0) {
            message = "Invalid username or password"; return false;
        }
    } catch (const std::exception&) { message = "Authentication unavailable"; return false; }
    message = "Login successful";
    return true;
}
