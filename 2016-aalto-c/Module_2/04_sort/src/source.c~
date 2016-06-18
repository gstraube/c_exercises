#include "source.h"

/* Selection sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void sort(int *start, int size)
{
	for (int i = 0; i < size; i++) {
		int min = start[i];
		int swap_pos = i;
		for (int j = i + 1; j < size; j++) {
			if (start[j] < min) {
				min = start[j];
				swap_pos = j;
			}
		}
		start[swap_pos] = start[i];
		start[i] = min;
	}
}
