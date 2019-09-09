// eratosthenes.h
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Rozhrani pro provedeni Eratosthenova sita nad vstupnim bitovym polem.

#ifndef ERATOSTHENES_H
#define ERATOSTHENES_H


/**
 * Sets bits to 1 in a given bit_array if it is not a prime,
 * otherwise leaves 0.
 *
 * @pre bit_array has all bits set to 0.
 * @pre Size of bit_array is 2 or more bits.
 * @post Bits are set at the appropriate positions where the numbers are not a prime to 1 .
 * @param bit_array A bit array to perform the Eratosthenes sieve on.
 */
void Eratosthenes(bit_array_t bit_array);


#endif
