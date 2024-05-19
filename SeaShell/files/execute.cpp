#include "execute.hpp"

void ExecuteFile(Arguments args, Options options) {
    const string& path = args[0];
    system(path.c_str());
}