/*
 *  suchar1.c -- demonstrace problému signed/unsigned char
 *
 *  UPOZORNÌNÍ: pouze pro BC 3.1 -- pou¾ívá #pragma
 *
 *  problém:  implicitní konverze   char --> int
 *
 *        char   ------->   int
 *     ===========================
 *     signed char       -128..127
 *     unsigned char        0..255
 *
 *  porovnání znakù (po konverzi, která probìhne v¾dy) dává rùzný výsledek
 *
 *  ØE©ENÍ: explicitnì pøetypovat char na signed char nebo unsigned char
 *
 */

#ifndef __TURBOC__
# error "Pou¾ijte Borland C"
#endif

#include <stdio.h>

/**************************************************************************/

#pragma option -K                /* implicitnì unsigned char (BC 3.1) */

int Cmp1(const char c1, const char c2) {
  if(c1 == c2) return 0; /* shoda */
  return (c1 > c2) ? 1 : -1;
}

#pragma option -K-               /* implicitnì signed char (BC 3.1) */

int Cmp2(const char c1, const char c2) {
  if(c1 == c2) return 0; /* shoda */
  return (c1 > c2) ? 1 : -1;
}

/**************************************************************************/

#define TEST(a,b) \
        printf(#a " " #b "  %d  %d \n", Cmp1(a,b), Cmp2(a,b));

int main(void)
{
  printf("Test:\n");
  TEST('È','È');        /* shoda je v poøádku v¾dy */
  TEST('A','A');

  TEST('A','È');        /* rùzné výsledky porovnání! */
  TEST('È','A');

  return 0;
}

