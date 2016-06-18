#include <stdio.h>
#include "source.h"


#ifndef MAWKKE
// longer solution by Pasi

/* 03-mastermind
 */
void mastermind(const int *solution, const int *guess, char *result,
		unsigned int len)
{
	for (unsigned int i = 0; i < len; i++) {
		char symbol = '-';
		for (unsigned int j = 0; j < len; j++) {
			if (guess[i] == solution[j]) {
				symbol = '*';
				if (i == j) {
					symbol = '+';
					break;
				}
			}
		}
		result[i] = symbol;
	}
}
#endif
