#include "source.h"


/* Korsoraattori
 */
void korsoroi(char *dest, const char *src)
{
	const char *niinku = " niinku ";
	const char *totanoin = " totanoin ";
	unsigned int word_count = 0;
	while (*src) {
		if (*src == ' ') {
			word_count++;
			if (word_count % 3 == 0 || word_count % 4 == 0) {
				const char *additional_word =
				    word_count % 3 ==
				    0 ? niinku : totanoin;
				while (*additional_word) {
					*dest = *additional_word;
					dest++;
					additional_word++;
				}
				dest--;
			} else {
				*dest = ' ';
			}
		} else if ((*src == 'k') && (*(src + 1) == 's')) {
			*dest = 'x';
			src++;
		} else if ((*src == 't') && (*(src + 1) == 's')) {
			*dest = 'z';
			src++;
		} else {
			*dest = *src;
		}

		dest++;
		src++;
	}
	*dest = '\0';
}
