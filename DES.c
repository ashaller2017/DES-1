#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DES.h"

//all tables were received from wikipedia
//Initial Permutation

int IP1[] =
{
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};



//Permutated choice 1
int PC1[] =
{
	57, 49,  41, 33,  25,  17,  9,
	1, 58,  50, 42,  34,  26, 18,
	10,  2,  59, 51,  43,  35, 27,
	19, 11,   3, 60,  52,  44, 36,
	63, 55,  47, 39,  31,  23, 15,
	7, 62,  54, 46,  38,  30, 22,
	14,  6,  61, 53,  45,  37, 29,
	21, 13,   5, 28,  20,  12,  4
};




//substitution boxes (1-8)
int S_1[] =
{
	14,4,13,1,2,15,11,8,3,10,6, 12,  5,  9,  0,  7,
	0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

int S_2[] =
{
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};

int S_3[] =
{
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};

int S_4[] =
{
	7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};

int S_5[] =
{
	2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};

int S_6[] =
{
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};

int S_7[] =
{
	4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};

int S_8[] =
{
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};


//Expansion Table
int expansion[] =
{
	32,1,2,3,4,5,
	4,5,6,7,8,9,
	8,9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32,1
};

//Permutation Table
int permutation[] =
{
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
};

//Inital permutation inverse
int IPINV[] =
{
	40,  8, 48, 16, 56, 24, 64, 32,
	39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30,
	37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28,
	35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26,
	33,  1, 41,  9, 49, 17, 57, 25
};

//Permutated Choice 2
int PC2[] =
{
	14, 17, 11, 24,  1,  5,
	3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

//Bit Rotation
int BitRotation[] = { 0,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

void generate_keys(unsigned char* secret, key* keyset)
{
	int i, j;
	int shift_size;

	unsigned char shift_byte, first_bit, second_bit, third_bit, fourth_bit;

	for (i = 0; i < 8; i++)
	{
		keyset[0].k[i] = 0;
	}

	for (i = 0; i < 56; i++)
	{
		shift_size = PC1[i];
		shift_byte = 0x80 >> ((shift_size - 1) % 8);
		shift_byte &= secret[(shift_size - 1) / 8];
		shift_byte <<= ((shift_size - 1) % 8);

		keyset[0].k[i / 8] |= (shift_byte >> i % 8);
		
	}
	for (i=0; i<3;i++)
	{
		keyset[0].c[i] = keyset[0].k[i];
	}
	keyset[0].c[3] = keyset[0].k[0] & 0xF0;

	for (i = 0; i < 3; i++) {
		keyset[0].d[i] = (keyset[0].k[i + 3] & 0x0F) << 4;
		keyset[0].d[i] |= (keyset[0].k[i + 4] & 0xF0) >> 4;
	}
	keyset[0].d[3] = (keyset[0].k[6] & 0x0F) << 4;

	for (i = 1; i < 17; i++)
	{
		for (j = 0; j < 4; j++) {
			keyset[i].c[j] = keyset[i - 1].c[j];
			keyset[i].d[j] = keyset[i - 1].d[j];
		}
		shift_size = BitRotation[i];
		if (shift_size == 1)
		{
			shift_byte = 0x80;
		}
		else
			shift_byte = 0xC0;

		//process c
		first_bit = shift_byte & keyset[i].c[0];
		second_bit = shift_byte & keyset[i].c[1];
		third_bit = shift_byte & keyset[i].c[2];
		fourth_bit = shift_byte & keyset[i].c[3];

		keyset[i].c[0] <<= shift_size;
		keyset[i].c[0] |= (second_bit >> (8 - shift_size));

		keyset[i].c[1] <<= shift_size;
		keyset[i].c[1] |= (third_bit >> (8 - shift_size));

		keyset[i].c[2] <<= shift_size;
		keyset[i].c[2] |= (fourth_bit >> (8 - shift_size));

		keyset[i].c[3] <<= shift_size;
		keyset[i].c[3] |= (first_bit >> (4 - shift_size));

		//process D
		first_bit = shift_byte & keyset[i].d[0];
		second_bit = shift_byte & keyset[i].d[1];
		third_bit = shift_byte & keyset[i].d[2];
		fourth_bit = shift_byte & keyset[i].d[3];

		keyset[i].d[0] <<= shift_size;
		keyset[i].d[0] |= (second_bit >> (8 - shift_size));

		keyset[i].d[1] <<= shift_size;
		keyset[i].d[1] |= (third_bit >> (8 - shift_size));

		keyset[i].d[2] <<= shift_size;
		keyset[i].d[2] |= (fourth_bit >> (8 - shift_size));

		keyset[i].d[3] <<= shift_size;
		keyset[i].d[3] |= (first_bit >> (4- shift_size));

		for (j = 0; j < 48; j++)
		{
			shift_size = PC2[j];
			if (shift_size <= 28)
			{
				shift_byte = 0x80 >> ((shift_size - 1) % 8);
				shift_byte &= keyset[i].c[(shift_size - 1) / 8];
				shift_byte <<= ((shift_size - 1) % 8);

			}
			else
			{
				shift_byte = 0x80 >> ((shift_size - 29) % 8);
				shift_byte &= keyset[i].d[(shift_size - 29) / 8];
				shift_byte <<= ((shift_size - 29) % 8);
			}
			keyset[i].k[j / 8] |= (shift_byte >> j % 8);
		}
	}
}

void process(unsigned char* message, unsigned char* processed, key* keyset, int mode)
{
	int i, k;
	int shift_size;
	unsigned char shift_byte;

	unsigned char ip[8];
	memset(ip, 0, 8);
	memset(processed, 0, 8);

	for (i = 0; i < 64; i++)
	{
		shift_size = IP1[i];
		shift_byte = 0x80 >> ((shift_size - 1) % 8);
		shift_byte &= message[(shift_size - 1) / 8];
		shift_byte <<= ((shift_size - 1) % 8);

		ip[i/8] |= (shift_byte >> i % 8);

	}

	unsigned char l[4], r[4];
	for (i = 0; i < 4; i++)
	{
		l[i] = ip[i];
		r[i] = ip[i+4];
	}
	unsigned char ln[4], rn[4], er[6], ser[4];
	int key_index;
	for (k = 1; k < 17; k++)
	{
		memcpy(ln, r, 4);

		memset(er, 0, 6);
		for (i = 0; i < 48; i++)
		{
			
			shift_size = expansion[i];
			shift_byte = 0x80 >> ((shift_size - 1) % 8);
			shift_byte &= r[(shift_size - 1) / 8];
			shift_byte <<= ((shift_size - 1) % 8);

			er[i / 8] |= (shift_byte >> i % 8);
		}
		if (mode == 0)
		{
			key_index = 17 - k;
		}
		else {
			key_index = k;
		}

		for (i = 0; i < 6; i++)
		{
			er[i] ^= keyset[key_index].k[i];
		}
		unsigned char row, column;

		for (i = 0; i < 4; i++)
		{
			ser[i] = 0;
		}
		
		row = 0;
		row |= ((er[0] & 0x80) >> 6);
		row |= ((er[0] & 0x04) >> 2);
		
		column = 0;
		column |= ((er[0] & 0x78) >> 3);

		ser[0] |= ((unsigned char)S_1[row * 16 + column] << 4);

		row = 0;
		row |= (er[0] & 0x02);
		row |= ((er[1] & 0x10) >> 4);

		column = 0;
		column |= ((er[0] & 0x01) << 3);
		column |= ((er[1] & 0xE0) >> 5);

		ser[0] |= (unsigned char)S_2[row * 16 + column];

		// Byte 2
		row = 0;
		row |= ((er[1] & 0x08) >> 2);
		row |= ((er[2] & 0x40) >> 6);

		column = 0;
		column |= ((er[1] & 0x07) << 1);
		column |= ((er[2] & 0x80) >> 7);

		ser[1] |= ((unsigned char)S_3[row * 16 + column] << 4);

		row = 0;
		row |= ((er[2] & 0x20) >> 4);
		row |= (er[2] & 0x01);

		column = 0;
		column |= ((er[2] & 0x1E) >> 1);

		ser[1] |= (unsigned char)S_4[row * 16 + column];

		// Byte 3
		row = 0;
		row |= ((er[3] & 0x80) >> 6);
		row |= ((er[3] & 0x04) >> 2);

		column = 0;
		column |= ((er[3] & 0x78) >> 3);

		ser[2] |= ((unsigned char)S_5[row * 16 + column] << 4);

		row = 0;
		row |= (er[3] & 0x02);
		row |= ((er[4] & 0x10) >> 4);

		column = 0;
		column |= ((er[3] & 0x01) << 3);
		column |= ((er[4] & 0xE0) >> 5);

		ser[2] |= (unsigned char)S_6[row * 16 + column];

		// Byte 4
		row = 0;
		row |= ((er[4] & 0x08) >> 2);
		row |= ((er[5] & 0x40) >> 6);

		column = 0;
		column |= ((er[4] & 0x07) << 1);
		column |= ((er[5] & 0x80) >> 7);

		ser[3] |= ((unsigned char)S_7[row * 16 + column] << 4);

		row = 0;
		row |= ((er[5] & 0x20) >> 4);
		row |= (er[5] & 0x01);

		column = 0;
		column |= ((er[5] & 0x1E) >> 1);

		ser[3] |= (unsigned char)S_8[row * 16 + column];

		for (i = 0; i < 4; i++) {
			rn[i] = 0;
		}

		for (i = 0; i < 32; i++)
		{
			shift_size = permutation[i];
			shift_byte = 0x80 >> ((shift_size - 1) % 8);
			shift_byte &= ser[(shift_size - 1) / 8];
			shift_byte <<= ((shift_size - 1) % 8);

			rn[i / 8] |= (shift_byte >> i % 8);
		}
		for (i = 0; i < 4; i++)
		{
			rn[i] ^= l[i];
		}
		for (i = 0; i < 4; i++)
		{
			l[i] = ln[i];
			r[i] = rn[i];
		}
	}
	unsigned char pre_end_permutation[8];
	for (i = 0; i < 4; i++) {
		pre_end_permutation[i] = r[i];
		pre_end_permutation[4 + i] = l[i];
	}

	for (i = 0; i < 64; i++) {
		shift_size = IPINV[i];
		shift_byte = 0x80 >> ((shift_size - 1) % 8);
		shift_byte &= pre_end_permutation[(shift_size - 1) / 8];
		shift_byte <<= ((shift_size - 1) % 8);

		processed[i / 8] |= (shift_byte >> i % 8);
	}
}