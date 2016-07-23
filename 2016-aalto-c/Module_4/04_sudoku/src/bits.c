#include <stdio.h>
#include <stdlib.h>
#include "bits.h"

/* Allocate memory for 8x8 table and returns pointer to the two-dimensional
 * array.
 */
char **allocTable(void)
{
    char **rows = malloc(8 * sizeof(char *));
    if (!rows)
        return NULL;
    for (unsigned int i = 0; i < 8; i++) {
        rows[i] = malloc(8 * sizeof(char));
    }
    return rows;
}

/* Frees memory of the two-dimensional array indicated in <s>
 */
void releaseTable(char **s)
{
    for (unsigned int i = 0; i < 8; i++) {
        free(s[i]);
    }
    free(s);
}

/* Prints the bits on table <s>, and the 8-bit values of each row and column.
 * Note that the function relies on having calculateRow and calculateColumn
 * implemented.
 */
void printTable(char **s)
{
    for (int y = 7; y >= 0; y--) {
        for (int x = 7; x >= 0; x--) {
            printf("%3d", s[y][x]);
        }
        printf(" %02x\n", calculateRow(s, y));
    }
    for (int x = 7; x >= 0; x--) {
        printf(" %02x", calculateColumn(s, x));
    }
    printf("\n");
}

/* Exercise 4.4.a: calculate the 8-bit number represented by row <idx> in
 * table <s>.
 * Returns: the number represented by the bits.
 */
unsigned char calculateRow(char **s, int idx)
{
    unsigned char number = 0;
    for (int x = 7; x >= 0; x--) {
	number |= (s[idx][x] << x);	
    }

    return number;
}

/* Exercise 4.4.a: calculate the 8-bit number represented by column <idx> in
 * table <s>.
 * Returns: the number represented by the bits.
 */
unsigned char calculateColumn(char **s, int idx)
{
    unsigned char number = 0;
    for (int y = 7; y >= 0; y--) {
	number |= (s[y][idx] << y);
    }

    return number;
}

/* Exercise 4.4.b: set the bits on row <idx> in table <s> to represent
 * <value>.
 */
void setRow(char **s, int idx, unsigned char value)
{
    for (int x = 0; x < 8; x++) {
	    unsigned char val1 = value << x;
	    unsigned char val2 = val1 >> 7;
	    s[idx][7 - x] = val2;

    } 
}

/* Exercise 4.4.b: set the bits on column <idx> in table <s> to represent
 * <value>.
 */
void setColumn(char **s, int idx, unsigned char value)
{
    for (int y = 0; y < 8; y++) {
	    unsigned char val1 = value << y;
	    unsigned char val2 = val1 >> 7;
	    s[7 - y][idx] = val2;

    } 
}
