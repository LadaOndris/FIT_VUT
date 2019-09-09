// htab_bucket_count.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <assert.h>
#include "htab_private.h"

size_t htab_bucket_count(const htab_t * t) {
    assert(t != NULL);
    return t->arr_size;
}