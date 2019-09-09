/*  sum.c 
 *  Jazyk C -- funkce AtoL() a p��klad pou�it�
 */

#include <stdio.h>
#include <ctype.h>

long AtoL(const char *s);         /* deklarace funkce AtoL */

int main(int argc, char *argv[]) {
  long suma = 0;                  /* inicializace */
  int  i;

  for(i=1; i<argc; i++)           /* pro v�echny argumenty programu */
    suma += AtoL(argv[i]);        /* s��t� hodnoty */

  printf ("%ld\n", suma);         /* tisk sou�tu */
  return 0;
}

/*
 *  funkce AtoL - p�evede �et�zec na ��slo long
 *  v p��pad� chyby vrac� nulu, nekontroluje p�ete�en�
 */
long AtoL(const char *s) {             /* definice funkce AtoL */
  long cislo = 0;
  int  zaporne = 0;

  while(isspace(*s)) s++;              /* p�esko�� �vodn� mezery */

  if(*s=='-' || *s=='+') {             /* zpracuje p��padn� znam�nko */
    zaporne = (*s=='-');
    s++;
  }
  if(*s=='0') {
    s++;
    if(toupper(*s)=='X') {             /* �estn�ctkov� ��slo */
      s++;
      while(isxdigit(*s)) {            /* dokud jsou ��slice */
        int c = toupper(*s++);         /* ��slice */
        cislo = 16 * cislo;
        if(c>='A')
          cislo += c - 'A' + 10;
        else
          cislo += c - '0';
      }
    }
    else {                             /* osmi�kov� ��slo */
      while( *s > '0' && *s < '8')     /* dokud jsou ��slice */
        cislo = 8 * cislo + (*s++ - '0');
    }
  }
  else                                 /* des�tkov� ��slo */
    while(isdigit(*s))                 /* dokud jsou ��slice */
      cislo = 10 * cislo + (*s++ - '0');

  return zaporne ? -cislo : cislo;
}

/* konec */
