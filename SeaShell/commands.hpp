#pragma once

#include <global.hpp>
#include <functions.hpp>

std::map<std::string, std::function<void(const std::vector<std::string>& args, const std::vector<std::string>& options)>> functionMap = {
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
};