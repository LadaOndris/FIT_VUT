/* UUDECODE.C */
/* static char sccsid[] = "@(#)uudecode.c	5.3 (Berkeley) 4/10/85"; */

/*
 * uudecode [input]
 *
 * create the specified file, decoding as you go.
 * used with uuencode.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>

/* single character decode */
#define DEC(c)	(((c) - ' ') & 077)

void decode(FILE *in, FILE *out);
int fr(FILE *fd, char *buf, int cnt);
void outdec(char *p, FILE *f, int n);
int file_exists(char *filename)
{
  return (access(filename, 0) == 0);
}

int main(int argc, char *argv[])
{
  FILE *in, *out;
  int mode;
  char dest[128];
  char buf[80];

  if (argc != 2) {
	  printf("Usage: uudecode infile \n");
	  exit(2);
  }

  if ((in = fopen(argv[1], "rt")) == NULL) {
	  perror(argv[1]);
	  exit(1);
  }

  /* search for header line */
  for (;;) {
	  if (fgets(buf, sizeof buf, in) == NULL) {
		  fprintf(stderr, "No begin line\n");
		  exit(3);
	  }
	  if (strncmp(buf, "begin ", 6) == 0)
		  break;
  }
  sscanf(buf, "begin %o %s", &mode, dest);

  if(file_exists(dest))
  {
    fprintf(stderr, "File '%s' exists. Overwrite? (Y/N) ", dest);
    while(kbhit()) getch();
    if(toupper(getche())!='Y') exit(6);
  }

  /* create output file */
  if((out=fopen(dest,"wb")) == NULL)
  {
    perror(dest);
    exit(4);
  }
  chmod(dest, mode);

  decode(in, out);

  if (fgets(buf, sizeof buf, in) == NULL || strcmp(buf, "end\n")) {
    fprintf(stderr, "No end line\n");
    exit(5);
  }
  return 0;
}

/*
* copy from in to out, decoding as you go along.
*/
void decode(FILE *in, FILE *out)
{
  char buf[80];
  char *bp;
  int n;

  for (;;) {
	  /* for each input line */
	  if (fgets(buf, sizeof buf, in) == NULL) {
		  printf("Short file\n");
		  exit(10);
	  }
	  n = DEC(buf[0]);
	  if (n <= 0)
		  break;

	  bp = &buf[1];
	  while (n > 0) {
		  outdec(bp, out, n);
		  bp += 4;
		  n -= 3;
	  }
  }
}

/*
* output a group of 3 bytes (4 input characters).
* the input chars are pointed to by p, they are to
* be output to file f.  n is used to tell us not to
* output all of them at the end of the file.
*/
void outdec(char *p, FILE *f, int n)
{
  int c1, c2, c3;

  c1 = (DEC(*p) << 2) | (DEC(p[1]) >> 4);
  c2 = (DEC(p[1]) << 4) | (DEC(p[2]) >> 2);
  c3 = (DEC(p[2]) << 6) | (DEC(p[3]));
  if (n >= 1)
	  putc(c1, f);
  if (n >= 2)
	  putc(c2, f);
  if (n >= 3)
	  putc(c3, f);
}


/* fr: like read but stdio */
int fr(FILE *fd, char *buf, int cnt)
{
  int c, i;

  for (i=0; i<cnt; i++) {
	  c = getc(fd);
	  if (c == EOF)
		  return(i);
	  buf[i] = c;
  }
  return (cnt);
}

/* end of UUDECODE.C */
