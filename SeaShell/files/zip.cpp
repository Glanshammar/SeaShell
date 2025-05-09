#include "zip.hpp"
#include <iostream>
#include <fstream>

void AddDirectoryToZip(Compress& zipper, const std::string& dirPath, const std::string& currentPath) {
    Poco::DirectoryIterator it(dirPath);
    Poco::DirectoryIterator end;

    while (it != end) {
        Path filePath(it.path());
        std::string relativePath = currentPath.empty() ? filePath.getFileName() : currentPath + "/" + filePath.getFileName();

        if (it->isDirectory()) {
            // Recursively add subdirectories
            AddDirectoryToZip(zipper, it.path().toString(), relativePath);
        } else {
            // Add file to the ZIP archive
            zipper.addFile(filePath, relativePath);
        }
        ++it;
    }
}

void ZIP(Arguments args, Options options) {
    if (args.size() != 2) {
        std::cerr << "Usage: zip <input file/folder> <output file>" << std::endl;
        return;
    }

    try {
        const std::string& source = args[0];
        const std::string& target = args[1];

        std::ofstream out(target, std::ios::binary);
        if (!out) {
            std::cerr << "Error: Cannot open output file." << std::endl;
            return;
        }

        // Create a Compress object with the output stream
        Poco::Zip::Compress zipper(out, true); // true for seekable output stream (local file)

        Poco::File sourceFile(source);
        if (sourceFile.isDirectory()) {
            // If the source is a directory, add all its contents recursively
            AddDirectoryToZip(zipper, source, "");
        } else {
            // If the source is a file, add it directly
            Poco::Path file(source);
            zipper.addFile(file, file.getFileName());
        }

        // Close the Compress object to finalize the ZIP file
        zipper.close();

        std::cout << "Compression completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
}

void UnZIP(Arguments args, Options options){
    if(args.size() != 2) {
        std::cerr << "Usage: unzip <input file> <output directory>" << std::endl;
        return;
    }

    const std::string& zipFilePath = args[0];
    const std::string& extractDir = args[1];

    try {
        // Open an input stream for the ZIP file (must be binary)
        std::ifstream inp(zipFilePath, std::ios::binary);
        if (!inp) {
            std::cerr << "Error: Cannot open input file." << std::endl;
            return;
        }

        // Create a Decompress object with the input stream and output directory
        Poco::Zip::Decompress dec(inp, extractDir);

        // Decompress all files from the ZIP archive
        dec.decompressAllFiles();

        std::cout << "Files decompressed successfully." << std::endl;
    } catch (const Poco::Exception& e) {
        std::cerr << "Error: " << e.displayText() << std::endl;
    }
}