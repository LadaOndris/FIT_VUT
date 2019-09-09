/* strcmp.c
 * Jazyk C -- porovnání øetìzcù
 */

#include <stdio.h>
#include <string.h>

int StrCmp(const char *s1, const char *s2);	/* porovnání øetìzcù */

/**************** TEST ********************/
int main(void)
{
    char s1[100], s2[100];
    printf("TEST: %d %d %d \n", StrCmp("aaa", "aab"),
	   StrCmp("bbb", ""), StrCmp("", ""));
    /*
     * následuje ètení dvou øetìzcù ze vstupu
     */
    fprintf(stderr, "zadejte první øetìzec: ");
    do {
	fgets(s1, sizeof(s1), stdin);	// kontroluje poèet naètených znakù
    } while (s1[strlen(s1) - 1] != '\n');
    s1[strlen(s1) - 1] = '\0';	// odstraní '\n' na konci
    fprintf(stderr, "zadejte druhý øetìzec: ");
    do {
	fgets(s2, sizeof(s2), stdin);
    } while (s2[strlen(s2) - 1] != '\n');
    s2[strlen(s2) - 1] = '\0';
    printf("výsledek funkce StrCmp: ");
    int r = StrCmp(s1, s2);
    printf("%d\n", r);
    printf("\n \"%s\" %s \"%s\" \n\n",
	   s1, (r < 0 ? "<" : (r == 0 ? "==" : ">")), s2);
    return 0;
}

/*
 *  funkce StrCmp - porovná dva zadané øetìzce
 *                  nezávisle na signed/unsigned cahr
 */
int StrCmp(const char *s1, const char *s2)
{
    while (*s1 == *s2) {
	if (*s1 == '\0')
	    return 0;		/* jsou stejné */
	s1++;
	s2++;
    }
    return (*(unsigned char *) s1 > *(unsigned char *) s2) ? 1 : -1;
}

/* konec */
