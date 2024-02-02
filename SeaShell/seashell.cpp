#include <map>
#include <functional>
#include "../global.hpp"
#include "functions.hpp"
#include "networking/client.hpp"


void ClearConsole(const vector<string>& args, const vector<string>& options) {
    system("cls");
}

int main() {

    SetConsoleTitle(TEXT("SeaShell"));

    HWND hwnd = GetConsoleWindow();  // Assuming you are working with a console window
    auto hIcon = (HICON)LoadImage(NULL, "C:/Users/Mondus/Pictures/Program Media/mandala.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    std::map<string, std::function<void(const vector<string>& args, const vector<string>& options)>> functionMap = {
        {"exec", ExecuteFile},
        {"connect", ConnectToServer},
        {"clear", ClearConsole},
    };

    string input;

    while (true) {
        cout << ">> " << std::flush;
        std::getline(std::cin, input);

        if(input == "exit") {
            break;
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
