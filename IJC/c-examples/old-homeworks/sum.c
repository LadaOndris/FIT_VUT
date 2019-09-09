/*  sum.c 
 *  Jazyk C -- funkce AtoL() a pøíklad pou¾ití
 */

#include <stdio.h>
#include <ctype.h>

long AtoL(const char *s);         /* deklarace funkce AtoL */

int main(int argc, char *argv[]) {
  long suma = 0;                  /* inicializace */
  int  i;

  for(i=1; i<argc; i++)           /* pro v¹echny argumenty programu */
    suma += AtoL(argv[i]);        /* sèítá hodnoty */

  printf ("%ld\n", suma);         /* tisk souètu */
  return 0;
}

/*
 *  funkce AtoL - pøevede øetìzec na èíslo long
 *  v pøípadì chyby vrací nulu, nekontroluje pøeteèení
 */
long AtoL(const char *s) {             /* definice funkce AtoL */
  long cislo = 0;
  int  zaporne = 0;

  while(isspace(*s)) s++;              /* pøeskoèí úvodní mezery */

  if(*s=='-' || *s=='+') {             /* zpracuje pøípadné znaménko */
    zaporne = (*s=='-');
    s++;
  }
  if(*s=='0') {
    s++;
    if(toupper(*s)=='X') {             /* ¹estnáctkové èíslo */
      s++;
      while(isxdigit(*s)) {            /* dokud jsou èíslice */
        int c = toupper(*s++);         /* èíslice */
        cislo = 16 * cislo;
        if(c>='A')
          cislo += c - 'A' + 10;
        else
          cislo += c - '0';
      }
    }
    else {                             /* osmièkové èíslo */
      while( *s > '0' && *s < '8')     /* dokud jsou èíslice */
        cislo = 8 * cislo + (*s++ - '0');
    }
  }
  else                                 /* desítkové èíslo */
    while(isdigit(*s))                 /* dokud jsou èíslice */
      cislo = 10 * cislo + (*s++ - '0');

  return zaporne ? -cislo : cislo;
}

/* konec */
