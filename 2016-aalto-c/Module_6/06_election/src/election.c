#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "election.h"

struct votes *read_votes(const char* filename)
{
	FILE *input = fopen(filename, "r");

	long file_size = 0;
	fseek(input, 0L, SEEK_END);
	file_size = ftell(input);
	rewind(input);

	int unique_names = 0;

	struct votes *vlist = malloc(unique_names * sizeof(struct votes));

	char *line = malloc(file_size * sizeof(char));
	int max_char_count = file_size / sizeof(char);
	while (fgets(line, max_char_count, input)) {
		int len = strlen(line);
		line[len - 1] = '\0';

		short found = 0;
		for (int i = 0; i < unique_names; i++) {
			struct votes current = vlist[i];
			if (strcmp(current.name, line) == 0) {
				vlist[i].votes++;
				found = 1;
				break;
			}
		}
		if (!found) {
			unique_names++;
			vlist = realloc(vlist, unique_names * sizeof(struct votes));
			struct votes new;
			strcpy(new.name, line);
			new.votes = 1;
			vlist[unique_names - 1] = new;
		}
	}
	
	free(line);

	vlist = realloc(vlist, (unique_names + 1) * sizeof(struct votes));
	struct votes end;
	end.name[0] = '\0';
	vlist[unique_names] = end;

	fclose(input);

	return vlist;
}

int compare(const void *l, const void *r)
{
	struct votes *left = (struct votes*) l;
	struct votes *right = (struct votes*) r;

	if (left->votes < right->votes) {
		return 1;
	} else if (left->votes > right->votes) {
		return -1;
	} else {
		return strcmp(left->name, right->name);
	}
}

void results(struct votes *vlist)
{
	long len = 0;
	struct votes *ptr = vlist;
	while (strlen(ptr->name) > 0) {
		len++;
		ptr++;
	}

	qsort(vlist, len, sizeof(struct votes), compare);

	for (int i = 0; i < len; i++) {
		printf("%s: %d\n", vlist[i].name, vlist[i].votes);
	}
}
