/* getline-test.c
 *
 * test funkce getline z modulu getline.c
 * nutno sestavit s getline.o
 *
 */

#include <stdio.h>    /* FILE, getc(), printf(), EOF */
#include <stdlib.h>   /* exit() */

#include "getline.h"  /* rozhraní modulu */

#define N 80

int main(int argc, char *argv[])
{
    FILE *f = stdin;
    char s[N];			/* pole pro znaky */
    int len;
    long ln = 0;

    if (argc > 2) {
	fprintf(stderr, "Usage: %s [file]\n\n", argv[0]);
	exit(1);
    }

    if (argc == 2) {
	f = fopen(argv[1], "r");
	if (f == NULL) {
	    fprintf(stderr, "Can't open file: %s\n", argv[1]);
	    exit(2);
	}
    }

    while ((len = getline(s, sizeof(s), f)) != EOF) {
	/* zpracovani radku */
	ln++;
	printf("%5ld %2d |%s|\n", ln, len, s);
    }

    return 0;
}

