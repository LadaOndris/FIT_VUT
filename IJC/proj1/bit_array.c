// bit_array.c
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Externi deklarace inline funkci pro praci s bitovym polem.

#include "bit_array.h"

#ifdef USE_INLINE

extern inline unsigned long bit_array_size(bit_array_t bit_array);
extern inline void bit_array_setbit(bit_array_t bit_array, unsigned long index, int expression);
extern inline unsigned long bit_array_getbit(bit_array_t bit_array, unsigned long index);
extern inline void bit_array_free(bit_array_t bit_array);

#endif