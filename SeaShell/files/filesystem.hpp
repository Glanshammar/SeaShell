#pragma once

#include "../common.hpp"
#include "../types.hpp"
#include <numeric>
#include <regex>


#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#define GetCurrentDir _getcwd
#define ChangeDir _chdir
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define ChangeDir chdir
#endif

std::string getHomeDirectory();
void ChangeDirectory(const CommandArgs& args);
void ListDirectoryContents(const CommandArgs& args);
void CreateFolder(const CommandArgs& args);
void AddFile(const CommandArgs& args);
void RemoveFile(const CommandArgs& args);
void RemoveFolder(const CommandArgs& args);
void FileCopy(const CommandArgs& args);
void FileMove(const CommandArgs& args);
void FindFiles(const CommandArgs& args);