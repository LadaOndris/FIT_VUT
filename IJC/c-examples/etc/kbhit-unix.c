/*
   Subject: Re: kbhit() MSDOS equivalent in Linux

   test kbhit() a readch()

   zdroj: NetNews
*/


#include <unistd.h>  /* read() */
//#include <ctype.h>
#include <termios.h> /* tc*() */

#include "kbhit-unix.h"

static struct termios orig, new;
static int peek = -1;

void kbhit_init()
{
  tcgetattr(0, &orig);
  new = orig;
  new.c_lflag &= ~ICANON;
  new.c_lflag &= ~ECHO;
  new.c_lflag &= ~ISIG;
  new.c_cc[VMIN] = 1;
  new.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new);
}

void kbhit_done()
{
  tcsetattr(0,TCSANOW, &orig);
}


int kbhit()
{

  char ch;
  int nread;

  if(peek != -1) return 1;
  new.c_cc[VMIN]=0;
  tcsetattr(0, TCSANOW, &new);
  nread = read(0,&ch,1);
  new.c_cc[VMIN]=1;
  tcsetattr(0, TCSANOW, &new);

  if(nread == 1) {
   peek = ch;
   return 1;
  }

  return 0;
}

int readch()
{

  unsigned char ch;

  if(peek != -1) {
    ch = peek;
    peek = -1;
    return ch;
  }

  read(0,&ch,1);
  return ch;
}


