/*
 * FREE GMP - a public domain implementation of a subset of the 
 *           gmp library
 *
 * I hearby place the file in the public domain.
 *
 * Do whatever you want with this code. Change it. Sell it. Claim you
 *  wrote it. 
 * Bugs, complaints, flames, rants: please send email to 
 *    Mark Henderson <markh@wimsey.bc.ca>
 * I'm already aware that fgmp is considerably slower than gmp
 *
 * CREDITS:
 *  Paul Rouse <par@r-cube.demon.co.uk> - generic bug fixes, mpz_sqrt and
 *    mpz_sqrtrem, and modifications to get fgmp to compile on a system 
 *    with int and long of different sizes (specifically MSDOS,286 compiler)
 *  Also see the file "notes" included with the fgmp distribution, for
 *    more credits.
 *
 * VERSION 1.0.1
 *
 * PP changes: 
 * PP: change the interface to GMP version 4.x
 *     add mpz_inv --- modular inversion
 * 
 */

#include <stdio.h>
#include <sys/types.h>

/* for malloc and free */
#include <stdlib.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef long mp_limb;
typedef unsigned mp_size;

typedef struct mp_int {
    mp_limb *p;
    short sn;
    mp_size sz;
} MP_INT;

/* GMP 4.x interface compatibility */
typedef MP_INT mpz_t[1];
typedef MP_INT *mpz_ptr;


/* initialize number */
void mpz_init(mpz_t s);
void mpz_init_set(mpz_t s, const mpz_t t);
void mpz_init_set_ui(mpz_t s, unsigned long v);
void mpz_init_set_si(mpz_t y, long v);
int mpz_init_set_str(mpz_t x, const char *s, const int base);

/* destroy */
void mpz_clear(mpz_t s);

/* convert to string */
char *mpz_get_str(char *s, int base, const mpz_t x);
long mpz_get_si(mpz_t y);
unsigned long mpz_get_ui(mpz_t y);

/* compare */
int mpz_cmp(const mpz_t x, const mpz_t y);
int mpz_cmp_si(const mpz_t, long);
int mpz_cmp_ui(const mpz_t, unsigned long);

/* size */
size_t mpz_size(const mpz_t x);
unsigned int mpz_sizeinbase(const mpz_t x, int base);

void mpz_abs(mpz_t, mpz_t);
void mpz_add(mpz_t zz, const mpz_t x, const mpz_t y);
void mpz_add_ui(mpz_t x, const mpz_t y, unsigned long n);

/* bitwise logical */
void mpz_and(mpz_t, mpz_t, mpz_t);
void mpz_or(mpz_t, mpz_t, mpz_t);
void mpz_xor(mpz_t, mpz_t, mpz_t);

/* division */
void mpz_div(mpz_t q, const mpz_t x, const mpz_t y);
void mpz_div_2exp(mpz_t z, mpz_t x, unsigned long e);
void mpz_div_ui(mpz_t x, const mpz_t y, unsigned long n);
void mpz_divmod(mpz_t q, mpz_t r, const mpz_t x, const mpz_t y);
void mpz_divmod_ui(mpz_t q, mpz_t x, const mpz_t y, unsigned long n);
void mpz_mdiv(mpz_t q, const mpz_t x, const mpz_t y);
void mpz_mdiv_ui(mpz_t x, const mpz_t y, unsigned long n);
void mpz_mdivmod(mpz_t q, mpz_t r, const mpz_t x, const mpz_t y);
void mpz_mdivmod_ui(mpz_t q, mpz_t x, mpz_t y, unsigned long n);
void mpz_mmod(mpz_t r, mpz_t x, mpz_t y);
void mpz_mmod_ui(mpz_t x, mpz_t y, unsigned long n);
void mpz_mod(mpz_t r, const mpz_t x, const mpz_t y);
void mpz_mod_2exp(mpz_t z, mpz_t x, unsigned long e);
void mpz_mod_ui(mpz_t x, mpz_t y, unsigned long n);

/* multiplication */
void mpz_mul(mpz_t ww, const mpz_t u, const mpz_t v);
void mpz_mul_2exp(mpz_t z, mpz_t x, unsigned long e);
void mpz_mul_ui(mpz_t x, const mpz_t y, unsigned long n);
void mpz_mul_si(mpz_t x, const mpz_t y, long int n);

void mpz_neg(mpz_t, const mpz_t);

/* power */
void mpz_pow_ui(mpz_t, mpz_t, unsigned long);
void mpz_powm(mpz_t, mpz_t, mpz_t, mpz_t);
void mpz_powm_ui(mpz_t, mpz_t, unsigned long, mpz_t);

/* random */
void mpz_random(mpz_t x, mp_size size);
void mpz_random2(mpz_t x, mp_size size);

/* assign new value */
void mpz_set(mpz_t y, const mpz_t x);
void mpz_set_si(mpz_t y, long v);
void mpz_set_ui(mpz_t y, unsigned long v);
int mpz_set_str(mpz_t x, const char *s, int base);

/* square-root */
void mpz_sqrt(mpz_t, mpz_t);
void mpz_sqrtrem(mpz_t, mpz_t, mpz_t);

/* subtract */
void mpz_sub(mpz_t z, const mpz_t x, const mpz_t y);
void mpz_sub_ui(mpz_t x, const mpz_t y, unsigned long n);

/* etc */
void mpz_fac_ui(mpz_t, unsigned long);
void mpz_gcd(mpz_t, mpz_t, mpz_t);
void mpz_gcdext(mpz_t, mpz_t, mpz_t, mpz_t, mpz_t);
int mpz_jacobi(mpz_t, mpz_t);
int mpz_probab_prime_p(mpz_t, int);

void _mpz_realloc(mpz_t x, mp_size size);


/*
 * ADDITIONS
 */
int mpz_invert(mpz_t inv, const mpz_t n, const mpz_t modulus);
int mpz_tstbit(const mpz_t n, unsigned long i);
int mpz_out_str(FILE*file, int base, const mpz_t number);
