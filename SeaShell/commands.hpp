#pragma once

#include "types.hpp"
#include <functional>
#include <map>
#include <iostream>

// Forward declaration for the help command
void ShowHelp(const CommandArgs& args);

// Forward declarations for file operations
void EncryptFile(const CommandArgs& args);
void DecryptFile(const CommandArgs& args);
void RunPythonScript(const CommandArgs& args);
void ZIP(const CommandArgs& args);
void UnZIP(const CommandArgs& args);
void ChangeDirectory(const CommandArgs& args);
void ListDirectoryContents(const CommandArgs& args);
void CreateFolder(const CommandArgs& args);
void AddFile(const CommandArgs& args);
void RemoveFile(const CommandArgs& args);
void RemoveFolder(const CommandArgs& args);
void FileCopy(const CommandArgs& args);
void FileMove(const CommandArgs& args);
void FindFiles(const CommandArgs& args);

// Forward declarations for networking
void ListInterfaces(const CommandArgs& args);
void SendClient(const CommandArgs& args);

// Forward declarations for system operations
void KillProcess(const CommandArgs& args);
void ListProcesses(const CommandArgs& args);

// Simple function type for commands
using CommandFunc = void(*)(const CommandArgs&);

// Direct command lookup table with all commands
inline std::map<std::string, CommandFunc> commands = {
    {"help", ShowHelp},
    // File operations
    {"encrypt", EncryptFile},
    {"decrypt", DecryptFile},
    {"python", RunPythonScript},
    {"zip", ZIP},
    {"unzip", UnZIP},
    {"cd", ChangeDirectory},
    {"ls", ListDirectoryContents},
    {"mkdir", CreateFolder},
    {"touch", AddFile},
    {"rm", RemoveFile},
    {"rmdir", RemoveFolder},
    {"cp", FileCopy},
    {"mv", FileMove},
    {"find", FindFiles},
    // Networking
    {"ifconfig", ListInterfaces},
    {"sendto", SendClient},
    // System operations
    {"kill", KillProcess},
    {"ps", ListProcesses}
};


// Help command implementation
inline void ShowHelp(const CommandArgs& args) {
    std::cout << "Available commands:\n\n";
    
    for (const auto& [name, _] : commands) {
        std::cout << "  " << name << "\n";
    }
    
    std::cout << "\nUse system commands by typing them directly.\n";
}