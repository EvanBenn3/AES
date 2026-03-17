#ifndef KEYGEN_H
#define KEYGEN_H

void roundKeyGen128(unsigned int* roundKeys);
void roundKeyGen192(unsigned int* roundKeys);
void roundKeyGen256(unsigned int* roundKeys);

#endif