#include <iostream>
#include <vector>
#include <string>
#include <cryptopp/cryptlib.h>
#include <cryptopp/scrypt.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <sqlite3.h>

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

    // Open SQLite database
    // Create if does not exist
    sqlite3 *db;
    int rc = sqlite3_open("passwords.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }
    const char* schema = "CREATE TABLE IF NOT EXISTS passwords (id INTEGER PRIMARY KEY AUTOINCREMENT, salt TEXT NOT NULL, hash TEXT NOT NULL);";
    if (sqlite3_exec(db, schema, 0, 0, 0) != SQLITE_OK) {
        std::cerr << "Can't create table: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Insert salt and hash into database
    sqlite3_stmt *stmt;
    const char* insertSQL = "INSERT INTO passwords (salt, hash) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, saltHex.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashHex.c_str(), -1, SQLITE_STATIC);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Can't execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    // Finalise the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
