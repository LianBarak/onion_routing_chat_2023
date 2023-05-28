#include "Rsa_function.h"

RSA* privateKeyFromConfig()
{

    Config cfg;
    cfg.readFile(CFG_PATH);

    string privateKey = cfg.lookup("rsa.private");

    RSA* rsa = NULL;
    const char* key = privateKey.c_str();
    BIO* keyBio = BIO_new_mem_buf((void*)key, -1);
    if (keyBio == NULL) {
        // handle error
        return NULL;
    }
    rsa = PEM_read_bio_RSAPrivateKey(keyBio, &rsa, NULL, NULL);
    BIO_free(keyBio);
    return rsa;
}
std::string decryptWithRSA(const char* cipherText)
{
    RSA* privateKey = privateKeyFromConfig();
    int keySize = RSA_size(privateKey);

    std::string decryptedMessage;
    decryptedMessage.resize(keySize);

    int decryptedLength = 0;
    const char* encryptedMessageBlock = cipherText;
    while (decryptedLength < keySize) {
        int result = RSA_private_decrypt(keySize, (const unsigned char*)encryptedMessageBlock, (unsigned char*)&decryptedMessage[decryptedLength], privateKey, RSA_PKCS1_PADDING);
        if (result == -1) {
            // handle error
            return "";
        }
        decryptedLength += result;
        encryptedMessageBlock += keySize;
    }
    decryptedMessage.resize(decryptedLength);
    return decryptedMessage;
}

/*
std::string encryptWithRsa(const char* plainText)
{
    RSA* publicKey = privateKeyFromConfig();

    int keySize = RSA_size(publicKey);
    int blockLength = keySize - 42;
    int messageLength = strlen(message);

    std::string encryptedMessage;
    encryptedMessage.resize(keySize);

    int encryptedLength = 0;
    const char* messageBlock = message;
    while (messageLength > 0) {
        int blockLengthUsed = (messageLength > blockLength) ? blockLength : messageLength;
        int result = RSA_public_encrypt(blockLengthUsed, (const unsigned char*)messageBlock, (unsigned char*)&encryptedMessage[encryptedLength], publicKey, RSA_PKCS1_PADDING);
        if (result == -1) {
            // handle error
            return "";
        }
        encryptedLength += result;
        messageBlock += blockLengthUsed;
        messageLength -= blockLengthUsed;
    }
    encryptedMessage.resize(encryptedLength);
    return encryptedMessage;
}*/
