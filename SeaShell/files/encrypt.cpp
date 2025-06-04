#include "encrypt.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Generate key from passphrase using SHA-256
void deriveKeyFromPassword(const string& passphrase, unsigned char* key, int keyLength) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(mdctx, passphrase.c_str(), passphrase.size());
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;
    EVP_DigestFinal_ex(mdctx, hash, &hashLen);
    EVP_MD_CTX_free(mdctx);
    
    // Copy the hash to the key (truncate or zero-pad as needed)
    memcpy(key, hash, static_cast<unsigned int>(keyLength) < hashLen ? static_cast<unsigned int>(keyLength) : hashLen);
}

// Encrypts data using AES-256-CBC
bool aesEncrypt(const string& passphrase, 
                const vector<unsigned char>& data,
                vector<unsigned char>& encrypted) {
    // Generate a key from passphrase
    unsigned char key[32]; // 256 bits
    deriveKeyFromPassword(passphrase, key, sizeof(key));
    
    // Generate random IV
    unsigned char iv[16]; // 128 bits
    if (RAND_bytes(iv, sizeof(iv)) != 1) {
        cerr << "Error generating random IV" << endl;
        return false;
    }
    
    // Initialize encryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Error creating cipher context" << endl;
        return false;
    }
    
    // Initialize encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1) {
        cerr << "Error initializing encryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    
    // Reserve space for encrypted data + IV (16 bytes)
    encrypted.resize(data.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()) + 16);
    
    // Copy IV to first 16 bytes
    memcpy(encrypted.data(), iv, 16);
    
    // Encrypt data
    int outlen;
    if (EVP_EncryptUpdate(ctx, encrypted.data() + 16, &outlen, data.data(), data.size()) != 1) {
        cerr << "Error during encryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    
    int total_len = outlen;
    
    // Finalize encryption
    if (EVP_EncryptFinal_ex(ctx, encrypted.data() + 16 + outlen, &outlen) != 1) {
        cerr << "Error finalizing encryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    
    total_len += outlen;
    encrypted.resize(total_len + 16); // Final size: IV + encrypted data
    
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

// Decrypts data using AES-256-CBC
bool aesDecrypt(const string& passphrase, 
                const vector<unsigned char>& encrypted,
                vector<unsigned char>& decrypted) {
    // Extract IV from first 16 bytes
    if (encrypted.size() <= 16) {
        cerr << "Encrypted data too short" << endl;
        return false;
    }
    
    unsigned char iv[16];
    memcpy(iv, encrypted.data(), 16);
    
    // Generate key from passphrase
    unsigned char key[32]; // 256 bits
    deriveKeyFromPassword(passphrase, key, sizeof(key));
    
    // Initialize decryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        cerr << "Error creating cipher context" << endl;
        return false;
    }
    
    // Initialize decryption operation
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1) {
        cerr << "Error initializing decryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    
    // Reserve space for decrypted data (will be smaller than encrypted due to padding)
    decrypted.resize(encrypted.size());
    
    // Decrypt data (skip IV)
    int outlen;
    if (EVP_DecryptUpdate(ctx, decrypted.data(), &outlen, 
                          encrypted.data() + 16, encrypted.size() - 16) != 1) {
        cerr << "Error during decryption" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    
    int total_len = outlen;
    
    // Finalize decryption
    if (EVP_DecryptFinal_ex(ctx, decrypted.data() + outlen, &outlen) != 1) {
        cerr << "Error finalizing decryption. Wrong passphrase?" << endl;
        EVP_CIPHER_CTX_free(ctx);
        return false;
    }
    
    total_len += outlen;
    decrypted.resize(total_len);
    
    EVP_CIPHER_CTX_free(ctx);
    return true;
}

void EncryptFile(const CommandArgs& args) {
    if (args.argCount() < 1) {
        cerr << "Usage: encrypt <filename> [passphrase] [output_filename]" << endl;
        return;
    }

    string inputFile = args.getArg(0);
    string passphrase = args.argCount() > 1 ? args.getArg(1) : "default";
    string outputFile = args.argCount() > 2 ? args.getArg(2) : inputFile + ".enc";

    // Read input file
    ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open input file: " << inputFile << endl;
        return;
    }

    vector<unsigned char> data(
        (std::istreambuf_iterator<char>(inFile)),
        std::istreambuf_iterator<char>()
    );
    inFile.close();

    // Encrypt data
    vector<unsigned char> encrypted;
    if (!aesEncrypt(passphrase, data, encrypted)) {
        cerr << "Encryption failed" << endl;
        return;
    }

    // Write encrypted data to output file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot open output file: " << outputFile << endl;
        return;
    }
    
    outFile.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
    outFile.close();

    cout << "File encrypted successfully: " << outputFile << endl;
}

void DecryptFile(const CommandArgs& args) {
    if (args.argCount() < 1) {
        cerr << "Usage: decrypt <filename> [passphrase] [output_filename]" << endl;
        return;
    }

    string inputFile = args.getArg(0);
    string passphrase = args.argCount() > 1 ? args.getArg(1) : "default";
    string outputFile = args.argCount() > 2 ? args.getArg(2) : inputFile + ".dec";

    // Read encrypted file
    std::ifstream inFile(inputFile, std::ios::binary);
    if (!inFile) {
        cerr << "Error: Cannot open input file: " << inputFile << endl;
        return;
    }

    vector<unsigned char> encrypted(
        (std::istreambuf_iterator<char>(inFile)),
        std::istreambuf_iterator<char>()
    );
    inFile.close();

    // Decrypt data
    vector<unsigned char> decrypted;
    if (!aesDecrypt(passphrase, encrypted, decrypted)) {
        cerr << "Decryption failed" << endl;
        return;
    }

    // Write decrypted data to output file
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile) {
        cerr << "Error: Cannot open output file: " << outputFile << endl;
        return;
    }
    
    outFile.write(reinterpret_cast<const char*>(decrypted.data()), decrypted.size());
    outFile.close();

    std::cout << "File decrypted successfully: " << outputFile << std::endl;
}
