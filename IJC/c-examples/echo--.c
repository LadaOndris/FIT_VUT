/*
 * - vypis argumentu programu:  argc, argv
 * - ukazka, co tiskne printf pro %s a NULL
 *
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    printf("argc = %d\n", argc);
    for (i = 0; i <= argc; i++)	/* CHYBA: <= vypisuje vse vcetne NULL na konci */
	printf("argv[%d] = \"%s\"\n", i, argv[i]);

    return 0;
}
