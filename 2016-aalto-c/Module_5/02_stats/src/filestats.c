#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "filestats.h"


/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
int line_count(const char *filename)
{
	FILE *file = fopen(filename, "r");

	if (!file) {
		return -1;
	}

	long size = 0;
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	int count = 0;

	char* string = malloc(size * sizeof(char) + 1);

	while (fgets(string, size, file)) {
		count++;
		int len = strlen(string);
		if (len == size - 1) {
			break;
		}
	}

	free(string);
	fclose(file);

	return count;
}


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
int word_count(const char *filename)
{
	FILE *file = fopen(filename, "r");

	if (!file) {
		return -1;
	}

	int count = 0;
	char inside = 0;
	char ch;

	while (fread(&ch, sizeof(char), 1, file)) {
		if (isalpha(ch)) {
			inside = 1;
		}

		if (isspace(ch)) {
			if (inside) {
				count++;
			} 
			inside = 0;
		}	
	}
	
	if (inside) {
		count++;
	}

	fclose(file);

	return count;
}
