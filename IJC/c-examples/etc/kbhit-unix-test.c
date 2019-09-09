/*
   Subject: Re: kbhit() MSDOS equivalent in Linux

   test kbhit() a readch()

   zdroj: NetNews
*/


#include <stdio.h>
#include <ctype.h>
#include <locale.h>

#include "kbhit-unix.h"

int main()
{
  int ch =0;

  setlocale(LC_CTYPE,""); /* localization for test */

  kbhit_init();

  printf("konec = klavesa q nebo ^D \n");

  while(ch != 'q' && ch != '\004') {
    if(kbhit()) {
        ch = readch();
        if(isprint(ch))
          printf("klavesa: '%c'\n", ch);
        else
          printf("klavesa: '\\x%02X'\n", ch);
    }
  }

  kbhit_done();

  return 0;
}


