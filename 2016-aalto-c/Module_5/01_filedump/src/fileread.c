#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "fileread.h"

/* Prints the given file as text on the screen.
 * Only printable characters are shown. Non-printable characters are printed
 * as '?'. <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int textdump(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
	    return -1;
    }

    char ch;
    int count = 0;
    while (fread(&ch, sizeof(char), 1, file)) {
	if (isprint(ch)) {
		printf("%c", ch);	
	} else {
		printf("?");
	}
	count++;
    }

    return count;
}


/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int hexdump(const char *filename)
{
    FILE *file = fopen(filename, "r");
    
    if (!file) {
	    return -1;
    }

    char ch;
    int count = 0;
    
    while (fread(&ch, sizeof(char), 1, file)) {
	    if (ch < 0x10) {
		printf("0%x", ch);
	    } else {
		printf("%.2x", ch);
	    }
	    printf(" ");
	    count++;

	    if (count % 16 == 0) {
		    printf("\n");
	    } 
    }

    return count;
}
