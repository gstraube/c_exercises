#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "myprint.h"

int myprint(const char *string, ...)
{
	va_list args;
	const char *ptr = string;
	int args_num = 0;
	
	while ((ptr = strchr(ptr, '&'))) {
		args_num++;
		ptr++;
	}

	va_start(args, string);

	for (unsigned int i = 0; i < strlen(string); i++) {
		if (string[i] == '&') {
			int num = va_arg(args, int);
			printf("%d", num);
		} else {
			fputc(string[i], stdout);
		}
	}

	return args_num;
}
