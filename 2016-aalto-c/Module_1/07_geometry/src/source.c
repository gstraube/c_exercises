#include <stdio.h>
#include <math.h>
#include "source.h"


void multi_table(unsigned int xsize, unsigned int ysize)
{
	for (unsigned int i = 1; i <= ysize; i++) {
		for (unsigned int j = 1; j <= xsize; j++) {
			printf("%4d", i * j);
		}
		printf("\n");
	}
}

void draw_triangle(unsigned int size)
{
	for (unsigned int i = 0; i < size; i++) {
		for (unsigned int j = 0; j < size - (i + 1); j++) {
			printf(".");
		}
		for (unsigned int k = size - (i + 1); k < size; k++) {
			printf("#");
		}
		printf("\n");
	}
}

double distance(int x, int y)
{
	return sqrt(x * x + y * y);
}


void draw_ball(unsigned int radius)
{
	for (unsigned int i = 0; i < 2 * radius + 1; i++) {
		for (unsigned int j = 0; j < 2 * radius + 1; j++) {
			if (distance(i - radius, j - radius) <= radius) {
				printf("*");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}
