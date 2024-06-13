#include "filesystem.hpp"

string getHomeDirectory() {
#if defined(_WIN32) || defined(_WIN64)
    return std::getenv("USERPROFILE");
#else
    return std::getenv("HOME");
#endif
}

std::map<string, string> directories = {
        {"home", getHomeDirectory()},
};

void ChangeDirectory(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No path provided." << std::endl;
        return;
    }


    string path = std::accumulate(args.begin(), args.end(), string(),
                                       [](const string& a, const string& b) -> string {
                                           return a + (!a.empty() ? " " : "") + b;
                                       });

    int result = -1;

    auto it = directories.find(path);
    if (it != directories.end()) {
        result = ChangeDir(it->second.c_str());
    } else {
        result = ChangeDir(path.c_str());
    }

    if (result != 0) {
        perror("ChangeDir failed");
    }
}

void ListDirectoryContents(Arguments args, Options options) {
    if(!options.empty()){
        if(options[0] == "-h"){
            cout << "Usage: ls" << std::endl;
            cout << "List directory contents." << std::endl;
            cout << "Files has the color..." << std::endl;
            cout << "Directories has the color..." << std::endl;
            return;
        }
    }
    try {
        string path = std::filesystem::current_path().string();

        auto iterator = std::filesystem::directory_iterator(path);

        if (iterator == std::filesystem::end(iterator)) {
            cout << "The directory is empty." << std::endl;
            return;
        }

        for (const auto &entry : iterator) {
            if (std::filesystem::is_directory(entry.status())) {
                setColor(Color::GREEN);
            } else if (std::filesystem::is_regular_file(entry.status())) {
                setColor(Color::YELLOW);
            }
            cout << entry.path().filename().string() << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        Print(Color::RED, "Error accessing directory: ", e.what());
    }

    setColor(Color::DEFAULT);
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
            Print(Color::GREEN, "Directory created successfully: ", Color::DEFAULT, path);
        } else {
            Print(Color::RED, "Failed to create directory: ", Color::DEFAULT, path);
        }
    } catch (const std::filesystem::filesystem_error &e) {
        Print(Color::RED, "Error creating directory: ", e.what());
    }
}

void AddFile(Arguments args, Options options) {
    if (args.empty()) {
        Print(Color::RED, "No file path provided.");
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
            setColor(Color::GREEN);
            cout << "File created successfully: " << std::flush;
            setColor(Color::WHITE);
            cout << path << std::endl;
        } else {
            setColor(Color::RED);
            std::cerr << "Failed to create file: " << std::flush;
            setColor(Color::WHITE);
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