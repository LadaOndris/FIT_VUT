// bit_array.h
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Soubor poskytujici inline funkce a makra pro praci s bitovym polem.


#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include "error.h"

typedef unsigned long bit_array_t[];


#define LONG_BITS (CHAR_BIT * sizeof(unsigned long))
#define BIT_ARRAY_INDEX(index) ((index) + 1) / (LONG_BITS) + (((index) + 1) % (LONG_BITS) != 0)

#define BIT_ARRAY_SETBIT(bit_array, index, expression) \
    ((expression) ? ((bit_array)[BIT_ARRAY_INDEX(index)] |= 1ul << ((index) % (LONG_BITS))) \
                 : ((bit_array)[BIT_ARRAY_INDEX(index)] &= ~(1ul << ((index) % (LONG_BITS)))) )
             
#define BIT_ARRAY_GETBIT(bit_array, index) \
    ((bit_array)[BIT_ARRAY_INDEX(index)] & (1ul << ((index) % (LONG_BITS)))) != 0


#define bit_array_create(bit_array, bit_size) \
        unsigned long (bit_array) [(bit_size) / LONG_BITS + ((bit_size) % (LONG_BITS) ? 2 : 1)] = { (bit_size) }; \
        static_assert((bit_size) > 0, "Bit array size must be greater than 0.\n")

#define bit_array_alloc(bit_array, bit_size) \
        assert((bit_size) > 0); \
        unsigned long *(bit_array) = calloc(((bit_size) / LONG_BITS + ((bit_size) % (LONG_BITS) ? 2 : 1)), sizeof(unsigned long)); \
        if ((bit_array) == NULL) \
            error_exit("bit_array_alloc: Chyba alokace paměti"); \
        (bit_array)[0] = (bit_size);

#ifndef USE_INLINE

    #define bit_array_size(bit_array)  (bit_array)[0]
    
    #define bit_array_setbit(bit_array, index, expression) \
        (((index) < 0 || (unsigned long)(index) + 1 > bit_array_size(bit_array)) \
            ? (error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), (unsigned long)bit_array_size(bit_array) - 1), 1) \
            : BIT_ARRAY_SETBIT(bit_array, index, (expression)))
        
    
    #define bit_array_getbit(bit_array, index) \
        (((index) < 0 || (unsigned long)(index) + 1 > bit_array_size(bit_array)) \
            ? (error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)(index), (unsigned long)bit_array_size(bit_array) - 1), 1) \
            : BIT_ARRAY_GETBIT(bit_array, index))

    #define bit_array_free(bit_array) \
        free(bit_array)
#else

    inline unsigned long bit_array_size(bit_array_t bit_array) {
        return bit_array[0];
    }
    
    inline void bit_array_setbit(bit_array_t bit_array, unsigned long index, int expression) {
        if (index + 1 > bit_array_size(bit_array)) {
            error_exit("bit_array_setbit: Index %lu mimo rozsah 0..%lu", index, bit_array_size(bit_array) - 1);
        } else {
            BIT_ARRAY_SETBIT(bit_array, index, (expression));
        }
    }
    
    inline unsigned long bit_array_getbit(bit_array_t bit_array, unsigned long index) {
        if (index + 1 > bit_array_size(bit_array)) {
            error_exit("bit_array_getbit: Index %lu mimo rozsah 0..%lu", index, bit_array_size(bit_array) - 1);
            return 1;
        }
        else {
            return BIT_ARRAY_GETBIT(bit_array, index);
        }
    }
    
    inline void bit_array_free(bit_array_t bit_array) {
        free(bit_array);
    }

#endif

#endif //BIT_ARRAY_H


