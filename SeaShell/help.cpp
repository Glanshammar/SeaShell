#include "help.hpp"

void PrintHelp(Arguments args, Options options){
    Print(Color::YELLOW, "SeaShell Help\n");
    Print(Color::DEFAULT, "Usage: [command] [arguments] [options]\n\n");
    Print(Color::CYAN, "Commands:\n");
    Print(Color::GREEN, "  help", Color::DEFAULT, "- Display this help message.\n");
    Print(Color::GREEN, "  cd [path]", Color::DEFAULT, "- Change the current working directory.\n");
    Print(Color::GREEN, "  ls", Color::DEFAULT, "- List the contents of the current directory.\n");
    Print(Color::GREEN, "  mkdir [path]", Color::DEFAULT, "- Create a new directory.\n");
    Print(Color::GREEN, "  touch [path]", Color::DEFAULT, "- Create a new file.\n");
    Print(Color::GREEN, "  rm [path]", Color::DEFAULT, "- Remove a file.\n");
    Print(Color::GREEN, "  rmdir [path]", Color::DEFAULT, "- Remove a directory.\n");
    cout << std::endl;
}