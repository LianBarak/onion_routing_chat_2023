#pragma once
#include <openssl/evp.h>
#include <string>
#define MAX_CIPHERTEXT_SIZE 1024

const char* decryptBuffer(const char* ciphertext, const char* key, const char* iv);