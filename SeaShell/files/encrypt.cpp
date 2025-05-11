#include "encrypt.hpp"
#include <iostream>
#include <fstream>

void EncryptFile(const CommandArgs& args) {
    if (args.argCount() < 1) {
        std::cerr << "Usage: encrypt <filename> [passphrase]" << std::endl;
        return;
    }

    std::string filename = args.getArg(0);
    std::string passphrase = args.argCount() > 1 ? args.getArg(1) : "default";

    std::cout << "Encrypting file: " << filename << " with passphrase" << std::endl;
    // TODO: Implement actual encryption logic
}

void DecryptFile(const CommandArgs& args) {
    if (args.argCount() < 1) {
        std::cerr << "Usage: decrypt <filename> [passphrase]" << std::endl;
        return;
    }

    std::string filename = args.getArg(0);
    std::string passphrase = args.argCount() > 1 ? args.getArg(1) : "default";

    std::cout << "Decrypting file: " << filename << " with passphrase" << std::endl;
    // TODO: Implement actual decryption logic
}
