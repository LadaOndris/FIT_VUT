/* test-copy.c 
 * 
 * test rychlosti kop�rov�n� souboru
 *   - znak po znaku
 *   - po bloc�ch
 *
 * pou�ijte dlouh� soubor (m��en� nen� p��li� p�esn�)
 * pozorujte vliv syst�mov�ch vyrovn�vac�ch pam�t�
 *
 * Pozor -- p�episuje c�lov� soubor bez dotazu
 * 
 * P��klad (Linux 2.2.18/PIII-733/128MB/GCC -O6):
 *     test-copy testfile10000KB testfile2
 *   v�stup:
 *     �as kop�rov�n� souboru:
 *     copy1: 1.6 s
 *     copy2: 0.08 s       <<< zde je vid�t zrychlen�
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*copy_function_pointer_t)(FILE*f1,FILE*f2);

/* funkce me��c� �as kopie */
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
  function(f1,f2); /* vol�n� testovan� funkce */
  clock_time = clock() - clock_time;
  fclose(f1);
  fclose(f2);
  return (double) clock_time / CLOCKS_PER_SEC;
}

/**************************************************************************/

void copy1(FILE*f1,FILE*f2) { /* kopie znak po znaku - neefektivn� */
    int c;
    while( (c=getc(f1)) != EOF )
      putc(c,f2); 
}

#define BUFSIZE 16384         /* m��ete zv�t�it */
void copy2(FILE*f1,FILE*f2) { /* kopie po bloc�ch znak� - efektivn� */
  static char buffer[BUFSIZE];
  int n;
  while( (n=fread(buffer,1,BUFSIZE,f1)) != 0 )
    fwrite(buffer,1,n,f2); 
}

/**************************************************************************/

int main(int argc, char *argv[]) { 
  if(argc != 3) {
    fprintf(stderr, "Pou�it�: %s soubor_odkud soubor_kam\n", argv[0]);
    return 1;
  }
  copy(argv[1], argv[2], copy2); /* napln� sys. vyrovnav�c� pam�ti */
  printf("�as kop�rov�n� souboru:\n");  
  printf("copy1: %g s\n", copy(argv[1], argv[2], copy1) );  
  printf("copy2: %g s\n", copy(argv[1], argv[2], copy2) );  
  return 0;
}

