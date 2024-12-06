#include "help.hpp"

void PrintHelp(Arguments args, Options options){
    std::cout << "SeaShell Help\n";
    std::cout << "Usage: [command] [arguments] [options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "  help" << "\033[0m" << " - Display this help message.\n";
    std::cout << "  cd [path]" << "\033[0m" << " - Change the current working directory.\n";
    std::cout << "  ls" << "\033[0m" << " - List the contents of the current directory.\n";
    std::cout << "  mkdir [path]" << "\033[0m" << " - Create a new directory.\n";
    std::cout << "  touch [path]" << "\033[0m" << " - Create a new file.\n";
    std::cout << "  rm [path]" << "\033[0m" << " - Remove a file.\n";
    std::cout << "  rmdir [path]" << "\033[0m" << " - Remove a directory.\n";
    cout << std::endl;
}