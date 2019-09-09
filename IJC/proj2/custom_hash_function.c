// custom_hash_function.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include "htab_hash_function.h"


#ifdef HASHTEST

unsigned int htab_hash_function(const char *str) {
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash += str[i] * (i + 1);
    }
    return hash;
}

#endif