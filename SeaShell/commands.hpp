#pragma once

#include "types.hpp"
#include "functions.hpp"
#include <functional>
#include <map>
#include <iostream>

using CommandFunction = std::function<void(Arguments args, Options opts)>;
using CommandMap = std::map<std::string, CommandFunction>;

// Command metadata structure
struct CommandInfo {
    std::string name;
    std::string description;
    std::string usage;
    std::string category;
};

// Commands metadata
inline std::map<std::string, CommandInfo> commandInfoMap = {
    {"help", {"help", "Display help information for commands", "help [command]", "system"}},
    {"py", {"py", "Run Python script", "py <script.py> [args]", "scripting"}},
    {"cd", {"cd", "Change current directory", "cd <directory>", "filesystem"}},
    {"ls", {"ls", "List directory contents", "ls [directory]", "filesystem"}},
    {"mkdir", {"mkdir", "Create a new directory", "mkdir <directory>", "filesystem"}},
    {"touch", {"touch", "Create a new file", "touch <file>", "filesystem"}},
    {"rm", {"rm", "Remove a file", "rm <file>", "filesystem"}},
    {"rmdir", {"rmdir", "Remove a directory", "rmdir <directory>", "filesystem"}},
    {"mv", {"mv", "Move a file", "mv <source> <destination>", "filesystem"}},
    {"cp", {"cp", "Copy a file", "cp <source> <destination>", "filesystem"}},
    {"ip", {"ip", "List network interfaces", "ip", "network"}},
    {"zip", {"zip", "Compress files", "zip <source> <destination.zip>", "filesystem"}},
    {"unzip", {"unzip", "Extract files", "unzip <source.zip> <destination>", "filesystem"}},
    {"find", {"find", "Find files by pattern", "find <pattern>", "filesystem"}},
    {"list", {"list", "List processes", "list", "system"}},
    {"kill", {"kill", "Terminate a process", "kill <pid|self>", "system"}},
};

// Help command implementation
void ShowHelp(Arguments args, Options opts) {
    if (args.empty()) {
        std::cout << "Available commands:\n";
        
        // Group commands by category
        std::map<std::string, std::vector<std::string>> categories;
        for (const auto& [name, info] : commandInfoMap) {
            categories[info.category].push_back(name);
        }
        
        // Print commands by category
        for (const auto& [category, commands] : categories) {
            std::cout << "\n" << category << ":\n";
            for (const auto& cmd : commands) {
                std::cout << "  " << cmd << " - " << commandInfoMap[cmd].description << "\n";
            }
        }
        
        std::cout << "\nUse 'help <command>' for more information about a specific command.\n";
    } else {
        const std::string& cmdName = args[0];
        auto it = commandInfoMap.find(cmdName);
        
        if (it != commandInfoMap.end()) {
            const auto& info = it->second;
            std::cout << "Command: " << info.name << "\n";
            std::cout << "Description: " << info.description << "\n";
            std::cout << "Usage: " << info.usage << "\n";
            std::cout << "Category: " << info.category << "\n";
        } else {
            std::cout << "Unknown command: " << cmdName << "\n";
        }
    }
}

// Initialize the command map
inline CommandMap initializeCommandMap() {
    return {
        {"help", ShowHelp},
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