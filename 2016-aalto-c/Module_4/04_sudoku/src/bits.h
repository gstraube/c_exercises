#ifndef AALTO_BITS_H
#define AALTO_BITS_H

char **allocTable(void);

void releaseTable(char **s);

void printTable(char **s);

unsigned char calculateRow(char **s, int idx);

unsigned char calculateColumn(char **s, int idx);

void setRow(char **s, int idx, unsigned char value);

void setColumn(char **s, int idx, unsigned char value);


#endif
