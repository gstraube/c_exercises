#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strarray.h"

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_array(void)
{
	char **array = malloc(sizeof(char*));
	array[0] = NULL;

	return array;   // replace this
}

/* Releases the memory used by the strings.
 */
void free_strings(char **array)
{
	char** ptr = array;
	while(*ptr) {
		free(*ptr);
		ptr++;
	}
	
	free(array);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **add_string(char **array, const char *string)
{
	int len = 0;
	char **current_ptr = array;
	while(*current_ptr) {
		len++;
		current_ptr++;
	}
	char **new_array = realloc(array, (len + 2) * sizeof(char*));
	new_array[len] = malloc(strlen(string) * sizeof(char*));
	strcpy(new_array[len], string);

	new_array[len + 1] = NULL;

	return new_array;
}

/* Exercise c: Convert letters of all strings in <array> to lower case.
 */
void make_lower(char **array)
{
	while (*array) {
		char *string = *array;
		while (*string) {
			*string = tolower(*string);
			string++;
		}	
		array++;
	}
}


/* Exercise d: reorder strings in <array> to lexicographical order */
void sort_strings(char **array)
{
	int len = 0;
	char **current_ptr = array;
	while (*current_ptr) {
		len++;
		current_ptr++;
	}

	for (int i = 0; i < len; i++) {
		char *string = array[i];
		unsigned int swap_pos = i;
		for (int j = i + 1; j < len; j++) {
			if (strcmp(array[j], string) < 0) {
				string = array[j];
				swap_pos = j;
			}	
		}	
		array[swap_pos] = array[i];
		array[i] = string;
	}
}

/* You can use this function to check what your array looks like.
 */
void print_strings(char **array)
{
	if (!array)
		return;
	while (*array) {
		printf("%s  ", *array);
		array++;
	}
    printf("\n");
}
