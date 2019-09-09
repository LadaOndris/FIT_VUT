// eratosthenes.c
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Implementace funkce Eratosthenes, ktera provede
//        Eratosthenovo sito nad vstupnim bitovym polem.

#include <math.h>
#include "bit_array.h"

void Eratosthenes(bit_array_t bit_array) {
    bit_array_setbit(bit_array, 0, 1);
    bit_array_setbit(bit_array, 1, 1);
    
    int last = sqrt(bit_array_size(bit_array));
    
    // mark even numbers
    //for (unsigned int i = 2; i < bit_array_size(bit_array); i += 2) {
    //    bit_array_setbit(bit_array, i, 1);
    //}
    memset(&bit_array[1], 0x55, bit_array_size(bit_array) / 8);
    
    // iterate only through odd numbers
    for (int i = 3; i <= last; i += 2) {
        if (bit_array_getbit(bit_array, i))
            continue;
        for (unsigned int j = i * i; j < bit_array_size(bit_array); j += i * 2) {
            bit_array_setbit(bit_array, j, 1);
        }
    }
}