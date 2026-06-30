#include <iostream>
#include <vector>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/scrypt.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>

int main(int argc, char *argv[]) {
    // Get password from first command line argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <password>" << std::endl;
        return 1;
    }
    
    std::string password = argv[1];

    const size_t saltSize = 16; // 16 bytes salt
    // Generate a random salt
    CryptoPP::byte salt[saltSize];
    CryptoPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(salt, sizeof(salt));

    // Scrypt params
    const size_t N = 16384; // CPU/memory cost parameter (must be power of 2)
    const size_t r = 8;     // Block size parameter
    const size_t p = 1;     // Parallelisation parameter

    const size_t keyLength = 32; // Desired key length in bytes
    CryptoPP::byte derivedKey[keyLength];
    
    // Derive the key using scrypt
    CryptoPP::Scrypt scrypt;
    scrypt.DeriveKey(
            derivedKey, keyLength, reinterpret_cast<const CryptoPP::byte*>(password.data()), password.size(),
            salt, sizeof(salt),
            N, r, p
    );

    // Convert salt and hash from byte arrays to hex strings
    std::string saltHex, hashHex;
    CryptoPP::StringSource(salt, sizeof(salt), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(saltHex)));
    CryptoPP::StringSource(derivedKey, sizeof(derivedKey), true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashHex)));

    // Output the salt and hash
    std::cout << "Salt: " << saltHex << std::endl;
    std::cout << "Hash: " << hashHex << std::endl;

    return 0;
}
