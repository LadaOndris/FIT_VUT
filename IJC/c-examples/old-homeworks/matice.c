/* matice.c
 * Jazyk C -- pr�ce s matic�  
 *
 * TODO: zru�it TMatice, 
 *       c99 prom�nn� velikost
 */

#include <stdio.h>

#define N 6
typedef int TMatice[N][N];        /* zadan� typ matice */

void TranMat(TMatice M);          /* transpozice matice */
void OtocMat(TMatice M);          /* oto�en� matice */
void TiskMat(const TMatice M);    /* tisk matice */

int main(void) {
  TMatice M = {                   /* inicializace lok�ln�ho pole */
    {1},
    {2,2},
    {3,3,3},
    {4,4,4,4},
    {5,5,5,5,5},
    {6,6,6,6,6,6},
  };

  printf("P�vodn� matice: \n");
  TiskMat(M);
  TranMat(M);
  OtocMat(M);
  printf("V�sledn� matice: \n");
  TiskMat(M);
  return 0;
}

/*
 * funkce VymenRadky - vym�n� obsah dvou ��dk� matice
 */
void VymenRadky( int r1[], int r2[] ) {
  int s;
  for( s = 0; s < N; s++ ) {
     int pom = r1[s];           /* v�m�na prvku */
     r1[s] = r2[s];
     r2[s] = pom;
  }
}

/*
 * funkce TranMat - transpozice matice
 *
 * parametr je pole - p�ed�v� se odkazem - zkuste sizeof(M)
 *
 */
void TranMat(TMatice M) {
  int r, s;
  for( r=0; r<N-1; r++ )
    for( s=r+1; s<N; s++ ) {
      int pom = M[r][s];
      M[r][s] = M[s][r];
      M[s][r] = pom;
    }
}

/*
 * funkce OtocMat - oto�en� matice podle vodorovn� osy
 */
void OtocMat(TMatice M) {
  int r;
  for( r=0; r<N/2; r++ )
    VymenRadky( M[r], M[N-1-r] );
}

/*
 * funkce TiskMat - tisk matice
 */
void TiskMat(const TMatice M) {
  int r, s;
  for(r=0; r<N; r++)
    for(s=0; s<N; s++)
      printf("%3i%c", M[r][s], (s==N-1) ? '\n' : ' ');
}

/* konec */
