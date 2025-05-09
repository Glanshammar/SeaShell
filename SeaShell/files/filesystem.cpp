#include "../utils.hpp"
#include "filesystem.hpp"
#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <numeric>

std::string GetHomeDirectory() {
    return std::getenv("HOME");
}

void ChangeDirectory(Arguments args, [[maybe_unused]] Options options) {
    if (args.empty()) {
        std::cout << "No path provided." << std::endl;
        return;
    }

    std::string path = std::accumulate(args.begin(), args.end(), std::string(),
        [](const std::string& a, const std::string& b) -> std::string {
            return a.empty() ? b : a + " " + b;
        });

    std::map<std::string, std::string> directories = {
        {"~", GetHomeDirectory()},
        {"home", GetHomeDirectory()}
    };

    if (directories.find(path) != directories.end()) {
        path = directories[path];
    }

    try {
        std::filesystem::current_path(path);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void ListDirectoryContents(Arguments args, [[maybe_unused]] Options options) {
    if (!args.empty() && args[0] == "--help") {
        std::cout << "Usage: ls" << std::endl;
        std::cout << "List directory contents." << std::endl;
        std::cout << "Files has the color..." << std::endl;
        std::cout << "Directories has the color..." << std::endl;
        return;
    }

    try {
        std::string path = std::filesystem::current_path().string();
        auto iterator = std::filesystem::directory_iterator(path);

        if (iterator == std::filesystem::end(iterator)) {
            std::cout << "The directory is empty." << std::endl;
            return;
        }

        for (const auto& entry : iterator) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void CreateFolder(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No folder path provided." << std::endl;
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
        if (std::filesystem::create_directory(path)) {
            //Print(Color::GREEN, "Directory created successfully: ", Color::DEFAULT, path);
            cout << "Created directory " << path << std::endl;
        } else {
            //Print(Color::RED, "Failed to create directory: ", Color::DEFAULT, path);
            cout << "Failed to create directory " << path << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        //Print(Color::RED, "Error creating directory: ", e.what());
        cout << e.what() << std::endl;
    }
}

void AddFile(Arguments args, Options options) {
    if (args.empty()) {
        //Print(Color::RED, "No file path provided.");
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

    // Check if the directory exists, if not, create it
    std::filesystem::path file_path(path);
    std::filesystem::path dir = file_path.parent_path();

    try {
        if (!dir.empty() && !std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
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
    } catch (const std::filesystem::filesystem_error &e) {
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
        if (std::filesystem::remove(path)) {
            cout << "File removed successfully: " << path << std::endl;
        } else {
            cout << "Failed to remove file or file does not exist: " << path << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
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
        if (std::filesystem::remove_all(path)) {
            cout << "Folder and its contents removed successfully: " << path << std::endl;
        } else {
            cout << "Failed to remove folder or folder does not exist: " << path << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
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
        std::filesystem::copy(source, destination, std::filesystem::copy_options::overwrite_existing);
        std::filesystem::remove(source);
        cout << "File moved successfully." << std::endl;
    } catch (std::filesystem::filesystem_error& e) {
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
        std::filesystem::copy(source, destination, std::filesystem::copy_options::overwrite_existing);
        cout << "File copied successfully." << std::endl;
    } catch (std::filesystem::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }
}

void FindFiles(Arguments args, Options options){
    string currentDirectory = std::filesystem::current_path().string();
    const string& pattern = args[0];
    std::regex regex_pattern(pattern);

    try {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(currentDirectory, std::filesystem::directory_options::skip_permission_denied)) {
            try {
                if (std::filesystem::is_regular_file(entry.status()) && std::regex_search(entry.path().string(), regex_pattern)) {
                    std::cout << entry.path() << std::endl;
                }
            } catch (const std::filesystem::filesystem_error& e) {
                continue;
            } catch (const std::regex_error& e) {
                std::cerr << "Regex error: " << e.what() << std::endl;
                return;
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return;
    }
}