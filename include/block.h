#ifndef BLOCK_H
#define BLOCK_H

void BAES128(unsigned char* block, unsigned int* roundKeys);
void BAES192(unsigned char* block, unsigned int* roundKeys);
void BAES256(unsigned char* block, unsigned int* roundKeys);

void BInvAES128(unsigned char* block, unsigned int* roundKeys);
void BInvAES192(unsigned char* block, unsigned int* roundKeys);
void BInvAES256(unsigned char* block, unsigned int* roundKeys);

#endif