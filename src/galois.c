#include "galois.h"

unsigned char mul2 (unsigned char n) {
    if (n & 0x80) {
        n <<= 1;
        n ^= 0x1b;
    } else {
        n <<= 1;
    }
    return n;
}

unsigned char mul3 (unsigned char n) {
    n ^= mul2(n);
    return n;
}

unsigned char mul9 (unsigned char n) {
    return mul2(mul2(mul2(n))) ^ n;
}

unsigned char mul11 (unsigned char n) {
    return mul2(mul2(mul2(n))) ^ mul2(n) ^ n;
}

unsigned char mul13 (unsigned char n) {
    return mul2(mul2(mul2(n))) ^ mul2(mul2(n)) ^ n;
}

unsigned char mul14 (unsigned char n) {
    return mul2(mul2(mul2(n))) ^ mul2(mul2(n)) ^ mul2(n);
}

unsigned char computeRCON(int n) {
    unsigned char m = 1;
    for (int i = 1; i < n; i++) {
        m = mul2(m);
    }
    return m;
}
