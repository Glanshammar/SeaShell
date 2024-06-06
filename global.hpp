#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <process.h>
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
#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>


// auto ptr = UniquePtr<int>(5);
template<typename T, typename... Args>
auto UniquePtr(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

#define Arguments const std::vector<std::string>&
#define Options const std::vector<std::string>&

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;


void UniquePointerTest();