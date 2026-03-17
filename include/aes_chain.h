#ifndef AES_CHAIN_H
#define AES_CHAIN_H

#include "cipherMode.h"

unsigned int AES128_E(unsigned char* plaintext, unsigned int messageSize, unsigned char** ciphertext, unsigned int* key, AES_cipherMode mode);
unsigned int AES192_E(unsigned char* plaintext, unsigned int messageSize, unsigned char** ciphertext, unsigned int* key, AES_cipherMode mode);
unsigned int AES256_E(unsigned char* plaintext, unsigned int messageSize, unsigned char** ciphertext, unsigned int* key, AES_cipherMode mode);

unsigned int AES128_D(unsigned char* ciphertext, unsigned int cipherSize, unsigned char** plaintext, unsigned int* key, AES_cipherMode mode);
unsigned int AES192_D(unsigned char* ciphertext, unsigned int cipherSize, unsigned char** plaintext, unsigned int* key, AES_cipherMode mode);
unsigned int AES256_D(unsigned char* ciphertext, unsigned int cipherSize, unsigned char** plaintext, unsigned int* key, AES_cipherMode mode);

#endif