#include "filesystem.hpp"

std::string getHomeDirectory() {
#if defined(_WIN32) || defined(_WIN64)
    return std::getenv("USERPROFILE");
#else
    return std::getenv("HOME");
#endif
}

void ChangeDirectory(Arguments args, Options options) {
    if (args.size() != 1) {
        cout << "No path provided." << endl;
        return;
    }


    const string& path = args[0];

    if (path == "~" || path == "user") {
        ChangeDir(getHomeDirectory().c_str()) == 0;
    } else {
        ChangeDir(path.c_str()) == 0;
    }
}

void ListDirectoryContents(Arguments args, Options options) {
    if(options[0] == "-h"){
        cout << "Usage: ls" << endl;
        cout << "List directory contents.\n" << std::flush;
        cout << "Files has the color...\n" << std::flush;
        cout << "Directories has the color..." << endl;
        return;
    }
    try {
        std::string path = std::filesystem::current_path().string();

        for (const auto &entry : std::filesystem::directory_iterator(path)) {
            if (std::filesystem::is_directory(entry.status())) {
                setColor(Color::BLUE); // Directory color
            } else if (std::filesystem::is_regular_file(entry.status())) {
                setColor(Color::GREEN); // File color
            }
            std::cout << entry.path().filename().string() << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }

    setColor(Color::DEFAULT);
}