#include <map>
#include <functional>
#include "global.hpp"
#include "functions.hpp"


std::map<std::string, std::function<void(const std::vector<std::string>& args, const std::vector<std::string>& options)>> functionMap = {
        {"help", PrintHelp},
        {"exec", ExecuteFile},
        {"ssh", ConnectToSSH},
        {"py", RunPythonScript},
        {"poco", POCOLoggingTest},
        {"cd", ChangeDirectory},
        {"ls", ListDirectoryContents},
        {"mkdir", CreateFolder},
        {"touch", AddFile},
        {"rm", RemoveFile},
        {"rmdir", RemoveFolder},
        {"mv", FileMove},
        {"cp", FileCopy},
        {"ip", ListInterfaces},
};


void SetupConsoleWindow() {
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleTitle(TEXT("SeaShell"));
    HWND hwnd = GetConsoleWindow();

    auto iconDeleter = [](HICON hIcon) {
        if (hIcon) {
            DestroyIcon(hIcon);
        }
    };

    std::unique_ptr<std::remove_pointer<HICON>::type, decltype(iconDeleter)> hIcon(
            (HICON)LoadImage(nullptr, L"../Data/mandala.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE),
            iconDeleter
    );

    if (hIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon.get());
    } else {
        std::cerr << "Failed to load icon" << std::endl;
    }
#endif
}

int main() {
    SetupConsoleWindow();

    string input;
    ChangeDirectory({"~"}, {});

    while (true) {
        setColor(Color::CYAN);
        std::cout << CurrentDir;
        setColor(Color::WHITE);
        std::cout << " >> " << std::flush;

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
