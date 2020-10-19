#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DES.h"



void CBC(FILE*input,FILE*output,key*keyset, int selection)
{

	unsigned char* data_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* temp = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* process_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned int number_of_blocks, block_count, padding, process_mode, bytes_written, bytes_read;
	unsigned long file_size;
	unsigned char* IV = (unsigned char*)malloc(8 * sizeof(char));
	int i,generate;
	FILE* IV1;
	printf("\n You have chosen Cipher Block Chaining\n");
	
	printf("you can either include an initialization vector file\n");
	printf("saved as IV.txt or enter 1 to generate one: \n");
	scanf_s("%d", &generate);
	if (generate == 1)
	{//create IV vector
		for (i = 0; i < 8; i++) {
			IV[i] = rand() % 255;
		}

		IV1 = fopen("IV.txt", "wb");
		bytes_written = fwrite(IV, 1, 8, IV1);
		fclose(IV1);
	}
	IV1 = fopen("IV.txt", "rb");
	bytes_read = fread(IV, 1, 8, IV1);
	if (bytes_read != 8)
	{
		printf("IV is not correct format\n");
		return 0;
	}
	fclose(IV1);
	fseek(input, 0L, SEEK_END);
	file_size = ftell(input);
	process_mode = 0;

	fseek(input, 0L, SEEK_SET);
	number_of_blocks = file_size / 8 + ((file_size % 8) ? 1 : 0);
	block_count = 0;
	while (fread(data_block, 1, 8, input))
	{
		block_count++;
		if (block_count == number_of_blocks)
		{

			if (selection == 1)
			{
				process_mode = 1;
				padding = 8 - file_size % 8;
				if (padding < 8)
				{
					memset((data_block + 8 - padding), (unsigned char)padding, padding);
				}
				for (i = 0; i < 8; i++)
				{
					data_block[i] ^= temp[i];
				}
				process(data_block, process_block, keyset, process_mode);
				bytes_written = fwrite(process_block, 1, 8, output);

				if (padding == 8)
				{
					memset(data_block, (unsigned char)padding, 8);
					for (i = 0; i < 8; i++)
					{
						data_block[i] ^= temp[i];
					}
					
					process(data_block, process_block, keyset, process_mode);
					bytes_written = fwrite(process_block, 1, 8, output);

				}
			}
			else {
				process(data_block, process_block, keyset, process_mode);
				padding = process_block[7];
				
				if (padding < 8)
				{
					for (i = 0; i < 8-padding; i++)
					{
						process_block[i] ^= temp[i];
					}
					bytes_written = fwrite(process_block, 1, 8 - padding, output);
				}	
			}
		
		}
		else
		{
			if (selection == 1)
			{
				if (block_count == 1)
				{
					for (i = 0; i < 8; i++)
					{
						data_block[i] ^= IV[i];
					}
				}
				else
				{
					for (i = 0; i < 8; i++)
					{
						data_block[i] ^= temp[i];
					}
				}
				process_mode = 1;
				process(data_block, process_block, keyset, process_mode);
				bytes_written = fwrite(process_block, 1, 8, output);
				*temp = *process_block;

			}
			else
			{
				process_mode = 0;
				
				process(data_block, process_block, keyset, process_mode);

				if (block_count == 1)
				{
					*temp = *data_block;
					for (i = 0; i < 8; i++)
					{
						process_block[i] ^= IV[i];
					}
				}
				else
				{
					for (i = 0; i < 8; i++)
					{
						process_block[i] ^= temp[i];
					}
					*temp = *data_block;
				}
				bytes_written = fwrite(process_block, 1, 8, output);
			}


		}
		memset(data_block, 0, 8);
	}
}


void OFB(FILE* input, FILE* output, key* keyset, int selection)

{
	unsigned char* data_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* temp = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* process_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned int number_of_blocks, block_count, padding, process_mode, bytes_written, bytes_read;
	unsigned long file_size;
	unsigned char* IV = (unsigned char*)malloc(8 * sizeof(char));
	int i, generate;
	FILE* IV1;
	printf("\n You have chosen Output Feedback Mode\n");

	printf("you can either include an initialization vector file\n");
	printf("saved as IV.txt or enter 1 to generate one: \n");
	scanf_s("%d", &generate);
	if (generate == 1)
	{//create IV vector
		for (i = 0; i < 8; i++) {
			IV[i] = rand() % 255;
		}

		IV1 = fopen("IV.txt", "wb");
		bytes_written = fwrite(IV, 1, 8, IV1);
		fclose(IV1);
	}
	IV1 = fopen("IV.txt", "rb");
	bytes_read = fread(IV, 1, 8, IV1);
	if (bytes_read != 8)
	{
		printf("IV is not correct format\n");
		return 0;
	}

	fclose(IV1);
	fseek(input, 0L, SEEK_END);
	file_size = ftell(input);
	process_mode = 0;

	fseek(input, 0L, SEEK_SET);
	number_of_blocks = file_size / 8 + ((file_size % 8) ? 1 : 0);
	block_count = 0;
	while (fread(data_block, 1, 8, input))
	{
		block_count++;
		if (block_count == number_of_blocks)
		{

			if (selection == 1)
			{
				process_mode = 1;
				padding = 8 - file_size % 8;
				if (padding < 8)
				{
					memset((data_block + 8 - padding), (unsigned char)padding, padding);
				}

				process(IV, process_block, keyset, process_mode);
				
				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				bytes_written = fwrite(process_block, 1, 8, output);
				
				if (padding == 8)
				{
					memset(data_block, (unsigned char)padding, 8);
					process(IV, process_block, keyset, process_mode);
					for (int i = 0; i < 8; i++)
					{
						data_block[i] ^= process_block[i];
					}
					bytes_written = fwrite(process_block, 1, 8, output);
				}
			}
			else {
				process(IV, process_block, keyset, process_mode);
				padding = process_block[7];
				for (int i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}

				if (padding < 8)
				{
					bytes_written = fwrite(process_block, 1, 8 - padding, output);
				}
			}
		}
		else
		{
			if (selection == 1)
			{
				process_mode = 1;
	
				process(IV, process_block, keyset, process_mode);		
				*IV = *process_block;
				for (int i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				bytes_written = fwrite(process_block, 1, 8, output);
			}
			else
			{
				process_mode = 0;
				process(IV, process_block, keyset, process_mode);
				
				*IV = *process_block;
				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				bytes_written = fwrite(process_block, 1, 8, output);
			}


		}
		memset(data_block, 0, 8);
	}
}

void CFB(FILE* input, FILE* output, key* keyset, int selection)
{
	unsigned char* data_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* temp = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* process_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned int number_of_blocks, block_count, padding, process_mode, bytes_written, bytes_read;
	unsigned long file_size;
	unsigned char* IV = (unsigned char*)malloc(8 * sizeof(char));
	int i, generate;
	FILE* IV1;
	printf("\n You have chosen Output Feedback Mode\n");

	printf("you can either include an initialization vector file\n");
	printf("saved as IV.txt or enter 1 to generate one: \n");
	scanf_s("%d", &generate);
	if (generate == 1)
	{//create IV vector
		for (i = 0; i < 8; i++) {
			IV[i] = rand() % 255;
		}

		IV1 = fopen("IV.txt", "wb");
		bytes_written = fwrite(IV, 1, 8, IV1);
		fclose(IV1);
	}
	IV1 = fopen("IV.txt", "rb");
	bytes_read = fread(IV, 1, 8, IV1);
	if (bytes_read != 8)
	{
		printf("IV is not correct format\n");
		return 0;
	}

	fclose(IV1);
	fseek(input, 0L, SEEK_END);
	file_size = ftell(input);
	process_mode = 0;

	fseek(input, 0L, SEEK_SET);
	number_of_blocks = file_size / 8 + ((file_size % 8) ? 1 : 0);
	block_count = 0;
	while (fread(data_block, 1, 8, input))
	{
		block_count++;
		if (block_count == number_of_blocks)
		{

			if (selection == 1)
			{
				process_mode = 1;
				padding = 8 - file_size % 8;
				if (padding < 8)
				{
					memset((data_block + 8 - padding), (unsigned char)padding, padding);
				}

				process(temp, process_block, keyset, process_mode);
				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				
				bytes_written = fwrite(process_block, 1, 8, output);
				
				if (padding == 8)
				{
					memset(data_block, (unsigned char)padding, 8);
					process(temp, process_block, keyset, process_mode);
					for (i = 0; i < 8; i++)
					{
						process_block[i] ^= data_block[i];
					}
					bytes_written = fwrite(process_block, 1, 8, output);
				}
			}
			else {
				process(temp, process_block, keyset, process_mode);
				padding = process_block[7];

				if (padding < 8)
				{
					for (i = 0; i < 8; i++)
					{
						process_block[i] ^= data_block[i];
					}
					bytes_written = fwrite(process_block, 1, 8 - padding, output);
				}
			}
		}
		else
		{
			if (selection == 1)
			{
				process_mode = 1;
				if (block_count == 1)
				{
					process(IV, process_block, keyset, process_mode);
				}
				else
				{
					process(temp, process_block, keyset, process_mode);
				}
				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				*temp = *process_block;
				bytes_written = fwrite(process_block, 1, 8, output);
				
			}
			else
			{
				process_mode = 0;
				if (block_count == 1)
				{
					process(IV, process_block, keyset, process_mode);
				}
				else
				{
					process(temp, process_block, keyset, process_mode);
				}
				
				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				*temp = *data_block;
				bytes_written = fwrite(process_block, 1, 8, output);
			}


		}
		memset(data_block, 0, 8);
	}
}

void CTR(FILE* input, FILE* output, key* keyset, int selection)
{
	unsigned char* data_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* temp = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* process_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned int number_of_blocks, block_count, padding, process_mode, bytes_written, bytes_read;
	unsigned long file_size;
	unsigned char* IV = (unsigned char*)malloc(8 * sizeof(char));
	int i, generate;
	unsigned int counter;
	FILE* IV1;
	printf("\n You have chosen Output Feedback Mode\n");

	printf("you can either include an initialization vector file\n");
	printf("saved as IV.txt or enter 1 to generate one: \n");
	scanf_s("%d", &generate);
	if (generate == 1)
	{//create IV vector
		for (i = 0; i < 8; i++) {
			IV[i] = rand() % 255;
		}

		IV1 = fopen("IV.txt", "wb");
		bytes_written = fwrite(IV, 1, 8, IV1);
		fclose(IV1);
	}
	IV1 = fopen("IV.txt", "rb");
	bytes_read = fread(IV, 1, 8, IV1);
	if (bytes_read != 8)
	{
		printf("IV is not correct format\n");
		return 0;
	}

	fclose(IV1);
	fseek(input, 0L, SEEK_END);
	file_size = ftell(input);
	process_mode = 0;

	fseek(input, 0L, SEEK_SET);
	number_of_blocks = file_size / 8 + ((file_size % 8) ? 1 : 0);
	block_count = 0;
	counter = 0;
	while (fread(data_block, 1, 8, input))
	{
		block_count++;
		if (block_count == number_of_blocks)
		{

			if (selection == 1)
			{
				process_mode = 1;
				padding = 8 - file_size % 8;
				if (padding < 8)
				{
					memset((data_block + 8 - padding), (unsigned char)padding, padding);
				}

				IV || counter;
				process(IV, process_block, keyset, process_mode);

				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				bytes_written = fwrite(process_block, 1, 8, output);

				if (padding == 8)
				{
					memset(data_block, (unsigned char)padding, 8);
					IV || counter;
					process(IV, process_block, keyset, process_mode);

					for (i = 0; i < 8; i++)
					{
						process_block[i] ^= data_block[i];
					}
					bytes_written = fwrite(process_block, 1, 8, output);
				}
			}
			else {
				for (i = 0; i < 8; i++)
				{
					IV[i] || counter;
				}
				process(IV, process_block, keyset, process_mode);

				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				padding = process_block[7];

				if (padding < 8)
				{
					bytes_written = fwrite(process_block, 1, 8 - padding, output);
				}
			}
		}
		else
		{
			if (selection == 1)
			{
				process_mode = 1;

				IV || counter;
				process(IV, process_block, keyset, process_mode);

				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				bytes_written = fwrite(process_block, 1, 8, output);
			}
			else
			{
				process_mode = 0;
				IV || counter;
				process(IV, process_block, keyset, process_mode);
				for (i = 0; i < 8; i++)
				{
					process_block[i] ^= data_block[i];
				}
				bytes_written = fwrite(process_block, 1, 8, output);
			}
		}
		memset(data_block, 0, 8);
		counter++;
	}
}
