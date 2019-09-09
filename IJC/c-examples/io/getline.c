/* getline.c
 *
 * implementace funkce:
 *   int getline(char *s, int n, FILE *f);
 *
 * pro test prelozte: gcc -DTEST getline.c  
 *
 */

#include <stdio.h>    /* FILE, getc(), printf(), EOF */
#include <assert.h>

#include "getline.h"  /* rozhraní modulu */

/* 
 * getline(s,n,f) --- funkce pro cteni radku ze souboru
 *
 * parametry:
 *    s - pole pro ulozeni prectenych znaku
 *    n - delka pole znaku (musi byt >1)
 *        pokud je radek delsi, precte pouze n-1 znaku a zbytek preskoci
 *    f - soubor otevreny v textovem rezimu
 *
 * vraci: 
 *    delku retezce s nebo EOF
 * 
 */
int getline(char *s, int n, FILE * f)
{
    int i = 0;
    int c;
    n--;

    assert(n > 0);		/* kontrola */

    while ((c = getc(f)) != EOF) {
	if (c == '\n')		/* '\n' se do vysledku neulozi */
	    break;
	if (i < n)
	    s[i++] = c;
    }

    if (i == 0 && c == EOF)	/* konec souboru */
	return EOF;

    s[i] = '\0';

    return i;			/* vraci delku retezce s */
}

