#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef DES_H
#define DES_H

//define struct key to store keys
typedef struct {

	unsigned char k[8];
	unsigned char c[4];
	unsigned char d[4];
}key;
void generate_keys(unsigned char* secret, key* keyset);
void process(unsigned char* message, unsigned char* processed, key* keyset, int mode);
void CBC(FILE* input,FILE*output, key*keyset, int selection);
void OFB(FILE* input, FILE* output, key* keyset, int selection);
void CFB(FILE* input, FILE* output, key* keyset, int selection);
void CTR(FILE* input, FILE* output, key* keyset, int selection);
#endif