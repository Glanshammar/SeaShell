#include "utils.hpp"
#include <filesystem>
#include <iostream>

std::string getCurrentDirectory() {
    return std::filesystem::current_path().string();
}

void printError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}

void printSuccess(const std::string& message) {
    std::cout << "Success: " << message << std::endl;
} 