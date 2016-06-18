#include <ctype.h>
#include <string.h>
#include "source.h"

/* Count Alpha
 * Count number of alphabetic characters in the given string <str>,
 * and return the count
 */
int count_alpha(const char *str)
{
	char current;
	unsigned int counter = 0;
	while ((current = *str)) {
		if (isalpha(current)) {
			counter++;
		}
		str++;
	}

	return counter;
}


/* Count Substring
 * Count number of occurances of substring <sub> in string <str>,
 * and return the count.
 */
int count_substr(const char *str, const char *sub)
{
	int count = 0;
	const char *str_copy = str;
	char *sub_pos;
	while ((sub_pos = strstr(str_copy, sub))) {
		count++;
		str_copy = sub_pos + strlen(sub);
	}

	return count;
}
