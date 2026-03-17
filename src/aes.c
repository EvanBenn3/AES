#include "aes.h"
#include "aes_chain.h"
#include "keygen.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

static bool srand_init = false;

void AES_dataInit(AES_DATA* data) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    data->ciphertext = NULL;
    data->plaintext = NULL;
    data->ciphertextSize = 0;
    data->plaintextSize = 0;
}

void AES_dataDestroy(AES_DATA* data) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    free(data->ciphertext); data->ciphertext = NULL;
    free(data->plaintext); data->plaintext = NULL;
    data->plaintextSize = 0;
    data->ciphertextSize = 0;
}

void AES_plainInsert(AES_DATA* data, const unsigned char* byteData, unsigned int byteLength) {
    unsigned char* tmp;
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    if (!byteData) {
        fprintf(stderr, "Error, byteData is NULL!");
        return;
    }
    if (byteLength == 0) {
        fprintf(stderr, "Error, zero-length insert!");
        return;
    }

    tmp = realloc(data->plaintext, byteLength);
    if (!tmp) {
        fprintf(stderr, "Error, realloc failed!");
        return;
    }
    data->plaintext = tmp;

    for (int i = 0; i < byteLength; i++) {
        data->plaintext[i] = byteData[i];
    }
    data->plaintextSize = byteLength;
    
}

void AES_cipherInsert(AES_DATA* data, const unsigned char* byteData, unsigned int byteLength) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    if (!byteData) {
        fprintf(stderr, "Error, byteData is NULL!");
        return;
    }
    if (byteLength == 0) {
        fprintf(stderr, "Error, zero-length insert!");
        return;
    }

    if ((byteLength & 15) != 0) {
        fprintf(stderr, "Error, byteLength is misalinged!");
        return;
    }
    
    unsigned char* tmp;
    tmp = realloc(data->ciphertext, byteLength);
    if (!tmp) {
        fprintf(stderr, "Error, realloc failed!");
        return;
    }
    data->ciphertext = tmp;

    for (int i = 0; i < byteLength; i++) {
        data->ciphertext[i] = byteData[i];
    }
    
    data->ciphertextSize = byteLength;
}

static void AES_randomizeIV(AES_DATA* data) {
    if (!srand_init) {
        srand(time(NULL));
        srand_init = true;
    }

    unsigned char* tmp;
    tmp = realloc(data->ciphertext, 16);
    if (!tmp) {
        fprintf(stderr, "Error, realloc failed!");
        return;
    }
    data->ciphertext = tmp;
    data->ciphertextSize = 16;

    for (int i = 0; i < 16; i++) {
        data->ciphertext[i] = rand() & 0xff;
    }
}

void AES_insertIV(AES_DATA* data, const unsigned char* IV) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }

    unsigned char* tmp;
    tmp = realloc(data->ciphertext, 16);
    if (!tmp) {
        fprintf(stderr, "Error, realloc failed!");
        return;
    }
    data->ciphertext = tmp;
    data->ciphertextSize = 16;

    for (int i = 0; i < 16; i++) {
        data->ciphertext[i] = IV[i];
    }
}

void AES_genkey(AES_CTX* key, const unsigned int* keyWords, AES_TYPE type) {
    if (!key) {
        fprintf(stderr, "Error, key is NULL!");
        return;
    }
    if (type > 2) {
        fprintf(stderr, "Error, type is invalid!");
        return;
    }
    key->type = type;
    if (type == AES_128) {
        for (int i = 0; i < 4; i++) key->key[i] = keyWords[i];
        roundKeyGen128(key->key);
    } else if (type == AES_192) {
        for (int i = 0; i < 6; i++) key->key[i] = keyWords[i];
        roundKeyGen192(key->key);
    } else if (type == AES_256) {
        for (int i = 0; i < 8; i++) key->key[i] = keyWords[i];
        roundKeyGen256(key->key);
    }
}

void AES_encrypt(AES_DATA* data, AES_CTX key, AES_cipherMode mode) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    if (!data->plaintext) {
        fprintf(stderr, "Error, plaintext is NULL!");
        return;
    }
    if (data->plaintextSize == 0) {
        fprintf(stderr, "Error, plaintextSize is 0!");
        return;
    }
    if (mode > 2) {
        fprintf(stderr, "Error, mode is invalid!");
        return;
    }

    if (mode == AES_CBC && data->ciphertextSize == 0) {
        AES_randomizeIV(data);
    }

    if (key.type == AES_128) {
        data->ciphertextSize = 16*AES128_E(data->plaintext, data->plaintextSize, &data->ciphertext, key.key, mode);
    } else if (key.type == AES_192) {
        data->ciphertextSize = 16*AES192_E(data->plaintext, data->plaintextSize, &data->ciphertext, key.key, mode);
    } else if (key.type == AES_256) {
        data->ciphertextSize = 16*AES256_E(data->plaintext, data->plaintextSize, &data->ciphertext, key.key, mode);
    }
}

void AES_decrypt(AES_DATA* data, AES_CTX key, AES_cipherMode mode) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    if (!data->ciphertext) {
        fprintf(stderr, "Error, ciphertext is NULL!");
        return;
    }
    if (data->ciphertextSize == 0) {
        fprintf(stderr, "Error, ciphertextSize is 0!");
        return;
    }
    if (mode > 2) {
        fprintf(stderr, "Error, mode is invalid!");
        return;
    }

    if (key.type == AES_128) {
        data->plaintextSize = AES128_D(data->ciphertext, data->ciphertextSize, &data->plaintext, key.key, mode);
    } else if (key.type == AES_192) {
        data->plaintextSize = AES192_D(data->ciphertext, data->ciphertextSize, &data->plaintext, key.key, mode);
    } else if (key.type == AES_256) {
        data->plaintextSize = AES256_D(data->ciphertext, data->ciphertextSize, &data->plaintext, key.key, mode);
    }
}

void AES_extractplain(AES_DATA* data, unsigned char* byteData) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    if (!byteData) {
        fprintf(stderr, "Error, byteData is NULL!");
        return;
    }

    for (int i = 0; i < data->plaintextSize; i++) {
        byteData[i] = data->plaintext[i];
    }
}

void AES_extractcipher(AES_DATA* data, unsigned char* byteData) {
    if (!data) {
        fprintf(stderr, "Error, data is NULL!");
        return;
    }
    if (!byteData) {
        fprintf(stderr, "Error, byteData is NULL!");
        return;
    }

    for (int i = 0; i < data->ciphertextSize; i++) {
        byteData[i] = data->ciphertext[i];
    }
}