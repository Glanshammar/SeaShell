#pragma once

#include "../types.hpp"
#include <iostream>

class HelpCommand : public Command {
public:
    void execute(Arguments args, Options opts) override {
        std::cout << "Available commands:\n";
        // TODO: Implement help command logic
    }
    
    std::string getName() const override { return "help"; }
    std::string getDescription() const override { return "Display help information for commands"; }
    std::string getUsage() const override { return "help [command]"; }
    std::string getCategory() const override { return "system"; }
};
