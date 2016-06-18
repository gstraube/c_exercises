#include <stdio.h>
#include <stddef.h>
#include "source.h"


/* Print string array, last element is NULL */
/* Parameters:
 * array: string array to be printed, each string on own line */
void print_strarray(char *array[])
{
	int i = 0;
	while (array[i]) {
		printf("%s\n", array[i]);
		i++;
	}
}

/* Put strings from string separated by space to a string array */
/* Parameters:
 * string: string to be cut into parts and placed into the array, 
   remember to add ending zeros '\0' for strings and NULL to the end of the whole array!
 * arr: ready-made array that the strings will be put into */
void str_to_strarray(char *string, char **arr)
{
	int word_index = 0;
	int char_index = 0;
	while (*string) {
		if (*string == ' ') {
			arr[word_index][char_index] = '\0';
			word_index++;
			char_index = 0;
		} else {
			arr[word_index][char_index] = *string;
			char_index++;
		}

		string++;
	}
	arr[word_index][char_index] = '\0';
	arr[word_index + 1] = NULL;
}
