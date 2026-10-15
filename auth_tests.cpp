#include "AuthService.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main() {
    const std::string filename = "test_accounts_temporary.txt";
    std::remove(filename.c_str());
    std::string msg;
    {
        AuthService auth(filename);
        assert(auth.load(msg));
        assert(auth.registerUser("michael", "testpassword123", msg));
        assert(!auth.registerUser("michael", "testpassword456", msg));
        assert(!auth.registerUser("ab", "testpassword123", msg));
        assert(!auth.registerUser("another", "short", msg));
        assert(auth.login("michael", "testpassword123", msg));
        assert(!auth.login("michael", "wrongpassword", msg));
        assert(!auth.login("unknown", "testpassword123", msg));
    }
    {
        AuthService fresh(filename);
        assert(fresh.load(msg));
        assert(fresh.login("michael", "testpassword123", msg));
    }
    std::ifstream saved(filename);
    std::string contents((std::istreambuf_iterator<char>(saved)), std::istreambuf_iterator<char>());
    assert(contents.find("testpassword123") == std::string::npos);
    std::remove(filename.c_str());
    std::cout << "PASS: registration, duplicate checks, validation, login, persistence, password hashing\n";
}
