#include "block.h"
#include "galois.h"
#include "constants.h"

void BAES128(unsigned char* block, unsigned int* roundKeys) {
    unsigned char temp[16];

    for (int i = 0; i < 4; i++) {
        block[i*4] ^= roundKeys[i] >> 24;
        block[i*4+1] ^= (roundKeys[i] >> 16) & 0xff;
        block[i*4+2] ^= (roundKeys[i] >> 8) & 0xff;
        block[i*4+3] ^= roundKeys[i] & 0xff;
    }

    for (int j = 1; j <= 10; j++) {
        for (int i = 0; i < 16; i++) {
            block[i] = sbox[block[i]];
        }

        for (int i = 0; i < 16; i++) {
            temp[i] = block[(i + 4 * (i % 4)) % 16];
        }
        for (int i = 0; i < 16; i++) {
            block[i] = temp[i];
        }

        if (j != 10) {
            for (int i = 0; i < 4; i++) {
                temp[i*4] = mul2(block[i*4]) ^ mul3(block[i*4+1]) ^ block[i*4+2] ^ block[i*4+3];
                temp[i*4+1] = block[i*4] ^ mul2(block[i*4+1]) ^ mul3(block[i*4+2]) ^ block[i*4+3];
                temp[i*4+2] = block[i*4] ^ block[i*4+1] ^ mul2(block[i*4+2]) ^ mul3(block[i*4+3]);
                temp[i*4+3] = mul3(block[i*4]) ^ block[i*4+1] ^ block[i*4+2] ^ mul2(block[i*4+3]);
            }
            for (int i = 0; i < 16; i++) {
                block[i] = temp[i];
            }
        }

        for (int i = 0; i < 4; i++) {
            block[i*4] ^= roundKeys[i+j*4] >> 24;
            block[i*4+1] ^= (roundKeys[i+j*4] >> 16) & 0xff;
            block[i*4+2] ^= (roundKeys[i+j*4] >> 8) & 0xff;
            block[i*4+3] ^= roundKeys[i+j*4] & 0xff;
        }

    }
}

void BAES192(unsigned char* block, unsigned int* roundKeys) {
    unsigned char temp[16];

    for (int i = 0; i < 4; i++) {
        block[i*4] ^= roundKeys[i] >> 24;
        block[i*4+1] ^= (roundKeys[i] >> 16) & 0xff;
        block[i*4+2] ^= (roundKeys[i] >> 8) & 0xff;
        block[i*4+3] ^= roundKeys[i] & 0xff;
    }

    for (int j = 1; j <= 12; j++) {
        for (int i = 0; i < 16; i++) {
            block[i] = sbox[block[i]];
        }

        for (int i = 0; i < 16; i++) {
            temp[i] = block[(i + 4 * (i % 4)) % 16];
        }
        for (int i = 0; i < 16; i++) {
            block[i] = temp[i];
        }

        if (j != 12) {
            for (int i = 0; i < 4; i++) {
                temp[i*4] = mul2(block[i*4]) ^ mul3(block[i*4+1]) ^ block[i*4+2] ^ block[i*4+3];
                temp[i*4+1] = block[i*4] ^ mul2(block[i*4+1]) ^ mul3(block[i*4+2]) ^ block[i*4+3];
                temp[i*4+2] = block[i*4] ^ block[i*4+1] ^ mul2(block[i*4+2]) ^ mul3(block[i*4+3]);
                temp[i*4+3] = mul3(block[i*4]) ^ block[i*4+1] ^ block[i*4+2] ^ mul2(block[i*4+3]);
            }
            for (int i = 0; i < 16; i++) {
                block[i] = temp[i];
            }
        }

        for (int i = 0; i < 4; i++) {
            block[i*4] ^= roundKeys[i+j*4] >> 24;
            block[i*4+1] ^= (roundKeys[i+j*4] >> 16) & 0xff;
            block[i*4+2] ^= (roundKeys[i+j*4] >> 8) & 0xff;
            block[i*4+3] ^= roundKeys[i+j*4] & 0xff;
        }

    }
}

void BAES256(unsigned char* block, unsigned int* roundKeys) {
    unsigned char temp[16];

    for (int i = 0; i < 4; i++) {
        block[i*4] ^= roundKeys[i] >> 24;
        block[i*4+1] ^= (roundKeys[i] >> 16) & 0xff;
        block[i*4+2] ^= (roundKeys[i] >> 8) & 0xff;
        block[i*4+3] ^= roundKeys[i] & 0xff;
    }

    for (int j = 1; j <= 14; j++) {
        for (int i = 0; i < 16; i++) {
            block[i] = sbox[block[i]];
        }

        for (int i = 0; i < 16; i++) {
            temp[i] = block[(i + 4 * (i % 4)) % 16];
        }
        for (int i = 0; i < 16; i++) {
            block[i] = temp[i];
        }

        if (j != 14) {
            for (int i = 0; i < 4; i++) {
                temp[i*4] = mul2(block[i*4]) ^ mul3(block[i*4+1]) ^ block[i*4+2] ^ block[i*4+3];
                temp[i*4+1] = block[i*4] ^ mul2(block[i*4+1]) ^ mul3(block[i*4+2]) ^ block[i*4+3];
                temp[i*4+2] = block[i*4] ^ block[i*4+1] ^ mul2(block[i*4+2]) ^ mul3(block[i*4+3]);
                temp[i*4+3] = mul3(block[i*4]) ^ block[i*4+1] ^ block[i*4+2] ^ mul2(block[i*4+3]);
            }
            for (int i = 0; i < 16; i++) {
                block[i] = temp[i];
            }
        }

        for (int i = 0; i < 4; i++) {
            block[i*4] ^= roundKeys[i+j*4] >> 24;
            block[i*4+1] ^= (roundKeys[i+j*4] >> 16) & 0xff;
            block[i*4+2] ^= (roundKeys[i+j*4] >> 8) & 0xff;
            block[i*4+3] ^= roundKeys[i+j*4] & 0xff;
        }

    }
}

void BInvAES128(unsigned char* block, unsigned int* roundKeys) {
    unsigned char temp[16];
    for (int j = 10; j >= 1; j--) {
        for (int i = 0; i < 4; i++) {
            block[i*4] ^= roundKeys[i+j*4] >> 24;
            block[i*4+1] ^= (roundKeys[i+j*4] >> 16) & 0xff;
            block[i*4+2] ^= (roundKeys[i+j*4] >> 8) & 0xff;
            block[i*4+3] ^= roundKeys[i+j*4] & 0xff;
        }
        
        if (j != 10) {
            for (int i = 0; i < 4; i++) {
                temp[i*4] = mul14(block[i*4]) ^ mul11(block[i*4+1]) ^ mul13(block[i*4+2]) ^ mul9(block[i*4+3]);
                temp[i*4+1] = mul9(block[i*4]) ^ mul14(block[i*4+1]) ^ mul11(block[i*4+2]) ^ mul13(block[i*4+3]);
                temp[i*4+2] = mul13(block[i*4]) ^ mul9(block[i*4+1]) ^ mul14(block[i*4+2]) ^ mul11(block[i*4+3]);
                temp[i*4+3] = mul11(block[i*4]) ^ mul13(block[i*4+1]) ^ mul9(block[i*4+2]) ^ mul14(block[i*4+3]);
            }
            for (int i = 0; i < 16; i++) {
                block[i] = temp[i];
            }
        }

        for (int i = 0; i < 16; i++) {
            temp[i] = block[(i - 4 * (i % 4) + 16) % 16];
        }
        for (int i = 0; i < 16; i++) {
            block[i] = temp[i];
        }

        for (int i = 0; i < 16; i++) {
            block[i] = sboxInv[block[i]];
        }
    }

    for (int i = 0; i < 4; i++) {
        block[i*4] ^= roundKeys[i] >> 24;
        block[i*4+1] ^= (roundKeys[i] >> 16) & 0xff;
        block[i*4+2] ^= (roundKeys[i] >> 8) & 0xff;
        block[i*4+3] ^= roundKeys[i] & 0xff;
    }
}

void BInvAES192(unsigned char* block, unsigned int* roundKeys) {
    unsigned char temp[16];
    for (int j = 12; j >= 1; j--) {
        for (int i = 0; i < 4; i++) {
            block[i*4] ^= roundKeys[i+j*4] >> 24;
            block[i*4+1] ^= (roundKeys[i+j*4] >> 16) & 0xff;
            block[i*4+2] ^= (roundKeys[i+j*4] >> 8) & 0xff;
            block[i*4+3] ^= roundKeys[i+j*4] & 0xff;
        }
        
        if (j != 12) {
            for (int i = 0; i < 4; i++) {
                temp[i*4] = mul14(block[i*4]) ^ mul11(block[i*4+1]) ^ mul13(block[i*4+2]) ^ mul9(block[i*4+3]);
                temp[i*4+1] = mul9(block[i*4]) ^ mul14(block[i*4+1]) ^ mul11(block[i*4+2]) ^ mul13(block[i*4+3]);
                temp[i*4+2] = mul13(block[i*4]) ^ mul9(block[i*4+1]) ^ mul14(block[i*4+2]) ^ mul11(block[i*4+3]);
                temp[i*4+3] = mul11(block[i*4]) ^ mul13(block[i*4+1]) ^ mul9(block[i*4+2]) ^ mul14(block[i*4+3]);
            }
            for (int i = 0; i < 16; i++) {
                block[i] = temp[i];
            }
        }

        for (int i = 0; i < 16; i++) {
            temp[i] = block[(i - 4 * (i % 4) + 16) % 16];
        }
        for (int i = 0; i < 16; i++) {
            block[i] = temp[i];
        }

        for (int i = 0; i < 16; i++) {
            block[i] = sboxInv[block[i]];
        }
    }

    for (int i = 0; i < 4; i++) {
        block[i*4] ^= roundKeys[i] >> 24;
        block[i*4+1] ^= (roundKeys[i] >> 16) & 0xff;
        block[i*4+2] ^= (roundKeys[i] >> 8) & 0xff;
        block[i*4+3] ^= roundKeys[i] & 0xff;
    }
}

void BInvAES256(unsigned char* block, unsigned int* roundKeys) {
    unsigned char temp[16];
    for (int j = 14; j >= 1; j--) {
        for (int i = 0; i < 4; i++) {
            block[i*4] ^= roundKeys[i+j*4] >> 24;
            block[i*4+1] ^= (roundKeys[i+j*4] >> 16) & 0xff;
            block[i*4+2] ^= (roundKeys[i+j*4] >> 8) & 0xff;
            block[i*4+3] ^= roundKeys[i+j*4] & 0xff;
        }
        
        if (j != 14) {
            for (int i = 0; i < 4; i++) {
                temp[i*4] = mul14(block[i*4]) ^ mul11(block[i*4+1]) ^ mul13(block[i*4+2]) ^ mul9(block[i*4+3]);
                temp[i*4+1] = mul9(block[i*4]) ^ mul14(block[i*4+1]) ^ mul11(block[i*4+2]) ^ mul13(block[i*4+3]);
                temp[i*4+2] = mul13(block[i*4]) ^ mul9(block[i*4+1]) ^ mul14(block[i*4+2]) ^ mul11(block[i*4+3]);
                temp[i*4+3] = mul11(block[i*4]) ^ mul13(block[i*4+1]) ^ mul9(block[i*4+2]) ^ mul14(block[i*4+3]);
            }
            for (int i = 0; i < 16; i++) {
                block[i] = temp[i];
            }
        }

        for (int i = 0; i < 16; i++) {
            temp[i] = block[(i - 4 * (i % 4) + 16) % 16];
        }
        for (int i = 0; i < 16; i++) {
            block[i] = temp[i];
        }

        for (int i = 0; i < 16; i++) {
            block[i] = sboxInv[block[i]];
        }
    }

    for (int i = 0; i < 4; i++) {
        block[i*4] ^= roundKeys[i] >> 24;
        block[i*4+1] ^= (roundKeys[i] >> 16) & 0xff;
        block[i*4+2] ^= (roundKeys[i] >> 8) & 0xff;
        block[i*4+3] ^= roundKeys[i] & 0xff;
    }
}