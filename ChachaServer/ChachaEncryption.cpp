#include "ChachaEncryption.h"

const char* decryptBuffer(const char* ciphertext, const char* key, const char* iv)
{
    // Set up the decryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CIPHER_CTX_set_padding(ctx, 0);
    EVP_DecryptInit_ex(ctx, EVP_chacha20(), NULL, NULL, NULL);
    EVP_CIPHER_CTX_set_key_length(ctx, 32);
    EVP_DecryptInit_ex(ctx, NULL, NULL, (const unsigned char*)key, (const unsigned char*)iv);

    // Perform the decryption
    int ciphertext_len = strlen(ciphertext);
    int outlen, totlen = 0;
    char* plaintext = new char[ciphertext_len];
    EVP_DecryptUpdate(ctx, (unsigned char*)plaintext, &outlen, (const unsigned char*)ciphertext, ciphertext_len);
    totlen += outlen;
    EVP_DecryptFinal_ex(ctx, (unsigned char*)(plaintext + totlen), &outlen);
    totlen += outlen;

    // Clean up and return the plaintext
    EVP_CIPHER_CTX_free(ctx);
    std::string result(plaintext, totlen);
    delete[] plaintext;
    return result.c_str();
}
