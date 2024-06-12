#include "filesystem.hpp"

string getHomeDirectory() {
#if defined(_WIN32) || defined(_WIN64)
    return std::getenv("USERPROFILE");
#else
    return std::getenv("HOME");
#endif
}

std::map<std::string, std::string> directories = {
        {"home", getHomeDirectory()},
};

void ChangeDirectory(Arguments args, Options options) {
    if (args.empty()) {
        cout << "No path provided." << std::endl;
        return;
    }


    string path = std::accumulate(args.begin(), args.end(), std::string(),
                                       [](const std::string& a, const std::string& b) -> std::string {
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
        std::string path = std::filesystem::current_path().string();

        auto iterator = std::filesystem::directory_iterator(path);

        if (iterator == std::filesystem::end(iterator)) {
            std::cout << "The directory is empty." << std::endl;
            return;
        }

        for (const auto &entry : iterator) {
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

void CreateFolder(Arguments args, Options options) {
    if (args.empty()) {
        setColor(Color::RED);
        std::cerr << "No path provided." << std::endl;
        setColor(Color::DEFAULT);
        return;
    }

    std::string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    try {
        if (std::filesystem::create_directory(path)) {
            std::cout << "Directory created successfully: " << path << std::endl;
        } else {
            std::cout << "Directory already exists or failed to create: " << path << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }
}

void AddFile(Arguments args, Options options) {
    if (args.empty()) {
        std::cout << "No file path provided." << std::endl;
        return;
    }

    // Concatenate all parts of the path into a single string
    std::string path;
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
        std::cout << "No file path provided." << std::endl;
        return;
    }

    // Concatenate all parts of the path into a single string
    std::string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    try {
        if (std::filesystem::remove(path)) {
            std::cout << "File removed successfully: " << path << std::endl;
        } else {
            std::cout << "Failed to remove file or file does not exist: " << path << std::endl;
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error removing file: " << e.what() << std::endl;
    }
}

void RemoveFolder(Arguments args, Options options) {
    if (args.empty()) {
        std::cout << "No folder path provided." << std::endl;
        return;
    }

    // Concatenate all parts of the path into a single string
    std::string path;
    for (const auto& part : args) {
        if (!path.empty()) {
            path += " ";
        }
        path += part;
    }

    try {
        if (std::filesystem::remove_all(path)) {
            std::cout << "Folder and its contents removed successfully: " << path << std::endl;
        } else {
            std::cout << "Failed to remove folder or folder does not exist: " << path << std::endl;
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

    const std::string& source = args[0];
    const std::string& destination = args[1];

    try {
        std::filesystem::copy(source, destination, std::filesystem::copy_options::overwrite_existing);
        std::filesystem::remove(source);
        std::cout << "File moved successfully." << std::endl;
    } catch (std::filesystem::filesystem_error& e) {
        std::cerr << "Error moving file: " << e.what() << std::endl;
    }
}

void FileCopy(Arguments args, Options options) {
    if (args.size() != 2) {
        std::cerr << "Usage: cp <source> <destination>" << std::endl;
        return;
    }

    const std::string& source = args[0];
    const std::string& destination = args[1];

    try {
        std::filesystem::copy(source, destination, std::filesystem::copy_options::overwrite_existing);
        std::cout << "File copied successfully." << std::endl;
    } catch (std::filesystem::filesystem_error& e) {
        std::cerr << "Error copying file: " << e.what() << std::endl;
    }
}