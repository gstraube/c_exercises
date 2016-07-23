#include <check.h>
#include "tmc-check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include "../src/bits.h"

static unsigned char rows[8];

void randomTable(char **s, int flip)
{
    for (unsigned int y = 0; y < 8; y++) {
        rows[y] = rand() & 0xff;
        int hamy = 128;
        for (int x = 7; x >= 0; x--) {
            if (!flip)
                s[y][x] = (rows[y] & hamy) != 0;
            else
                s[x][y] = (rows[y] & hamy) != 0;
            hamy >>= 1;
        }
    }
}

void emptyTable(char **s, int flip)
{
    for (unsigned int y = 0; y < 8; y++) {
        rows[y] = rand() & 0xff;
        int hamy = 128;
        for (int x = 7; x >= 0; x--) {
            if (!flip)
                s[y][x] = 0;
            else
                s[x][y] = 0;
            hamy >>= 1;
        }
    }
}

void printRow(char **s, int idx, char *buf, int flip)
{
    char buf2[8];
    buf[0] = 0;
    for (int i = 7; i >= 0; i--) {
        if (!flip)
            snprintf(buf2, 7, "%d ", s[idx][i]);
        else
            snprintf(buf2, 7, "%d ", s[i][idx]);
        strcat(buf, buf2);
    }
}

void printbin(char *buf, unsigned char val)
{
    int hamy = 128;
    char buf2[8];
    buf[0] = 0;
    for (int i = 7; i >= 0; i--) {
        snprintf(buf2, 8, "%d ", (val & hamy) != 0);
        strcat(buf, buf2);
        hamy >>= 1;
    }
}

START_TEST(test_calculate)
{
    char **s = allocTable();
    char buf[80];
    
    randomTable(s, 0);    
    for (unsigned int i = 0; i < 8; i++) {
        unsigned char student = calculateRow(s, i);
        if (student != rows[i]) {
            printRow(s, i, buf, 0);
            releaseTable(s);
            fail("[Task 4.4.a] Row %d is %s. calculateRow should return 0x%02x. You returned: 0x%02x",
                    i, buf, rows[i], student);
        }
    }
    randomTable(s, 1);    
    for (unsigned int i = 0; i < 8; i++) {
        unsigned char student = calculateColumn(s, i);
        if (student != rows[i]) {
            printRow(s, i, buf, 1);
            releaseTable(s);
            fail("[Task 4.4.a] Column %d is %s. calculateColumn should return 0x%02x. You returned: 0x%02x",
                    i, buf, rows[i], student);
        }
    }
    releaseTable(s);
}
END_TEST

int checkRow(char **s, int idx, int flip)
{
    int hamy = 128;
    int i = 7;
    while (hamy) {
        unsigned char v;
        if (!flip)
            v = s[idx][i];
        else
            v = s[i][idx];
        if (((rows[idx] & hamy) != 0) != v)
            return 0;
        i--;
        hamy >>= 1;
    }
    return 1;
}

START_TEST(test_set)
{
    char **s = allocTable();
    char buf_ref[80];
    char buf_stud[80];
    
    emptyTable(s, 0);    
    for (unsigned int i = 0; i < 8; i++) {
        setRow(s, i, rows[i]);
        if (!checkRow(s, i, 0)) {
            printRow(s, i, buf_stud, 0);
            printbin(buf_ref, rows[i]);
            releaseTable(s);
            fail("[Task 4.4.b] setRow on row %d with value 0x%02x should result row content %s, you got %s",
                    i, rows[i], buf_ref, buf_stud);
        }
    }
    
    emptyTable(s, 1);    
    for (unsigned int i = 0; i < 8; i++) {
        setColumn(s, i, rows[i]);
        if (!checkRow(s, i, 1)) {
            printRow(s, i, buf_stud, 1);
            printbin(buf_ref, rows[i]);
            releaseTable(s);
            fail("[Task 4.4.b] setColumn on column %d with value 0x%02x should result column content %s, you got %s",
                    i, rows[i], buf_ref, buf_stud);
        }
    }
    releaseTable(s);
}
END_TEST


int main(int argc, const char *argv[])
{
    srand((unsigned) time(NULL));
    Suite *s = suite_create("Test-4.4");

    tmc_register_test(s, test_calculate, "4.4.a");
    tmc_register_test(s, test_set, "4.4.b");
        
    return tmc_run_tests(argc, argv, s);
}
