// htab_hash_function.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdint.h>
#include "htab.h"
#include "htab_hash_function.h"

unsigned int htab_hash_function(const char *str) {
    uint32_t h = 0; // musí mít 32 bitů
    const unsigned char *p;
    for (p = (const unsigned char *) str; *p != '\0'; p++)
        h = 65599 *h + *p;
    return h;
}
