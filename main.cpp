#include <map>
#include <functional>
#include "global.hpp"
#include "functions.hpp"

int main() {

    std::map<string, std::function<void(const vector<string>&, const vector<string>& options)>> functionMap;
    functionMap["exec"] = ExecuteFile;

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

        // Check for options (assuming options start with '--')
        vector<string> options;
        for (auto it = tokens.begin(); it != tokens.end();) {
            if ((*it)[0] == '-') {
                options.push_back(*it);
                it = tokens.erase(it);
            } else {
                ++it;
            }
        }

        for (auto item: options) {
            cout << "Option: " << item << endl;
        }

        
        if (functionMap.contains(command)) {
            functionMap[command](tokens, options);
        } else {
            cout << "Unknown command: " << command << endl;
        }
    }

    return 0;
}