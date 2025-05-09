#include "../utils.hpp"
#include "filesystem.hpp"
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <numeric>

namespace fs = std::filesystem;

string GetHomeDirectory() {
    return getenv("HOME");
}

void ChangeDirectory(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No path provided." << endl;
        return;
    }

    string path = std::accumulate(args.begin(), args.end(), string(),
        [](const string& a, const string& b) -> string {
            return a.empty() ? b : a + " " + b;
        });

    map<string, string> directories = {
        {"~", GetHomeDirectory()},
        {"home", GetHomeDirectory()}
    };

    if (directories.find(path) != directories.end()) {
        path = directories[path];
    }

    try {
        fs::current_path(path);
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void ListDirectoryContents(Arguments args, Options options) {
    if (!args.empty() && args[0] == "--help") {
        cout << "Usage: ls" << endl;
        cout << "List directory contents." << endl;
        cout << "Files has the color..." << endl;
        cout << "Directories has the color..." << endl;
        return;
    }

    try {
        std::string path = fs::current_path().string();
        auto iterator = fs::directory_iterator(path);

        if (iterator == fs::end(iterator)) {
            cout << "The directory is empty." << endl;
            return;
        }

        for (const auto& entry : iterator) {
            cout << entry.path().filename().string() << endl;
        }
    } catch (const fs::filesystem_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void CreateFolder(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No folder path provided." << endl;
        return;
    }

    string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    try {
        if (fs::create_directory(path)) {
            //Print(Color::GREEN, "Directory created successfully: ", Color::DEFAULT, path);
            cout << "Created directory " << path << endl;
        } else {
            //Print(Color::RED, "Failed to create directory: ", Color::DEFAULT, path);
            cout << "Failed to create directory " << path << endl;
        }
    } catch (const fs::filesystem_error &e) {
        //Print(Color::RED, "Error creating directory: ", e.what());
        cout << "Error creating directory: " << e.what() << endl;
    }
}

void AddFile(Arguments args, Options options) {
    if (args.empty()) {
        //Print(Color::RED, "No file path provided.");
        cout << "No file path provided." << endl;
        return;
    }

    // Concatenate all parts of the path into a single string
    string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    // Check if the directory exists, if not, create it
    fs::path file_path(path);
    fs::path dir = file_path.parent_path();

    try {
        if (!dir.empty() && !fs::exists(dir)) {
            fs::create_directories(dir);
        }

        // Create and open the file
        std::ofstream file(path);
        if (file) {
            //setColor(Color::GREEN);
            cout << "File created successfully: " << std::flush;
            //setColor(Color::WHITE);
            cout << path << std::endl;
        } else {
            //setColor(Color::RED);
            std::cerr << "Failed to create file: " << std::flush;
            //setColor(Color::WHITE);
            std::cerr << path << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error creating file: " << e.what() << std::endl;
    }
}

void RemoveFile(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No file path provided." << std::endl;
        return;
    }

    // Concatenate all parts of the path into a single string
    string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    try {
        if (fs::remove(path)) {
            cout << "File removed successfully: " << path << std::endl;
        } else {
            cout << "Failed to remove file or file does not exist: " << path << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error removing file: " << e.what() << std::endl;
    }
}

void RemoveFolder(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No folder path provided." << std::endl;
        return;
    }

    // Concatenate all parts of the path into a single string
    string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    try {
        if (fs::remove_all(path)) {
            cout << "Folder and its contents removed successfully: " << path << std::endl;
        } else {
            cout << "Failed to remove folder or folder does not exist: " << path << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error removing folder: " << e.what() << std::endl;
    }
}

void FileMove(Arguments args, Options options) {
    if (args.size() != 2) {
        std::cerr << "Usage: mv <source> <destination>" << std::endl;
        return;
    }

    const string& source = args[0];
    const string& destination = args[1];

    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        fs::remove(source);
        cout << "File moved successfully." << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
    }
}

void FileCopy(Arguments args, Options options) {
    if (args.size() != 2) {
        std::cerr << "Usage: cp <source> <destination>" << std::endl;
        return;
    }

    const string& source = args[0];
    const string& destination = args[1];

    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        cout << "File copied successfully." << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }
}

void FindFiles(Arguments args, Options options){
    string currentDirectory = fs::current_path().string();
    const string& pattern = args[0];
    std::regex regex_pattern(pattern);

    try {
        for (const auto& entry : fs::recursive_directory_iterator(currentDirectory, fs::directory_options::skip_permission_denied)) {
            try {
                if (fs::is_regular_file(entry.status()) && std::regex_search(entry.path().string(), regex_pattern)) {
                    std::cout << entry.path() << std::endl;
                }
            } catch (const fs::filesystem_error& e) {
                continue;
            } catch (const std::regex_error& e) {
                std::cerr << "Regex error: " << e.what() << std::endl;
                return;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return;
    }
}