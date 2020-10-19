#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DES.h"


int main()
{
	int selection, mode;
	FILE* secret, * input, * output, * keys;

	printf("Welcome to Data Standard Encryption \n");
	printf("Please look at our menu since it has changed \n");
	printf("Please make sure you have your secret key \n");
	printf("Saved as secret.txt and input saved as \n");
	printf("input.txt and the output will be saved as \n");
	printf("output.txt");
	printf("Select 1 for encryption: \n");
	printf("Select 2 for decryption: \n");
	
	scanf_s("%d", &selection);

	//get key from user
	unsigned char* data_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char* process_block = (unsigned char*)malloc(8 * sizeof(char));
	unsigned int number_of_blocks,block_count, padding,process_mode,bytes_written,bytes_read;
	unsigned long file_size;
	unsigned char* des_key = (unsigned char*)malloc(8 * sizeof(char));

	secret = fopen("secret.txt", "rb");
	keys = fopen("keys.txt", "wb");
	
	if (!secret) {
		printf("file not open\n");
		return 0;
	}
	else if (!keys)
	{
		printf("keys file not opened try again \n");
		return 0;
	}
	else {
		unsigned char* des_key = (unsigned char*)malloc(8 * sizeof(char));
		for (int i = 0; i < 8; i++)
		{
			fscanf(secret, "%hhu", &des_key[i]);
			printf("%hhu", des_key[i]);

		}	
	bytes_written=fwrite(des_key, 1, 8, keys);
	}

	if (bytes_written != 8)
		{
			printf("error writing key to file \n");
			fclose(keys);
			return 0;
		}
	
	fclose(keys);
	
	keys = fopen("keys.txt", "rb");

	
	//checks key was stored properly
	
	bytes_read = fread(des_key, sizeof(unsigned char), 8, keys);
	if (bytes_read != 8)
	{
		printf("Key from file not valid size try again. \n");
		fclose(keys);
		return 0;
	}
	fclose(keys);
	key* keyset = (key*)malloc(17 * sizeof(key));
	generate_keys(des_key, keyset);
	fclose(secret);
	input = fopen("input.txt", "rb");
	output = fopen("output.txt", "wb");
	if (!output)
		{
			printf("could not open file please save correctly\n");
			return 0;
		}
	if (!input)
	{
		printf("could not find input file please format as plain.txt\n");
		return 0;
	}
	
	printf("\nOur menu now includes different modes of operations \n");
	printf("1 for ECB\n");
	printf("2 for CBC\n");
	printf("3 for OFB\n");
	printf("4 for CFB\n");
	printf("5 for CTR\n");
	scanf_s("%d", &mode);

	if (mode == 1)
	{
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

					process(data_block, process_block, keyset, process_mode);
					bytes_written = fwrite(process_block, 1, 8, output);

					if (padding == 8)
					{
						memset(data_block, (unsigned char)padding, 8);
						process(data_block, process_block, keyset, process_mode);
						bytes_written = fwrite(process_block, 1, 8, output);
					}
				}
				else {
					process(data_block, process_block, keyset, process_mode);
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
					process(data_block, process_block, keyset, process_mode);
					bytes_written = fwrite(process_block, 1, 8, output);
				}
				else
				{
					process_mode = 0;
					process(data_block, process_block, keyset, process_mode);
					bytes_written = fwrite(process_block, 1, 8, output);
				}
			}
			memset(data_block, 0, 8);
		}
	}
		
		

	if (mode == 2)
	{
		CBC(input,output, keyset,selection);
	
	}
	 if (mode == 3)
	{
		OFB(input, output, keyset, selection);

	}
	 if (mode == 4)
	{
		CFB(input, output, keyset, selection);

	}
	 if (mode == 5)
	 {
		 CTR(input, output, keyset, selection);
	 }
	free(des_key);
	free(data_block);
	free(process_block);
	fclose(input);
	fclose(output);
	return 0;
};
