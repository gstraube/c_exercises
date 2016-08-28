/* monster.c -- Implementation of monster actions
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
	char name[20];  // Name of monster
	char sign;  // character to show it on map
	unsigned int hplow;  // lowest possible initial maxhp
	unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
	{ "Goblin", 'G', 6, 10},
	{ "Rat", 'R', 3, 5},
	{ "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
	printf("%s punches you! ", monst->name);
	int hitprob = 50;
	int maxdam = 4;
	if (rand() % 100 < hitprob) {
		printf("Hit! ");
		int dam = rand() % maxdam + 1;
		printf("Damage: %d ", dam);
		game->hp = game->hp - dam;
		if (game->hp <= 0)
			printf("You died!");
		printf("\n");
	} else {
		printf("Miss!\n");
	}
}

double calc_dist(Point pos1, Point pos2)
{
	return sqrt(pow(pos1.y - pos2.y, 2) + pow(pos1.x - pos2.x, 2));
}

/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */

typedef enum {
	TOWARDS,
	AWAY
} Direction;

void move(Game *game, Creature *monst, Direction direction)
{
	Point player_pos = game->position;
	Point monster_pos = monst->pos;
	double orig_dist = calc_dist(monster_pos, player_pos);

	int xpos[3];
	xpos[0] = monster_pos.x - 1 < 1 ? 1 : monster_pos.x - 1;
	xpos[1] = monster_pos.x;
	xpos[2] = monster_pos.x + 1 >= (int) game->opts.mapWidth ? (int) game->opts.mapWidth : monster_pos.x + 1; 

	int ypos[3];
	ypos[0] = monster_pos.y - 1 < 1 ? 1 : monster_pos.y - 1;
	ypos[1] = monster_pos.y;
	ypos[2] = monster_pos.y + 1 >= (int) game->opts.mapHeight ? (int) game->opts.mapHeight : monster_pos.y + 1; 

	double dist = orig_dist;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Point new_pos;
			new_pos.y = ypos[i];
			new_pos.x = xpos[j];
			double distance = calc_dist(new_pos, player_pos);

			if (direction == TOWARDS) {
				if (distance < dist && !isBlocked(game, ypos[i], xpos[j]) && distance > 0) {
					monst->pos.y = new_pos.y;
					monst->pos.x = new_pos.x;
				}
			} else if (direction == AWAY) {
				if (distance > dist && !isBlocked(game, ypos[i], xpos[j]) && distance > 0) {
					monst->pos.y = new_pos.y;
					monst->pos.x = new_pos.x;
				}
			}

		}
	}
}

void moveTowards(Game *game, Creature *monst)
{
	move(game, monst, TOWARDS);
}

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(Game *game, Creature *monst)
{
	move(game, monst, AWAY);
}


/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game)
{
	for (unsigned int i = 0; i < game->numMonsters; i++) {
		Creature monster = game->monsters[i];

		double dist = calc_dist(game->position, monster.pos);
		if (monster.hp == 0) {
			return;
		}

		if (dist == 1.0) {
			monster.attack(game, &game->monsters[i]);
		} else {
			monster.move(game, &game->monsters[i]);
		}
	}
}

/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The monster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game)
{
	game->monsters = malloc(sizeof(Creature) * game->opts.numMonsters);	
	game->numMonsters = 0;
	for (unsigned int i = 0; i < game->opts.numMonsters; i++) {
		Creature creature;

		unsigned int x;
		unsigned int y;

		do {
			x = rand() % game->opts.mapWidth;
			y = rand() % game->opts.mapHeight;
		} while (isBlocked(game, y, x));

		Point pos;
		pos.x = x;
		pos.y = y;

		creature.pos = pos;

		creature.maxhp = 1 + (rand() % 1000);
		creature.hp = creature.maxhp;

		creature.sign = 97 + (rand() % 26);

		for (unsigned int j = 0; j < 19; j++) {
			creature.name[j] = 97 + (rand() % 26);	
		}
		creature.name[19] = '\0';
		
		creature.move = moveTowards;
		creature.attack = attackPunch;

		game->monsters[i] = creature;
		game->numMonsters++;
	}
}

/* Determine whether monster moves towards or away from player character.
*/
void checkIntent(Game *game)
{
	for (unsigned int i = 0; i < game->numMonsters; i++) {
		Creature *m = &game->monsters[i];
		if (m->hp <= 2) {
			m->move = moveAway;
		} else {
			m->move = moveTowards;
		}
		if (m->hp < m->maxhp)
			m->hp = m->hp + 0.1;  // heals a bit every turn
	}
}
