#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "queue.h"
#include "queuepriv.h"

Queue *Queue_init(void)
{
	Queue *q = calloc(1, sizeof(Queue));
	return q;
}

int Queue_enqueue(Queue *q, const char *id, const char *name)
{
	if (strlen(id) <= 6) {
		struct student *new_student = malloc(sizeof(struct student));
		strcpy(new_student->id, id);
		new_student->name = malloc(strlen(name) + 1);
		strcpy(new_student->name, name);
		new_student->name[strlen(name)] = '\0';	
		new_student->next = NULL;

		if (q->last != NULL) {
			q->last->next = new_student;
		}

		q->last = new_student;

		if (q->first == NULL) {
			q->first = new_student;
		}

		return 1;
	}

	return 0;
}

char *Queue_firstID(Queue *q)
{
	if (q && q->first)
		return q->first->id;
	else
		return NULL;
}

char *Queue_firstName(Queue *q)
{
	if (q && q->first)
		return q->first->name;
	else
		return NULL;
}

int Queue_dequeue(Queue *q)
{
	if (q->first) {
		free(q->first->name);
		struct student *next = q->first->next;
		free(q->first);
		if (next != NULL) {
			q->first = next;
		} else {
			q->first = NULL;
			q->last = NULL;
		}

		return 1;
	} 

	return 0;
}

int Queue_drop(Queue *q, const char *id)
{
	struct student *current = q->first;
	struct student *prev = current;
	while (current) {
		if (strcmp(current->id, id) == 0) {
			if (current == q->first) {
				if (current == q->last) {
					q->first = NULL;
					q->last = NULL;
				} else {
					q->first = current->next;
				}
				free(current->name);
				free(current);

				return 1;
			} 
		        if (current == q->last) {
				q->last = prev;
				prev->next = NULL;

				free(current->name);
				free(current);

				return 1;
			}

			prev->next = current->next;
			free(current->name);
			free(current);

			return 1;	
		}
		prev = current;
		current = current->next;
	}
	return 0;
}

void Queue_delete(Queue *q)
{
    if (q) {
        while(Queue_dequeue(q));
        free(q);
    }
}
