#include <stdlib.h>
#include <string.h>
#include "oodi.h"


/* Exercise a: Initialize student record
 * 
 * Parameters:
 * or: Oodi record to be changed (does not need to be allocated)
 * p_student, p_course, p_grade, p_compdate: Values for different structure
 *      fields (must be copied)
 * 
 * Returns: 1 if initialization was succesful, 0 if it failed
 * If student ID is more than 6 characters, initialization fails.
 * 
 * -- Note that structure contains enough space for student ID, but not for
 * course name
 * -- Remember to check that reserved space is not overwritten
 */
int init_record(struct oodi *or, const char *p_student, const char *p_course,
        unsigned char p_grade, struct date p_date)
{
    if (strlen(p_student) > 6) {
	return 0;
    }

    strncpy(or->student, p_student, 6);
    or->student[6] = '\0';

    or->course = malloc(strlen(p_course) + 1);
    strncpy(or->course, p_course, strlen(p_course));
    or->course[strlen(p_course)] = '\0';

    or->grade = p_grade;
    or->compdate = p_date;

    return 1;
}

/* Exercise b: Add a new record to a dynamic array.
 * (Resize the array as needed). All content of the new structure is copied.
 * 
 * Parameters:
 * array: start of an dynamic array (may be NULL, if array is empty)
 * length: current length of the array (number of entries)
 * newrec: new record to be added, all fields need to be copied.
 * 
 * Returns: pointer to the array after adding the new item
 */
struct oodi *add_record(struct oodi *array, unsigned int length, struct oodi newrec)
{
    struct oodi *new_array;
    if (array) {
	new_array = realloc(array, (length + 1) * sizeof(struct oodi));
    } else {
	new_array = malloc(sizeof(struct oodi));
    }

    struct oodi new_entry;
    new_entry.course = malloc(strlen(newrec.course) + 1);

    strcpy(new_entry.course, newrec.course);
    new_entry.course[strlen(newrec.course)] = '\0';

    strcpy(new_entry.student, newrec.student);
    new_entry.student[strlen(newrec.student)] = '\0';

    new_entry.grade = newrec.grade;
    new_entry.compdate = newrec.compdate;
    new_array[length] = new_entry;

    return new_array;
}

/* Exercise c: Change grade and date in existing record.
 * 
 * Parameters:
 * array: beginning of array
 * size: size of array
 * student: student ID to be changed
 * course: course to be changed
 * newgrade: new value for grade
 * newdate: new value for date
 * 
 * Returns: number of entries changed, i.e. either 1 or 0
 */
int change_grade(struct oodi *array, unsigned int size, const char *p_student,
        const char *p_course, unsigned char newgrade, struct date newdate)
{
 
    unsigned int i = 0;
    while (i < size) {
	if (strcmp(array->student, p_student) == 0 && strcmp(array->course, p_course) == 0) {
		array->grade = newgrade;
		array->compdate = newdate;
		return 1;
	}
	i++;
	array++;
    }

    return 0;
}

/* Exercise d: Delete array (and all memory allocated for it)
 * 
 * Parameters:
 * array: beginning of the array
 * 
 * Returns: 1 when array is deleted
 */
int delete_array(struct oodi *array, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
	free(array[i].course);
    }
    free(array);

    return 0;
}
