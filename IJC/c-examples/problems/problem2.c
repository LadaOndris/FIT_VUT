/*
 * test of errorneous expression 
 * try with/without optimization:  gcc -O3 / gcc -O0
 * output on Debian 3.1 GCC 3.3.5:       5 / 4
 * 
 */

#include <stdio.h>

#define TEST(expr) { printf(#expr "\n"); expr; }

int main() {
    int i = 1;
    printf("\ni = %d\n", i);
    TEST( i = i++ * ++i );
    printf("i = %d\n\n", i);
    return 0;
}
