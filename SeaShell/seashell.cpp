#include <functional>
#include <VApplication>
#include "global.hpp"
#include "functions.hpp"
#include "networking/sql.hpp"

std::map<std::string, std::function<void(const std::vector<std::string>& args, const std::vector<std::string>& options)>> functionMap = {
        {"help", PrintHelp},
        {"exec", ExecuteFile},
        {"py", RunPythonScript},
        {"cd", ChangeDirectory},
        {"ls", ListDirectoryContents},
        {"mkdir", CreateFolder},
        {"touch", AddFile},
        {"rm", RemoveFile},
        {"rmdir", RemoveFolder},
        {"mv", FileMove},
        {"cp", FileCopy},
        {"ip", ListInterfaces},
        {"zip", ZIP},
        {"unzip", UnZIP},
        {"find", FindFiles},
};


int main() {
    VApplication::setIcon("C:/Users/Mondus/Pictures/Programs/mandala.ico");
    VApplication::setTitleBar("SeaShell");

    string input;
    ChangeDirectory({"home"}, {});

    while (true) {
        Print(Color::CYAN, CurrentDir);
        cout << " >> " << std::flush;

        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        } else if(input == "exit" || input == "quit" || input == "q" || input == "e") {
            break;
        } else if (input == "clear" || input == "cls") {
            system("cls");
            continue;
        }

        vector<string> tokens;
        size_t pos;
        while ((pos = input.find(' ')) != string::npos) {
            string token = input.substr(0, pos);
            if (!token.empty()) {
                tokens.push_back(token);
            }
            input.erase(0, pos + 1);
        }
        if (!input.empty()) {
            tokens.push_back(input);
        }

        if (tokens.empty()) {
            cout << "Invalid input. Try again." << std::endl;
            continue;
        }

        string command = tokens[0];
        tokens.erase(tokens.begin());

        vector<string> options;
        for (auto it = tokens.begin(); it != tokens.end();) {
            if ((*it)[0] == '-') {
                options.push_back(*it);
                it = tokens.erase(it);
            } else {
                ++it;
            }
        }

        if (functionMap.contains(command)) {
            functionMap[command](tokens, options);
        } else {
            system(input.c_str());
        }
    }

    return 0;
}
