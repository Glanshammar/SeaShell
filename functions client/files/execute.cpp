#include "execute.hpp"

void ExecuteFile(const vector<string>& args, const vector<string>& options) {
    const string& filename = args[0];
    if(options[0] == "-help") {
        cout << "Usage: Yo mama!" << endl;
    }
    cout << "Executing file: " << filename << endl;
}