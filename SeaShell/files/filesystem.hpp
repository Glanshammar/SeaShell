#pragma once

#include "../../global.hpp"
#include "../color.hpp"

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