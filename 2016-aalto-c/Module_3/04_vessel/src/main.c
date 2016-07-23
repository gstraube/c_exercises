#include <string.h>
#include <stdio.h>
#include "source.h"

int main()
{
    /* testing exercise. Feel free to modify */
    struct cargo c = { "Bananas", 10000, 1500 };

    struct vessel v = create_vessel( "Apinalaiva", 180, 8.5, c );

    printf("Length of the name: %u\n", strlen(v.name));

    // shortening the name, if it is very long
    v.name[19] = 0;

    if (v.length < 1)
	printf("Length is too short!\n");

    if (v.depth > 100)
	printf("Submarines not allowed\n");

    printf("cargo: %s\n", v.crg.title);

    print_vessel(&v);
}
