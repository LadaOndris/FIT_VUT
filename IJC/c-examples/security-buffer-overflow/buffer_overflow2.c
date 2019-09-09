/*
 *
 * demonstrace zaludne chyby typu BUFFER OVERFLOW
 *
 * zkuste:
 *  - prelozit bez optimalizace:   gcc 
 *  - prelozit s optimalizaci:     gcc -O3
 *  - program valgrind
 *
 */

#include <stdio.h>

#define N       10		/* vhodna velikost */
#define ERR      1		/* o kolik prekrocime meze - ZKUSTE 1..5 */
#define VAL    'A'		/* CO zapisujeme je take vyznamne - ZKUSTE '\0' */

int main()
{
    int i;
    char pole[N];

    printf("start zapisu (VAL='\\%o'):\n", VAL);

    for (i = 0; i < N + ERR; i++) {	/* <<< zde je hruba chyba */
	printf("  nasleduje: pole[%d] = VAL %s\n",
	       i, (i >= N) ? "(>limit!)" : "");
	pole[i] = VAL;		/* chyba typu BUFFER OVERFLOW pro i>=N */
    }

    printf("konec zapisu, i=%d\n", i);

    /*** chyba se nemusi projevit pro male ERR (zarovnani promenne i) */
    /*** nebo se program muze zacyklit pro VAL='\0' (prepise promennou i) */
    /*** nebo muze havarovat pokud je i v registru a prepise navratovou adresu */
    /*** je mozne i jine chovani ... */

    printf("konec.\n");
    return 0;
}
