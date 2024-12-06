#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif


#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <csignal>
#include <cstring>
#include <memory>
#include <any>
#include <filesystem>
#include <fstream>
#include <cstdlib>


// auto ptr = UniquePtr<int>(5);
template<typename T, typename... Args>
auto UniquePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

using Arguments = const std::vector<std::string>&;
using Options = const std::vector<std::string>&;
#define CurrentDirectory std::filesystem::current_path().string()

using std::string;
using std::vector;
using std::cout;
using std::cin;

void UniquePointerTest();

