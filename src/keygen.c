#include "keygen.h"
#include "galois.h"
#include "constants.h"

void roundKeyGen128(unsigned int* roundKeys) {
    unsigned int temp;
    for (int i = 4; i < 44; i++) {
        temp = roundKeys[i-1];
        if (i % 4 == 0) {
            temp = (temp << 8) | (temp >> 24);
            temp = (sbox[(temp >> 24) & 0xff] << 24) |
                            (sbox[(temp >> 16) & 0xff] << 16) |
                            (sbox[(temp >> 8) & 0xff] << 8) |
                            (sbox[temp & 0xff]);
            temp ^= (computeRCON(i/4) << 24);
        }
        roundKeys[i] = temp ^ roundKeys[i-4];
    }
}

void roundKeyGen192(unsigned int* roundKeys) {
    unsigned int temp;
    for (int i = 6; i < 52; i++) {
        temp = roundKeys[i-1];
        if (i % 6 == 0) {
            temp = (temp << 8) | (temp >> 24);
            temp = (sbox[(temp >> 24) & 0xff] << 24) |
                            (sbox[(temp >> 16) & 0xff] << 16) |
                            (sbox[(temp >> 8) & 0xff] << 8) |
                            (sbox[temp & 0xff]);
            temp ^= (computeRCON(i/4) << 24);
        }
        roundKeys[i] = temp ^ roundKeys[i-6];
    }
}

void roundKeyGen256(unsigned int* roundKeys) {
    unsigned int temp;
    for (int i = 8; i < 60; i++) {
        temp = roundKeys[i-1];
        if (i % 8 == 0) {
            temp = (temp << 8) | (temp >> 24);
            temp = (sbox[(temp >> 24) & 0xff] << 24) |
                            (sbox[(temp >> 16) & 0xff] << 16) |
                            (sbox[(temp >> 8) & 0xff] << 8) |
                            (sbox[temp & 0xff]);
            temp ^= (computeRCON(i/4) << 24);
        } else if (i % 8 == 4) {
            temp = (sbox[(temp >> 24) & 0xff] << 24) |
                            (sbox[(temp >> 16) & 0xff] << 16) |
                            (sbox[(temp >> 8) & 0xff] << 8) |
                            (sbox[temp & 0xff]);
        }
        roundKeys[i] = temp ^ roundKeys[i-8];
    }
}