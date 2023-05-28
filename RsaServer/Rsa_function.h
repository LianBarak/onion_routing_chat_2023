#ifndef RSA_FUNCTIONS_H
#define RSA_FUNCTION_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <string>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;

#define CFG_PATH "config.ini"

RSA* privateKeyFromConfig();
std::string decryptWithRSA(const char* cipherText);

#endif