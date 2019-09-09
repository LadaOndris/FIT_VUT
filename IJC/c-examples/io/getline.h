/* getline.h
 *
 * rozhrani funkce:
 *   int getline(char *s, int n, FILE *f);
 *
 */

#include <stdio.h>  /* FILE */

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

int getline(char *s, int n, FILE * f);

