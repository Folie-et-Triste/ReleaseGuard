#include <iostream>
#include "release.h"

int main() {
    std::cout << "=== Testing Release Request Feature (#7) ===" << std::endl;

    // 1. Create a release instance
    release rel("v1.2.0");
    std::cout << "Initial Status: " << rel.getStatus() << std::endl;

    // 2. Submit a release request
    rel.submitReleaseRequest("Alice (Developer)", "Release v1.2.0 includes payment module fixes.");
    
    std::cout << "\n--- Release Request Submitted ---" << std::endl;
    std::cout << "Version: " << rel.getVersion() << std::endl;
    std::cout << "Status: " << rel.getStatus() << std::endl;
    std::cout << "Requested By: " << rel.getRequestedBy() << std::endl;
    std::cout << "Description: " << rel.getDescription() << std::endl;
    std::cout << "Date: " << rel.getRequestDate() << std::endl;

    return 0;
}