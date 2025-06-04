#pragma once

#include "common.hpp"
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

[[nodiscard]] inline bool isNumeric(const string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

[[nodiscard]] inline std::wstring StringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

// Core utility functions
[[nodiscard]] std::string getCurrentDirectory();
void printError(const std::string& message);
void printSuccess(const std::string& message); 