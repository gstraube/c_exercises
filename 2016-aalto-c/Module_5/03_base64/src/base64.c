#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "base64.h"

/* The set of base64-encoded characters. You may use this table if you want.
 * (The last character is not part of the actual base64 set, but used for
 * padding). 
 */
const char *encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

char get_index(char encoded_ch)
{
	char index = 0;
	const char *ptr = encoding;
	while (*ptr) {
		if (*ptr == encoded_ch) {
			return index;
		}
		index++;
		ptr++;
	}

	return -1;
}

/* Open file named <src_file> for reading, and convert it to Base64 format,
 * which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int to_base64(const char *dst_file, const char *src_file)
{
	FILE *input = fopen(src_file, "r");
	FILE *output = fopen(dst_file, "w");

	if (!input || !output) {
		return -1;
	}

	long size = 0;
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	rewind(input);

	int num_reads = size / 3;
	int rem_reads = size % 3;
	int buffer = 0;

	for (int i = 0; i < num_reads; i++) {
		fread(&buffer, sizeof(char), 3, input);

		char string[5];

		string[0] = encoding[(buffer >> 2) & 0x3f];
		string[1] = encoding[((buffer & 3) << 4) | ((buffer >> 12) & 15)]; 
		string[2] = encoding[(buffer >> 22) | (((buffer >> 8) << 2) & 0x3f)];
		string[3] = encoding[(buffer >> 16) & 0x3f];
		string[4] = '\0';

		fputs(string, output);
		if ((i + 1) % 16 == 0) {
			fputs("\n", output);
		}
	}

	if (rem_reads > 0) {
		buffer = 0;
		fread(&buffer, sizeof(char), rem_reads, input);
		char string[5];

		string[0] = encoding[(buffer >> 2) & 0x3f];
		string[1] = encoding[((buffer & 3) << 4) | ((buffer >> 12) & 15)]; 

		if (rem_reads == 1) {
			string[2] = '=';
		} else {
			string[2] = encoding[(buffer >> 22) | (((buffer >> 8) << 2) & 0x3f)];
		}

		string[3] = '=';
		string[4] = '\0';

		fputs(string, output);
	}

	fclose(input);
	fclose(output);

	return size;
}

/* Open Base64-encoded file named <src_file> for reading, and convert it
 * to regular binary format, which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int from_base64(const char *dst_file, const char *src_file)
{
	FILE *input = fopen(src_file, "r");
	FILE *output = fopen(dst_file, "w");

	if (!input || !output) {
		return -1;
	}
	long size = 0;
	fseek(input, 0, SEEK_END);
	size = ftell(input);
	rewind(input);

	int buffer = 0;
	long byte_count = size;

	for (long i = 0; i < (byte_count / 4); i++) {

		char string[4];
		fread(&buffer, sizeof(char), 4, input); 

		char first = buffer >> 24;
		char second = (buffer << 8) >> 24;
		char third = (buffer << 16) >> 24;
		char fourth = (buffer << 24) >> 24;

		first = get_index(first);
		second = get_index(second);
		third = get_index(third);
		fourth = get_index(fourth);
		string[0] = (fourth << 2) | (third >> 4);
		string[1] = (third << 4) | (second >> 2);
		string[2] = (second << 6) | first;
		string[3] = '\0';

		int num_writes = (first == 64) ? 2 : 3;
		num_writes = (second == 64) ? 1 : num_writes;

		fwrite(string, sizeof(char), num_writes, output);

		if (((i + 1) % 16 == 0)) {
			char *temp;
			fread(&temp, sizeof(char), 1, input); 
			byte_count--;
		}
	}

	fclose(input);
	fclose(output);

	return size;
}
