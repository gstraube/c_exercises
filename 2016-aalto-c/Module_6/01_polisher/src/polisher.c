#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "polisher.h"


/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
	FILE *input = fopen(filename, "r");
	if (input == NULL) {
		return NULL;
	}
	fseek(input, 0, SEEK_END);
	long size = ftell(input);
	rewind(input);

	char *content = malloc(sizeof(char) * (size + 1));
	fread(content, 1, size, input);
	content[size] = '\0';

	return content;
}


/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input)
{
	char *content = input;
	unsigned int length = 0;

	while (*content) {
		length++;
		content++;
	}
	content = input;

	char *polished = malloc(sizeof(char) * (length + 1));
	memset(polished, 0, sizeof(char) * (length + 1));
	char *ret_polished = polished;

	int in_multi_line_comment = 0;
	int in_single_line_comment = 0;
	for (unsigned int i = 0; i < length - 1; i++) {
		if (content[i] == '/' && (content[i + 1] == '/' || content[i + 1] == '*')) {
			if (content[i + 1] == '/' && !in_multi_line_comment) {
				in_single_line_comment = 1;
			} else {
				in_multi_line_comment = 1;
			}
		} else if (content[i] == '\n' && in_single_line_comment) {
			in_single_line_comment = 0;
		} else if (content[i] == '*' && content[i + 1] == '/') {
			in_multi_line_comment = 0;
			i++;
		} else {
			if (!in_single_line_comment && !in_multi_line_comment) {
				*polished = content[i];
				polished++;
			}
		}	
	}

	if (!in_single_line_comment && !in_multi_line_comment) {
		*polished = content[length - 1];
		polished++;
	}

	*polished = '\0';

	free(input);

	return ret_polished;
}

int calc_diff(char *line, unsigned int pad_len)
{
	int current_pad_len = 0;
	while (isspace(*line)) {
		current_pad_len++;
		line++;
	}

	return pad_len - current_pad_len;
}

int get_indent(char *line) 
{
	int indent = 0;
	while (*line) {
		if (*line == '{') {
			indent++;
		} else if (*line == '}') {
			indent--;
		}
		line++;
	}

	return indent;
}

/* Indent the C-code at memory block <indent>. String <pad> represents
 * one block of indentation. Only opening curly braces '{' increase the
 * indentation level, and closing curly braces '}' decrease the indentation level.
 * Return the pointer to the code after modification.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *indent(char *input, const char *pad)
{
	char *content = malloc(sizeof(char) * (strlen(input) + 1));
	memset(content, 0, sizeof(char) * (strlen(input + 1)));
	strcpy(content, input);

	char *output = malloc(sizeof(char) * (strlen(input) + 1));
	memset(output, 0, sizeof(char) * (strlen(input) + 1));
	strcpy(output, input);
	unsigned int pos = 0;
	unsigned int len = strlen(output) + 1; 

	int indentation_level = 0;
	unsigned int pad_len = strlen(pad);

	char **paragraphs = malloc(sizeof(char*));
	unsigned int count = 0;

	char *curr = content;
	unsigned int char_count = 0;
	short newline_count = 0;
	char *paragraph = malloc(sizeof(char) * (strlen(input) + 1));
	memset(paragraph, 0, sizeof(char) * (strlen(input) + 1));
	int *trailing_lines = malloc(sizeof(int));
	trailing_lines[0] = 0;

	while (*curr) {
		if (*curr == '\n') {
			if (newline_count <= 1) {
				paragraph[char_count] = *curr; 
			}

			newline_count++;
		} else {
			if (newline_count > 1) {
				paragraph[char_count] = '\0';
				paragraphs[count] = malloc(sizeof(char) * (strlen(input) + 1));
				memset(paragraphs[count], 0, sizeof(char) * (strlen(input) + 1));
				strcpy(paragraphs[count], paragraph);
				free(paragraph);
				paragraph = malloc(sizeof(char) * (strlen(input) + 1));
				memset(paragraph, 0, sizeof(char) * (strlen(input) + 1));

				trailing_lines[count] = newline_count - 1;

				count++;
				paragraphs = realloc(paragraphs, sizeof(char*) * (count + 1));
				trailing_lines = realloc(trailing_lines, sizeof(int) * (count + 1));
				trailing_lines[count] = 0;

				char_count = 0;

			}

			paragraph[char_count] = *curr;
			newline_count = 0;
		}	
		curr++;
		char_count++;
	}

	paragraph[char_count] = '\0';
	paragraphs[count] = malloc(sizeof(char) * (strlen(input) + 1));
	memset(paragraphs[count], 0, sizeof(char) * (strlen(input) + 1));
	strcpy(paragraphs[count], paragraph);

	count++;

	for (unsigned int i = 0; i < count; i++) {
		char *line = strtok(paragraphs[i], "\n");

		while (line != NULL) {
			int diff = calc_diff(line, pad_len);
			len = len + diff * indentation_level + trailing_lines[i];

			output = realloc(output, sizeof(char) * (len + trailing_lines[i] + 1)); 
			output[len + trailing_lines[i]] = '\0';

			int indent = get_indent(line);
			short indented = 0;
			short read_else = 0;

			if (line[0] == '}') { 
				if (strstr(line, "else")) {
					indentation_level = indentation_level - 1; 
					read_else = 1;
				} else {
					indentation_level = indentation_level + indent; 
				}
				indented = 1;
			}

			for (int i = 0; i < indentation_level; i++) {
				for (unsigned int j = 0; j < pad_len; j++) {
					output[pos] = pad[j];
					pos++;
				}
			}

			if (!indented) {
				indentation_level = indentation_level + indent;
			}

			if (read_else) {
				indentation_level++;

			}

			while (isspace(*line)) {
				line++;
			}

			while (*line) {
				output[pos] = *line;
				pos++;
				line++;
			}
			output[pos] = '\n';
			pos++;


			line = strtok(NULL, "\n");
		}

		if (i < count - 1) {
			for (int j = 0; j < trailing_lines[i]; j++) {
				output[pos] = '\n';
				pos++;
			}
		}
	}

	for (unsigned int i = 0; i < count; i++) {
		free(paragraphs[i]);
	}

	free(paragraph);
	free(paragraphs);
	free(trailing_lines);
	free(input);
	free(content);

	output[pos] = '\0';

	return output;
}
