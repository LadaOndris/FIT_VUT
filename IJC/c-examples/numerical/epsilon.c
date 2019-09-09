/* epsilon.c 
 *
 * Program vytiskne rozli�en� typ� v plovouc� ��rce
 * (vypo��tan� i z�skan� z float.h).
 *
 */

#include <stdio.h>
#include <float.h>

/* makro pro v�po�et a tisk rozli�en� */
#define epsilon(flt_t)                                     \
{                                                          \
  long double eps;                                         \
  flt_t x, delta;                                          \
  for(x=1.0L, delta=x; ; delta/=2) {                       \
    flt_t y = x + delta;                                   \
    if( y == x ) break; /* ji� se nem�n� */                \
  }                                                        \
  eps = delta * 2;	                                   \
  printf(#flt_t " epsilon = %25.22LfL (%Le)\n", eps, eps); \
}

#define EPSILON(x) \
  printf( #x " = %Le\n", (long double) x ) 
  

int main(void)
{
    printf("Rozliseni cisel v plovouci carce\n");
    epsilon(float);
    EPSILON(FLT_EPSILON);
    epsilon(double);
    EPSILON(DBL_EPSILON);
    epsilon(long double);
    EPSILON(LDBL_EPSILON);
    return 0;
}

