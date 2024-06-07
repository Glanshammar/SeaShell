#include "help.hpp"

void PrintHelp(Arguments args, Options options){
    std::cout << "SeaShell Help" << std::endl;
    std::cout << "Usage: [command] [arguments] [options]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  cd [path] - Change the current working directory" << std::endl;
    std::cout << "  ls [path] - List the contents of a directory" << std::endl;
    std::cout << "  mkdir [path] - Create a new directory" << std::endl;
    std::cout << "  touch [path] - Create a new file" << std::endl;
    std::cout << "  rm [path] - Remove a file" << std::endl;
    std::cout << "  rmdir [path] - Remove a directory" << std::endl;
    std::cout << "  help - Display this help message" << std::endl;
}