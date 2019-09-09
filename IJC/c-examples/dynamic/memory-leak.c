/*
 * memory-leak.c
 *
 * test dynamicke alokace pameti
 * zkuste program valgrind pro detekci "memory leak" chyby
 *
 */

#include <stdio.h>		/* printf() */
#include <stdlib.h>		/* malloc(), realloc(), free() */
#include <string.h>		/* memset() */

#define SIZE1 100
#define SIZE2 1000000L		/* zkuste zvetsit, pozor na "optimistickou" alokaci */

int main(void)
{
    void *p = malloc(SIZE1);
    printf("malloc(%d) = %p\n", SIZE1, p);
    if (p == NULL)
	return 1;		/* vzdy kontrolujte */
    memset(p, 1, SIZE1);

    p = realloc(p, SIZE2);
    printf("realloc(p,%ld) = %p\n", SIZE2, p);
    if (p == NULL)
	return 2;
    memset(p, 2, SIZE2);

    p = realloc(p, SIZE1);
    printf("realloc(p,%d) = %p\n", SIZE1, p);
    if (p == NULL)
	return 3;
    memset(p, 3, SIZE1);

#if 0
    free(p);			/* uvolneni pameti - pokud chybi, mame "memory leak" */
    /* zde neni problem, protoze proces konci, ale treba v cyklu
     * a/nebo u dlouhodobe bezicich procesu JE problem */
#endif

    free(NULL);			/* neni problem - viz norma */

    return 0;
}
