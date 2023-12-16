#include "foobar.h"
#include "global.h"

void foo(const vector<string>& args) {
    cout << "Executing 'foo' function with " << args.size() << " arguments:" << endl;
    for (const string& arg : args) {
        cout << arg << endl;
    }
}

void bar(const vector<string>& args) {
    cout << "Executing 'bar' function with " << args.size() << " arguments:" << endl;
    for (const string& arg : args) {
        cout << arg << endl;
    }
}