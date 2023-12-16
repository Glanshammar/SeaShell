#include <map>
#include <functional>
#include "functions/global.h"
#include "functions/foobar.h"

int main() {
    std::map<string, std::function<void(const vector<string>&)>> functionMap;
    functionMap["foo"] = foo;
    functionMap["bar"] = bar;

    string input;

    while (true) {
        cout << ">> ";
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

        if (functionMap.contains(command)) {
            functionMap[command](tokens);
        } else {
            cout << "Unknown command: " << command << endl;
        }
    }

    return 0;
}
