/*
 *  suchar1.c -- demonstrace probl�mu signed/unsigned char
 *
 *  UPOZORN�N�: pouze pro BC 3.1 -- pou��v� #pragma
 *
 *  probl�m:  implicitn� konverze   char --> int
 *
 *        char   ------->   int
 *     ===========================
 *     signed char       -128..127
 *     unsigned char        0..255
 *
 *  porovn�n� znak� (po konverzi, kter� prob�hne v�dy) d�v� r�zn� v�sledek
 *
 *  �E�EN�: explicitn� p�etypovat char na signed char nebo unsigned char
 *
 */

#ifndef __TURBOC__
# error "Pou�ijte Borland C"
#endif

#include <stdio.h>

/**************************************************************************/

#pragma option -K                /* implicitn� unsigned char (BC 3.1) */

int Cmp1(const char c1, const char c2) {
  if(c1 == c2) return 0; /* shoda */
  return (c1 > c2) ? 1 : -1;
}

#pragma option -K-               /* implicitn� signed char (BC 3.1) */

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
  TEST('�','�');        /* shoda je v po��dku v�dy */
  TEST('A','A');

  TEST('A','�');        /* r�zn� v�sledky porovn�n�! */
  TEST('�','A');

  return 0;
}

