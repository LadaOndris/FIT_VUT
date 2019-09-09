/*
 *
 * demonstrace zaludne chyby typu BUFFER OVERFLOW
 *
 * zkuste:
 *  - program valgrind
 *  - sestavit s knihovnou "Electric Fence": -lefence
 *  - pripadne dalsi nastroje (dmalloc,...)
 *
 */

#include <stdio.h>		/* printf       */
#include <stdlib.h>		/* malloc, free */

#define N       10		/* vhodna velikost */
#define ERR      1		/* o kolik prekrocime meze - ZKUSTE 1..5 */

int main()
{
    int *ptr;
    int i;

    printf("malloc:\n");
    ptr = (int *) malloc(N * sizeof(int));

    printf("start zapisu:\n");

    for (i = 0; i < N + ERR; i++) {	/* <<< zde je hruba chyba */
	printf("  nasleduje: ptr[%d] = 0 %s\n",
	       i, (i >= N) ? "(>limit!)" : "");
	ptr[i] = 0;		/* chyba typu BUFFER OVERFLOW pro i>=N */
    }

    printf("konec zapisu, dalsi malloc:\n");
    /*** a zde se projevi prepsani pameti za koncem dynamickeho pole: */
    ptr = (int *) malloc(sizeof(int));	/* dalsi chyba: MEMORY LEAK */

    printf("free:\n");
    /*** nebo pripadne zde ? */
    free(ptr);

    /*** nebo se nemusi projevit vubec (zarovnavani velikosti */
    /*** alokovanych bloku na nasobky 16 a podobne) */

    printf("konec.\n");
    return 0;
}
