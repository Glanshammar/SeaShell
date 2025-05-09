#pragma once

#include "types.hpp"
#include "functions.hpp"


// Command metadata structure
struct CommandInfo {
    std::string name;
    std::string description;
    CommandFunction function;
};

// Initialize the command map
inline CommandMap initializeCommandMap() {
    return {
        {"help", PrintHelp},
        {"py", RunPythonScript},
        {"cd", ChangeDirectory},
        {"ls", ListDirectoryContents},
        {"mkdir", CreateFolder},
        {"touch", AddFile},
        {"rm", RemoveFile},
        {"rmdir", RemoveFolder},
        {"mv", FileMove},
        {"cp", FileCopy},
        {"ip", ListInterfaces},
        {"zip", ZIP},
        {"unzip", UnZIP},
        {"find", FindFiles},
        {"list", ListProcesses},
        {"kill", KillProcess},
    };
}

inline const CommandMap functionMap = initializeCommandMap();