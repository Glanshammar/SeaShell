#pragma once

#include "../types.hpp"
#include <filesystem>
#include <iostream>

class LsCommand : public Command {
public:
    void execute(Arguments args, Options opts) override {
        bool showHidden = false;
        for (const auto& opt : opts) {
            if (opt == "-a" || opt == "--all") {
                showHidden = true;
            }
        }

        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            if (!showHidden && entry.path().filename().string()[0] == '.') {
                continue;
            }
            std::cout << entry.path().filename().string() << "\n";
        }
    }
    
    std::string getName() const override { return "ls"; }
    std::string getDescription() const override { return "List directory contents"; }
    std::string getUsage() const override { return "ls [-a|--all]"; }
    std::string getCategory() const override { return "filesystem"; }
}; 