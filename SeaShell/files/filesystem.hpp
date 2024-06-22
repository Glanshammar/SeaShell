#pragma once

#include "../global.hpp"
#include "../color.hpp"
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
void ChangeDirectory(Arguments args, Options options);
void ListDirectoryContents(Arguments args, Options options);
void CreateFolder(Arguments args, Options options);
void AddFile(Arguments args, Options options);
void RemoveFile(Arguments args, Options options);
void RemoveFolder(Arguments args, Options options);
void FileCopy(Arguments args, Options options);
void FileMove(Arguments args, Options options);
void FindFiles(Arguments args, Options options);