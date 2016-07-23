#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "source.h"

int *join_arrays(unsigned int num1, int *array1, unsigned int num2, int *array2, unsigned int num3, int* array3) 
{
	unsigned int num = num1 + num2 + num3;	
	int *array = malloc(num * sizeof(int));
	memcpy(array, array1, num1 * sizeof(int));
	memcpy(array + num1, array2, num2 * sizeof(int));
	memcpy(array + num1 + num2, array3, num3 * sizeof(int));

	return array;
}
