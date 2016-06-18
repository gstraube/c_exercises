#include <stdio.h>
#include <stdlib.h>
#include "ships.h"

const unsigned int xsize = 10;
const unsigned int ysize = 10;
const unsigned int shiplen = 3;

/* implement these functions */

/* Task a: Place <num> ships on the game map.
 */
void set_ships(unsigned int num)
{
	for (unsigned int i = 0; i < num; i++) {
		int xpos;
		int ypos;
		int dir;
		do {
			xpos = rand() % xsize;
			ypos = rand() % ysize;
			dir = rand() % 2;
		} while (place_ship(xpos, ypos, dir) == 0);
	}
}


/* Task b: print the game field
 */
void print_field(void)
{
	for (unsigned int i = 0; i < ysize; i++) {
		for (unsigned int j = 0; j < xsize; j++) {
			if (is_visible(j, i)) {
				printf("%c", is_ship(j, i));
			} else {
				printf("?");
			}
		}
		printf("\n");
	}
}


/* Task c: Ask coordinates (two integers) from user, and shoot the location.
 * Returns -1 if user gave invalid input or coordinates, 0 if there was no ship
 * at the given location; and 1 if there was a ship hit at the location.
 */
int shoot(void)
{
	unsigned int xpos, ypos;
	char space;
	int ret_x = scanf("%u", &xpos);
	int ret_space = scanf("%c", &space);
	int ret_y = scanf("%u", &ypos);

	if (ret_x == 0 || ret_y == 0 || ret_space == 0) {
		return -1;
	}

	if (xpos >= xsize || ypos >= ysize) {
		return -1;
	}

	checked(xpos, ypos);
	if (is_ship(xpos, ypos) == '+') {
		hit_ship(xpos, ypos);
		return 1;
	}

	return 0;
}

/* Task d: Returns 1 if game is over (all ships are sunk), or 0 if there
 * still are locations that have not yet been hit. <num> is the number of
 * ships on the game map. It is assumed to be the same as in the call to
 * set_ships function.
 */
int game_over(unsigned int num)
{
	unsigned int hits = 0;
	for (unsigned int i = 0; i < xsize; i++) {
		for (unsigned int j = 0; j < ysize; j++) {
			if (is_ship(i, j) == '#') {
				hits++;
			}
		}
	}
	if (hits == num * 3) {
		return 1;
	}
	return 0;
}
