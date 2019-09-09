/*
 * malloc-overhead.c
 *
 * test rezie dynamicke alokace pameti
 *
 */

#include <stdio.h>		/* printf() */
#include <stdlib.h>		/* malloc(), free() */
#include "hdump.h"

#define SIZE1 1

int main(void)
{
    char *p1;
    char *p2;
    int dif;

    printf("\n");
    printf("malloc() overhead test\n");
    printf("\n");
    p1 = malloc(SIZE1);
    printf("malloc(%d)=%p\n", SIZE1, p1);
    if (p1 == NULL)
	return 1;		/* vzdy kontrolujte */
    *p1 = '1';

    p2 = malloc(SIZE1);
    printf("malloc(%d)=%p\n", SIZE1, p2);
    if (p2 == NULL)
	return 1;		/* vzdy kontrolujte */
    *p2 = '2';

    dif = (char *) p2 - (char *) p1;
    printf("difference=%d\n", dif);

    printf("\n");
    hdump(p1, dif);
    hdump(p2, dif);
    printf("\n");

    free(p1);			/* uvolneni pameti */
    free(p2);			/* uvolneni pameti */

    return 0;
}
