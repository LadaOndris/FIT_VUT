// primes.c
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Vypis poslednich deseti prvocisel do cisla 123000000.

#include <stdio.h>
#include "bit_array.h"
#include "eratosthenes.h"


int main() {
    bit_array_create(bit_array, 123000000);
    
    Eratosthenes(bit_array);
    
    // sets the first prime's index to i
    int primes_count = 0;
    long i = bit_array_size(bit_array) - 1;
    for (; i >= 0 && primes_count < 10; i--) {
        if (!bit_array_getbit(bit_array, i)) {
            primes_count++;
        }
    }
    // print last 10 primes
    for (; (unsigned long)i < bit_array_size(bit_array); i++) {
        if (!bit_array_getbit(bit_array, i)) {
            printf("%ld\n", i);
        }
    }
    
    return 0;
}