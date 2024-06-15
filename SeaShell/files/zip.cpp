#include "zip.hpp"

void ZIP(Arguments args, Options options) {
    if(args.size() != 2) {
        std::cerr << "Usage: zip <input file> <output file>" << std::endl;
        return;
    }

    const string& source = args[0];
    const string& destination = args[1];

    // Create a new ZIP archive
    ZipArchive zf(destination);

    // Open the archive in write mode
    zf.open(libzippp::ZipArchive::New);

    // Add a file to the archive
    zf.addFile(source, source);

    // Close the archive
    zf.close();

    std::cout << "File compression completed." << std::endl;
}

void UnZIP(Arguments args, Options options){
    if(args.size() != 2) {
        std::cerr << "Usage: unzip <input file> <output directory>" << std::endl;
        return;
    }

    const string& zipFilePath = args[0];
    const string& extractDir = args[1];
}