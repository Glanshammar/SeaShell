#include <functional>
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

void Setup() {
#if defined(_WIN32) || defined(_WIN64)
    SetConsoleTitle(TEXT("SeaShell"));

    // Get the path of the executable
    TCHAR buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    std::wstring exePath(buffer);

    // Extract the directory path from the executable path
    std::wstring::size_type pos = exePath.find_last_of(L"\\/");
    if (pos == std::wstring::npos) {
        std::cerr << "Failed to get executable directory path" << std::endl;
        return;
    }
    std::wstring dirPath = exePath.substr(0, pos + 1);

    // Specify the name of the icon file (assuming it's in the same directory as the executable)
    std::wstring iconFileName = dirPath + L"sea.ico";

    // Load the icon from file
    HICON hIcon = static_cast<HICON>(LoadImage(
            nullptr,
            iconFileName.c_str(),
            IMAGE_ICON,
            0,
            0,
            LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
    ));

    if (!hIcon) {
        std::cerr << "Failed to load icon" << std::endl;
        return;
    }

    // Set the icon for the console window
    HWND hwnd = GetConsoleWindow();
    if (hwnd) {
        // Set both small and large icons
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon));
        SendMessage(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon));
    } else {
        std::cerr << "Failed to get console window handle" << std::endl;
    }

#else // Linux
    std::cout << "\033]0;SeaShell\007";
#endif
}

int main() {
    Setup();

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
