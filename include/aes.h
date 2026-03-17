#ifndef AES_H
#define AES_H

#include "cipherMode.h"

typedef enum {
    AES_128, AES_192, AES_256
} AES_TYPE;

typedef struct {
    unsigned int key[60];
    AES_TYPE type;
} AES_CTX;

typedef struct {
    unsigned char* plaintext;
    unsigned char* ciphertext;
    unsigned int plaintextSize;
    unsigned int ciphertextSize;
} AES_DATA;

void AES_dataInit(AES_DATA* data);
void AES_dataDestroy(AES_DATA* data);
void AES_plainInsert(AES_DATA* data, const unsigned char* byteData, unsigned int byteLength);
void AES_cipherInsert(AES_DATA* data, const unsigned char* byteData, unsigned int byteLength);
void AES_insertIV(AES_DATA* data, const unsigned char* IV);
void AES_genkey(AES_CTX* key, const unsigned int* keyWords, AES_TYPE type);
void AES_encrypt(AES_DATA* data, AES_CTX key, AES_cipherMode mode);
void AES_decrypt(AES_DATA* data, AES_CTX key, AES_cipherMode mode);
void AES_extractplain(AES_DATA* data, unsigned char* byteData);
void AES_extractcipher(AES_DATA* data, unsigned char* byteData);

#endif