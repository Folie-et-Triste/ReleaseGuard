#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <fstream>
#include <string>
#include <ctime>
#include <iostream>

inline void logActivity(const std::string &user, const std::string &action,
                        const std::string &path = "activity.txt"){
    std::ofstream out(path, std::ios::app);
    std::time_t now = std::time(nullptr);
    char buf[100];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now)))
        out << buf << " | " << user << " | " << action << "\n";
}

inline void printActivity(const std::string &path = "activity.txt"){
    std::ifstream in(path);
    if(!in){ std::cout << "No activity recorded yet.\n"; return; }
    std::cout << "Activity History:\n";
    std::string line;
    while(std::getline(in, line)) std::cout << "  " << line << "\n";
}

#endif
