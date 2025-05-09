#include "commands/registry.hpp"
#include "commands/help_command.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> splitInput(const string& input) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<string> extractOptions(vector<string>& tokens) {
    vector<string> options;
    for (auto it = tokens.begin(); it != tokens.end();) {
        if ((*it)[0] == '-') {
            options.push_back(*it);
            it = tokens.erase(it);
        } else {
            ++it;
        }
    }
    return options;
}

int main() {
    auto& registry = commands::CommandRegistry::getInstance();
    
    // Register all commands
    registry.registerCommand(std::make_unique<commands::HelpCommand>());
    // TODO: Register other commands here
    
    string input;
    while (true) {
        cout << getCurrentDirectory() << " >> " << flush;

        getline(cin, input);
        if (input.empty()) continue;
        
        if (input == "exit" || input == "quit" || input == "q" || input == "e") {
            break;
        }
        
        if (input == "clear" || input == "cls") {
            system("clear");  // Use clear for Linux/macOS
            continue;
        }

        auto tokens = splitInput(input);
        if (tokens.empty()) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        string command = tokens[0];
        tokens.erase(tokens.begin());
        auto options = extractOptions(tokens);

        if (!registry.executeCommand(command, tokens, options)) {
            // If command not found, try system command
            system(input.c_str());
        }
    }

    return 0;
}
