#pragma once

#include <string>
using std::string;

inline void OpenURL(const string& url) {
#ifdef _WIN32
    string command = "start " + url;
#elif __APPLE__
    string command = "open " + url;
#else
    string command = "xdg-open " + url;
#endif
    system(command.c_str());
} 