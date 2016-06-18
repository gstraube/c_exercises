#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "source.h"

/* Don't touch the definition of msgs array! Checker uses this. */
char *msgs[10] = {
	"'6=*w+~)._", "J65+~5+~=0/*69,~+9;,9*~19++=79"
};

void print_number(int number)
{
	if (number < 100) {
		printf("%3d", number);
	} else {
		printf("%d", number);
	}
	printf(" ");

	if (number < 16) {
		printf("0x0%x", number);
	} else {
		printf("0x%x", number);
	}
	printf(" ");

	if (isprint(number) != 0) {
		printf("%c", number);
	} else {
		printf("?");
	}
}

void ascii_chart(char min, char max)
{
	int counter = min;
	for (int i = 0; i < (max - min + 1) / 4; i++) {
		for (int k = 0; k < 3; k++) {
			print_number(counter++);
			printf("\t");
		}
		print_number(counter++);
		printf("\n");
	}
	for (int j = 0; j < (max - min + 1) % 4; j++) {
		print_number(counter++);
		printf("\t");
	}
}

char get_character(int msg, unsigned int cc)
{
	if (msg >= 10 || !msgs[msg])
		return 0;

	if (strlen(msgs[msg]) <= cc)
		return 0;

	return msgs[msg][cc];
}

void secret_msg(int msg)
{
	char enc_char;
	int counter = 0;
	while ((enc_char = get_character(msg, counter++)) != 0) {
		printf("%c", 158 - enc_char);
	}
}
