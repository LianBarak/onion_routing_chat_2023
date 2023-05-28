#include "AesDecryption.h"

const char* decryptBuffer(const char* ciphertext, const char* key, const char* iv)
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    const EVP_CIPHER* cipher = EVP_aes_256_cbc(); // Use AES-256 in CBC mode
    const int key_length = EVP_CIPHER_key_length(cipher);
    const int iv_length = EVP_CIPHER_iv_length(cipher);
    unsigned char decrypted[MAX_CIPHERTEXT_SIZE + 1] = { 0 };
    int len;
    int plaintext_len;

    // Initialize the decryption context
    EVP_DecryptInit_ex(ctx, cipher, nullptr, reinterpret_cast<const unsigned char*>(key), reinterpret_cast<const unsigned char*>(iv));

    // Decrypt the ciphertext
    EVP_DecryptUpdate(ctx, decrypted, &len, reinterpret_cast<const unsigned char*>(ciphertext), strlen(ciphertext));
    plaintext_len = len;

    // Finalize the decryption
    EVP_DecryptFinal_ex(ctx, decrypted + len, &len);
    plaintext_len += len;

    // Clean up the context
    EVP_CIPHER_CTX_free(ctx);

    // Convert the decrypted plaintext to a string and return it
    return reinterpret_cast<const char*>(decrypted);
}
