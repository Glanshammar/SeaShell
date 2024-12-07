#pragma once

#include <global.hpp>
#include <functions.hpp>

inline std::map<std::string, std::function<void(Arguments arguments, Options options)>> functionMap = {
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