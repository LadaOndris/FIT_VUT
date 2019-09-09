/* mpfact.c
 *
 * multiple precision factorial computation
 *
 * example for performance analysis of programs
 *
 * TODO: add basic operations mpz_*
 *
 * (c) GPL  due to using GMP
 *
 */

#include <gmp.h> /* use GMP */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000L

int main(int argc, char *argv[]) {
    int i;
    long int n;
    mpz_t x;

    if(argc!=2) {
        fprintf(stderr,"Usage: %s number\n", argv[0]); 
        return 1;
    }

    n = strtol(argv[1],NULL,10);

    if(n < 0 || n > MAXN) {
        fprintf(stderr,"%s: number out of range (0..%ld)\n", argv[0], MAXN); 
        return 1;
    }

    mpz_init_set_ui(x,1);

    for(i=1; i<=n; i++)
        mpz_mul_ui(x,x,i);

    printf("\n%ld! = ", n);
    mpz_out_str(stdout,10,x);
    printf("\n\n");
    
    return 0;
}
