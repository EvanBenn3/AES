#include "aes_chain.h"
#include "keygen.h"
#include "block.h"

#include <stdlib.h>

unsigned int AES128_E(unsigned char* plaintext, unsigned int messageSize, unsigned char** ciphertext, unsigned int* key, AES_cipherMode mode) {
    int blockcount = messageSize / 16 + 1;
    int padcount = 16 - (messageSize % 16);

    if (mode == AES_ECB) {
        *ciphertext = realloc(*ciphertext, 16*blockcount);
        for (int i = 0; i < messageSize; i++) (*ciphertext)[i] = plaintext[i];
        for (int i = messageSize; i < blockcount * 16; i++) (*ciphertext)[i] = padcount;
        for (int i = 0; i < blockcount; i++) {
            BAES128(*ciphertext+16*i, key);
        }
    } else if (mode == AES_CBC) {
        blockcount++;
        *ciphertext = realloc(*ciphertext, 16*blockcount);
        for (int i = 0; i < messageSize; i++) (*ciphertext)[i+16] = plaintext[i];
        for (int i = messageSize; i < blockcount * 16 - 16; i++) (*ciphertext)[i+16] = padcount;
        for (int i = 1; i < blockcount; i++) {
            for (int j = 0; j < 16; j++) {
                (*ciphertext)[i*16+j] ^= (*ciphertext)[(i-1)*16+j];
            }
            BAES128(*ciphertext+16*i, key);
        }
    }

    return blockcount;
}

unsigned int AES192_E(unsigned char* plaintext, unsigned int messageSize, unsigned char** ciphertext, unsigned int* key, AES_cipherMode mode) {
    int blockcount = messageSize / 16 + 1;
    int padcount = 16 - (messageSize % 16);

    if (mode == AES_ECB) {
        *ciphertext = realloc(*ciphertext, 16*blockcount);
        for (int i = 0; i < messageSize; i++) (*ciphertext)[i] = plaintext[i];
        for (int i = messageSize; i < blockcount * 16; i++) (*ciphertext)[i] = padcount;
        for (int i = 0; i < blockcount; i++) {
            BAES192(*ciphertext+16*i, key);
        }
    } else if (mode == AES_CBC) {
        blockcount++;
        *ciphertext = realloc(*ciphertext, 16*blockcount);
        for (int i = 0; i < messageSize; i++) (*ciphertext)[i+16] = plaintext[i];
        for (int i = messageSize; i < blockcount * 16 - 16; i++) (*ciphertext)[i+16] = padcount;
        for (int i = 1; i < blockcount; i++) {
            for (int j = 0; j < 16; j++) {
                (*ciphertext)[i*16+j] ^= (*ciphertext)[(i-1)*16+j];
            }
            BAES192(*ciphertext+16*i, key);
        }
    }

    return blockcount;
}

unsigned int AES256_E(unsigned char* plaintext, unsigned int messageSize, unsigned char** ciphertext, unsigned int* key, AES_cipherMode mode) {
    int blockcount = messageSize / 16 + 1;
    int padcount = 16 - (messageSize % 16);

    if (mode == AES_ECB) {
        *ciphertext = realloc(*ciphertext, 16*blockcount);
        for (int i = 0; i < messageSize; i++) (*ciphertext)[i] = plaintext[i];
        for (int i = messageSize; i < blockcount * 16; i++) (*ciphertext)[i] = padcount;
        for (int i = 0; i < blockcount; i++) {
            BAES256(*ciphertext+16*i, key);
        }
    } else if (mode == AES_CBC) {
        blockcount++;
        *ciphertext = realloc(*ciphertext, 16*blockcount);
        for (int i = 0; i < messageSize; i++) (*ciphertext)[i+16] = plaintext[i];
        for (int i = messageSize; i < blockcount * 16 - 16; i++) (*ciphertext)[i+16] = padcount;
        for (int i = 1; i < blockcount; i++) {
            for (int j = 0; j < 16; j++) {
                (*ciphertext)[i*16+j] ^= (*ciphertext)[(i-1)*16+j];
            }
            BAES256(*ciphertext+16*i, key);
        }
    }

    return blockcount;
}

unsigned int AES128_D(unsigned char* ciphertext, unsigned int cipherSize, unsigned char** plaintext, unsigned int* key, AES_cipherMode mode) {
    int blockcount = cipherSize / 16;
    int padcount;
    unsigned int messageLength;

    if (mode == AES_ECB) {
        *plaintext = realloc(*plaintext, 16*blockcount);
        for (int i = 0; i < cipherSize; i++) (*plaintext)[i] = ciphertext[i];

        for (int i = 0; i < blockcount; i++) {
            BInvAES128(*plaintext+16*i, key);
        }

        padcount = (*plaintext)[cipherSize - 1];
        messageLength = cipherSize - padcount;
        *plaintext = realloc(*plaintext, messageLength);
    } else if (mode == AES_CBC) {
        *plaintext = realloc(*plaintext, 16*blockcount);
        for (int i = 0; i < cipherSize-16; i++) (*plaintext)[i] = ciphertext[i+16];
        for (int i = 0; i < blockcount; i++) {
            BInvAES128(*plaintext+16*i, key);
            for (int j = 0; j < 16; j++) {
                (*plaintext)[i*16+j] ^= ciphertext[(i)*16+j];
            }
        }
        padcount = (*plaintext)[cipherSize - 17];
        messageLength = cipherSize - padcount - 16;
        *plaintext = realloc(*plaintext, messageLength);
    }

    return messageLength;
}

unsigned int AES192_D(unsigned char* ciphertext, unsigned int cipherSize, unsigned char** plaintext, unsigned int* key, AES_cipherMode mode) {
    int blockcount = cipherSize / 16;
    int padcount;
    unsigned int messageLength;

    if (mode == AES_ECB) {
        *plaintext = realloc(*plaintext, 16*blockcount);
        for (int i = 0; i < cipherSize; i++) (*plaintext)[i] = ciphertext[i];

        for (int i = 0; i < blockcount; i++) {
            BInvAES192(*plaintext+16*i, key);
        }

        padcount = (*plaintext)[cipherSize - 1];
        messageLength = cipherSize - padcount;
        *plaintext = realloc(*plaintext, messageLength);
    } else if (mode == AES_CBC) {
        *plaintext = realloc(*plaintext, 16*blockcount);
        for (int i = 0; i < cipherSize-16; i++) (*plaintext)[i] = ciphertext[i+16];
        for (int i = 0; i < blockcount; i++) {
            BInvAES192(*plaintext+16*i, key);
            for (int j = 0; j < 16; j++) {
                (*plaintext)[i*16+j] ^= ciphertext[(i)*16+j];
            }
        }
        padcount = (*plaintext)[cipherSize - 17];
        messageLength = cipherSize - padcount - 16;
        *plaintext = realloc(*plaintext, messageLength);
    }

    return messageLength;
}

unsigned int AES256_D(unsigned char* ciphertext, unsigned int cipherSize, unsigned char** plaintext, unsigned int* key, AES_cipherMode mode) {
    int blockcount = cipherSize / 16;
    int padcount;
    unsigned int messageLength;

    if (mode == AES_ECB) {
        *plaintext = realloc(*plaintext, 16*blockcount);
        for (int i = 0; i < cipherSize; i++) (*plaintext)[i] = ciphertext[i];

        for (int i = 0; i < blockcount; i++) {
            BInvAES256(*plaintext+16*i, key);
        }

        padcount = (*plaintext)[cipherSize - 1];
        messageLength = cipherSize - padcount;
        *plaintext = realloc(*plaintext, messageLength);
    } else if (mode == AES_CBC) {
        *plaintext = realloc(*plaintext, 16*blockcount);
        for (int i = 0; i < cipherSize-16; i++) (*plaintext)[i] = ciphertext[i+16];
        for (int i = 0; i < blockcount; i++) {
            BInvAES256(*plaintext+16*i, key);
            for (int j = 0; j < 16; j++) {
                (*plaintext)[i*16+j] ^= ciphertext[(i)*16+j];
            }
        }
        padcount = (*plaintext)[cipherSize - 17];
        messageLength = cipherSize - padcount - 16;
        *plaintext = realloc(*plaintext, messageLength);
    }

    return messageLength;
}