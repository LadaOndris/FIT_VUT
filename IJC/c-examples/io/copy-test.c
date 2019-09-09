/* test-copy.c 
 * 
 * test rychlosti kopírování souboru
 *   - znak po znaku
 *   - po blocích
 *
 * pou¾ijte dlouhý soubor (mìøení není pøíli¹ pøesné)
 * pozorujte vliv systémových vyrovnávacích pamìtí
 *
 * Pozor -- pøepisuje cílový soubor bez dotazu
 * 
 * Pøíklad (Linux 2.2.18/PIII-733/128MB/GCC -O6):
 *     test-copy testfile10000KB testfile2
 *   výstup:
 *     èas kopírování souboru:
 *     copy1: 1.6 s
 *     copy2: 0.08 s       <<< zde je vidìt zrychlení
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*copy_function_pointer_t)(FILE*f1,FILE*f2);

/* funkce meøící èas kopie */
double copy(const char * from, 
            const char * to, 
            copy_function_pointer_t function) {
  clock_t clock_time;
  FILE *f1 = fopen(from,"r");
  FILE *f2 = fopen(to,"w");
  if(f1==NULL || f2==NULL) {
    fprintf(stderr, "Soubor nelze otevrit\n");
    exit(2);
  }
  clock_time = clock();
  function(f1,f2); /* volání testované funkce */
  clock_time = clock() - clock_time;
  fclose(f1);
  fclose(f2);
  return (double) clock_time / CLOCKS_PER_SEC;
}

/**************************************************************************/

void copy1(FILE*f1,FILE*f2) { /* kopie znak po znaku - neefektivní */
    int c;
    while( (c=getc(f1)) != EOF )
      putc(c,f2); 
}

#define BUFSIZE 16384         /* mù¾ete zvìt¹it */
void copy2(FILE*f1,FILE*f2) { /* kopie po blocích znakù - efektivní */
  static char buffer[BUFSIZE];
  int n;
  while( (n=fread(buffer,1,BUFSIZE,f1)) != 0 )
    fwrite(buffer,1,n,f2); 
}

/**************************************************************************/

int main(int argc, char *argv[]) { 
  if(argc != 3) {
    fprintf(stderr, "Pou¾ití: %s soubor_odkud soubor_kam\n", argv[0]);
    return 1;
  }
  copy(argv[1], argv[2], copy2); /* naplní sys. vyrovnavácí pamìti */
  printf("èas kopírování souboru:\n");  
  printf("copy1: %g s\n", copy(argv[1], argv[2], copy1) );  
  printf("copy2: %g s\n", copy(argv[1], argv[2], copy2) );  
  return 0;
}

