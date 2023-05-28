#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

const char* decryptBuffer(const char* ciphertext, const char* key, const char* iv);