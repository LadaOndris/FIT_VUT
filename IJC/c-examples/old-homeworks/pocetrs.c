/* pocetrs.c
 * Jazyk C -- poèítání øádkù a slov 
 */

#include <stdio.h>

#define TRUE   1
#define FALSE  0

long pocet_znaku=0;
long pocet_radku=0;
long pocet_slov=0;
long znaku_ve_slovech=0;

#define  ZNAK_SLOVA(c)  (!(c==' ' || c=='\n' || c=='\t'))

/*
 *  main - program poèítá øádky a slova ve stdin
 */
int main(void)
{
  int c;
  int je_slovo=FALSE;

  while((c=getchar()) != EOF)
  {
    pocet_znaku++;
    if(c=='\n') pocet_radku++;
    if(ZNAK_SLOVA(c))
    {
      znaku_ve_slovech++;
      if(!je_slovo)
      {
        je_slovo = TRUE;
        pocet_slov++;
      }
    }
    else
    {
      je_slovo = FALSE;
    }
  } /* while */

  printf("Poèet slov : %ld\n", pocet_slov);
  printf("Poèet øádkù: %ld\n", pocet_radku);
  if(pocet_slov>0)
    printf("Prùmìrnı poèet znakù ve slovì: %4.1f\n",
                (double)znaku_ve_slovech/pocet_slov);
  if(pocet_radku>0)
    printf("Prùmìrnı poèet znakù na øádku: %5.1f\n",
                (double)pocet_znaku/pocet_radku-1);
  return 0;
}

/* konec */
