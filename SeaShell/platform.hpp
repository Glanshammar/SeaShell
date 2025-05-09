#pragma once

#include <string>

inline void openURL(const std::string& url) {
#ifdef _WIN32
    std::string command = "start " + url;
#elif __APPLE__
    std::string command = "open " + url;
#else
    std::string command = "xdg-open " + url;
#endif
    system(command.c_str());
} 