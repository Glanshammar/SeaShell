#include "dll.hpp"

void LoadDll(Arguments args, Options options) {
    if(args.empty()) {
        cout << "Usage: load_dll <dll_path>" << std::endl;
        return;
    }

    const string& path = args[0];
    cout << "Loading DLL " << path << std::endl;
}