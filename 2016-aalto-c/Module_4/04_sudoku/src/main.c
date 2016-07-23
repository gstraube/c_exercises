#include <stdio.h>
#include "bits.h"

int main()
{
    /* Feel free to modify this function to test different things */

    char **s = allocTable();
    
    // format: "r <row> <hexnumber>"
    // or: "c <column> <hexnumber>"
    while (1) {
        int idx;
        unsigned int value;
        printTable(s);
        char buf[40];
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "r %d %x", &idx, &value) == 2) {
            setRow(s, idx, value);
        } else if (sscanf(buf, "c %d %x", &idx, &value) == 2) {
            setColumn(s, idx, value);
        } else {
            printf("Invalid input, should be: r|c <row> <hexnumber>\n");
        }
    }
    releaseTable(s);
}
