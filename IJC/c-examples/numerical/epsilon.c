/* epsilon.c 
 *
 * Program vytiskne rozli¹ení typù v plovoucí èárce
 * (vypoèítané i získané z float.h).
 *
 */

#include <stdio.h>
#include <float.h>

/* makro pro výpoèet a tisk rozli¹ení */
#define epsilon(flt_t)                                     \
{                                                          \
  long double eps;                                         \
  flt_t x, delta;                                          \
  for(x=1.0L, delta=x; ; delta/=2) {                       \
    flt_t y = x + delta;                                   \
    if( y == x ) break; /* ji¾ se nemìní */                \
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

