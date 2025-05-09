#pragma once

#include "common.hpp"
#include <algorithm>
#include <filesystem>

[[nodiscard]] inline bool isNumeric(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

[[nodiscard]] inline std::wstring StringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

[[nodiscard]] inline std::string getCurrentDirectory() {
    return std::filesystem::current_path().string();
} 