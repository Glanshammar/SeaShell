#include "zip.hpp"


void ZIP(Arguments args, Options options) {
    if (args.size() != 2) {
        std::cerr << "Usage: zip <input file/folder> <output file>" << std::endl;
        return;
    }

    try{
        const string& source = args[0];
        const string& target = args[1];

        std::ofstream out(target, std::ios::binary);

        // Create a Compress object with the output stream
        Compress zipper(out, true); // true for seekable output stream (local file)

        // Add a single file to the ZIP archive
        Path file(source);
        zipper.addFile(file, source);

        // Close the Compress object to finalize the ZIP file
        zipper.close();

        cout << "File compressed successfully." << std::endl;
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

    const string& zipFilePath = args[0];
    const string& extractDir = args[1];

    try {
        // Open an input stream for the ZIP file (must be binary)
        std::ifstream inp(zipFilePath, std::ios::binary);
        poco_assert(inp);

        // Create a Decompress object with the input stream and output directory
        Decompress dec(inp, extractDir);

        // Decompress all files from the ZIP archive
        dec.decompressAllFiles();

        cout << "Files decompressed successfully." << std::endl;
    } catch (const Poco::Exception& e) {
        std::cerr << "Error: " << e.displayText() << std::endl;
    }
}