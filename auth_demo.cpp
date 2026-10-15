#include "AuthService.h"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    const std::string path = argc > 1 ? argv[1] : "demo_accounts.txt";
    AuthService auth(path);
    std::string message;
    if (!auth.load(message)) { std::cerr << message << '\n'; return 1; }
    std::cout << "ReleaseGuard standalone authentication demo\n";
    while (true) {
        std::cout << "\n1) Register  2) Login  3) Exit\nChoice: ";
        std::string choice;
        if (!std::getline(std::cin, choice) || choice == "3") break;
        if (choice != "1" && choice != "2") { std::cout << "Unknown option\n"; continue; }
        std::string user, pass;
        std::cout << "Username: "; if (!std::getline(std::cin, user)) break;
        std::cout << "Password (visible during demo): "; if (!std::getline(std::cin, pass)) break;
        bool ok = choice == "1" ? auth.registerUser(user, pass, message) : auth.login(user, pass, message);
        std::cout << (ok ? "OK: " : "ERROR: ") << message << '\n';
    }
}
