#pragma once

#include "types.hpp"
#include "functions.hpp"
#include "commands/help_command.hpp"
#include <functional>

using CommandFunction = std::function<void(Arguments args, Options opts)>;
using CommandMap = std::map<std::string, CommandFunction>;

// Command metadata structure
struct CommandInfo {
    std::string name;
    std::string description;
    CommandFunction function;
};

// Initialize the command map
inline CommandMap initializeCommandMap() {
    return {
        {"help", [](Arguments args, Options opts) { commands::HelpCommand().execute(args, opts); }},
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