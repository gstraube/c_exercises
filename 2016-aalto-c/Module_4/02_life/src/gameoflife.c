#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gameoflife.h"


/* Exercise a: Allocates needed memory for the field structure and
 * the actual game field. 'xsize' and 'ysize' indicate the horizontal and
 * vertical dimensions of the field.
 * 
 * Returns: pointer to the Field structure allocated by this function.
 */
Field *createField(unsigned int xsize, unsigned int ysize)
{

	Field *field = malloc(sizeof(Field));
	field->xsize = xsize;
	field->ysize = ysize;
	field->cells = malloc(ysize * sizeof(State*));
	for (unsigned int i = 0; i < ysize; i++) {
		field->cells[i] = malloc(xsize * sizeof(State));
		for (unsigned int j = 0; j < xsize; j++) {
			field->cells[i][j] = DEAD;
		}
	}

	return field;
}

/* Free memory allocated for field <f>.
 */
void releaseField(Field *f)
{
	for (unsigned int i = 0; i < f->ysize; i++) {
		free(f->cells[i]);
	}
	free(f->cells);
	free(f);
}

/* Exercise b: Initialize game field by setting exactly <n> cells into
 * ALIVE state in the game field <f>.
 */
void initField(Field *f, unsigned int n)
{
	unsigned int i = 0;
	while (i < n) {
		unsigned int ypos, xpos;
		ypos = rand() % f->ysize;
		xpos = rand() % f->xsize;

		if (f->cells[ypos][xpos] == DEAD) {
			f->cells[ypos][xpos] = ALIVE;
			i++;
		}
	}
}

/* Exercise c: Output the current state of field <f>.
 */
void printField(const Field *f)
{
	for (unsigned int i = 0; i < f->ysize; i++) {
		for (unsigned int j = 0; j < f->xsize; j++) {
			if (f->cells[i][j] == ALIVE) {
				printf("*");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}

unsigned int get_alive_neighbors(int ypos, int xpos, Field field) {
	unsigned int count = 0;
	int ysize = field.ysize;
	int xsize = field.xsize;
	for (int i = ypos - 1; i <= ypos + 1; i++) {
		for (int j = xpos - 1; j <= xpos + 1; j++) {
			if (i == ypos && j == xpos) {
				continue;
			}
			if (i < 0 || i >= ysize) {
				continue;
			}
			if (j < 0 || j >= xsize) {
				continue;
			}
			if (field.cells[i][j] == ALIVE) {
				count++;
			}
		}
	}

	return count;
}

/* Exercise d: Advance field <f> by one generation.
 */
void tick(Field *f)
{
	Field current_field;
	State **current_cells = malloc(f->ysize * sizeof(State*));
	for (unsigned int i = 0; i < f->ysize; i++) {
		current_cells[i] = malloc(f->xsize * sizeof(State));
		memcpy(current_cells[i], f->cells[i], f->xsize * sizeof(State));
	}
	current_field.cells = current_cells;
	current_field.ysize = f->ysize;
	current_field.xsize = f->xsize;

	for (unsigned int i = 0; i < f->ysize; i++) {
		for (unsigned j = 0; j < f->xsize; j++) {
			unsigned int alive_neighbors = get_alive_neighbors(i, j, current_field);
			if (current_cells[i][j] == ALIVE) {
				if (alive_neighbors < 2 || alive_neighbors > 3) {
					f->cells[i][j] = DEAD;
				} 
			} else {
				if (alive_neighbors == 3) {
					f->cells[i][j] = ALIVE;
				}
			}	
		}
	}

	for (unsigned int i = 0; i < f->ysize; i++) {
		free(current_cells[i]);
	}
	free(current_cells);
}
