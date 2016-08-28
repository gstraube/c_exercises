#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "getopt.h"

/* a) Returns the list of options given on command line arguments
 * indicated in <argc> and <argv>. These parameters are used similarly as
 * in the main function.
 * 
 * Function returns pointer to the start of linked list that contains the
 * options.
 */
struct options *get_options(int argc, char *argv[])
{
	struct options *head = NULL;
	struct options *prev = NULL;
	short has_read_arg = 0;
	for (int i = 0; i < argc; i++) {
		struct options *element = malloc(sizeof(struct options));
		element->next = NULL;
		element->optarg = NULL;
		element->optchar = ' ';
		if (argv[i][0] == '-') {
			element->optchar = argv[i][1];
			if (!has_read_arg) {
				head = element; 
				prev = element;
			} else {
				prev->next = element;
				prev = element;
			}
			has_read_arg = 1;
		} else {
			free(element);
		}

		if (i < argc - 1 && argv[i + 1][0] != '-') {
			element->optarg = malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));
			strcpy(element->optarg, argv[i + 1]);
		}
	}

	return head;
}

/* a) Free the memory allocated for the linked list at <opt>.
*/
void free_options(struct options *opt)
{
	struct options *ptr = opt->next;

	if (opt->optarg) {
		free(opt->optarg);
	}

	while (ptr) {
		struct options *tmp = ptr;
		if (ptr->optarg) {
			free(ptr->optarg);
		}
		ptr = ptr->next;
		free(tmp);
	}

	free(opt);
}

/* b) Returns non-zero if option character <optc> is included in the
 * linked list pointed by <opt>
 */
int is_option(struct options *opt, char optc)
{
	struct options *ptr = opt;
	while (ptr) {
		if (ptr->optchar == optc) {
			return 1;
		}
		ptr = ptr->next;
	}

	return 0;
}

/* b) Returns the argument given with option <optc>. If argument or
 * the option was not given, the function returns NULL.
 */
char *get_optarg(struct options *opt, char optc)
{
	struct options *ptr = opt;
	while (ptr) {
		if (ptr->optchar == optc) {
			return ptr->optarg;
		}
		ptr = ptr->next;
	}

	return NULL;
}
