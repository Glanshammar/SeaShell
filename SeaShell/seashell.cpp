#include <map>
#include <functional>
#include "../global.hpp"
#include "functions.hpp"


std::map<std::string, std::function<void(const std::vector<std::string>& args, const std::vector<std::string>& options)>> functionMap = {
        {"exec", ExecuteFile},
        {"ssh", ConnectToSSH},
        {"py", RunPythonScript},
        {"poco", POCOLoggingTest},
};

int main() {
    SetConsoleTitle(TEXT("SeaShell"));

    HWND hwnd = GetConsoleWindow();
    auto hIcon = (HICON)LoadImage(nullptr, L"../Data/mandala.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    string input;

    while (true) {
        cout << ">> " << std::flush;
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
            cout << "Invalid input. Try again." << endl;
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

        for (const auto& item: options) {
            cout << "Option: " << item << endl;
        }

        
        if (functionMap.contains(command)) {
            functionMap[command](tokens, options);
        } else {
            cout << "Unknown command: " << command << endl;
        }
    }

    DestroyIcon(hIcon);
    return 0;
}
