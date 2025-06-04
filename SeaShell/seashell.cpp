#include "common.hpp"
#include "commands.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <VString>
#include <VConsole>

std::vector<std::string> splitInput(const std::string& input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Parse command line tokens into a CommandArgs structure
CommandArgs parseCommandLine(const std::vector<std::string>& tokens) {
    CommandArgs args;
    
    // Process all tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        const std::string& token = tokens[i];
        
        // Check if it's an option (starts with - or --)
        if (token.size() > 1 && token[0] == '-') {
            std::string optionName;
            std::string optionValue;
            
            // Check if it's a long option (--option)
            if (token.size() > 2 && token[1] == '-') {
                optionName = token.substr(2);
            } else {
                optionName = token.substr(1);
            }
            
            // Check if the option has a value (--option=value or -o=value)
            size_t equalPos = optionName.find('=');
            if (equalPos != std::string::npos) {
                optionValue = optionName.substr(equalPos + 1);
                optionName = optionName.substr(0, equalPos);
            }
            // Check if the next token is a value (not an option)
            else if (i + 1 < tokens.size() && tokens[i + 1][0] != '-') {
                optionValue = tokens[i + 1];
                i++; // Skip the next token as we've consumed it
            }
            
            args.options[optionName] = optionValue;
        } else {
            // It's a positional argument
            args.args.push_back(token);
        }
    }
    
    return args;
}

int main() {
    std::string input;
    while (true) {
        VPrint("SeaShell");
        VPrint(getCurrentDirectory() + " >> ");

        std::getline(std::cin, input);
        if (input.empty()) continue;
        
        if (input == "exit" || input == "quit" || input == "q" || input == "e") {
            break;
        }
        
        if (input == "clear" || input == "cls") {
            system("clear");  // Use clear for Linux/macOS
            continue;
        }

        std::vector<std::string> tokens = splitInput(input);
        if (tokens.empty()) {
            std::cout << "Invalid input. Try again." << std::endl;
            continue;
        }

        std::string commandName = tokens[0];
        tokens.erase(tokens.begin()); // Remove command name
        
        // Parse the rest of the tokens into CommandArgs
        CommandArgs commandArgs = parseCommandLine(tokens);

        // Try to execute the command
        auto it = commands.find(commandName);
        if (it != commands.end()) {
            // Command found, execute it
            it->second(commandArgs);
        } else {
            // Command not found, try system command
            system(input.c_str());
        }
    }

    return 0;
}
