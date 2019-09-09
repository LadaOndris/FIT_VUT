// wordcount.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdio.h>
#include "htab.h"
#include "io.h"
#include "stdbool.h"

#define MAX_WORD_CHAR 128 // 127 characters + null termination character

extern inline bool htab_iterator_valid(htab_iterator_t it);
extern inline bool htab_iterator_equal(htab_iterator_t it1, htab_iterator_t it2);


void print_htab_content(htab_t *htab) {
    htab_iterator_t iterator = htab_begin(htab);
    
    while (htab_iterator_valid(iterator)) {
        printf("%s\t%d\n", htab_iterator_get_key(iterator), htab_iterator_get_value(iterator));
        iterator = htab_iterator_next(iterator);
    }
}

int main() {
    // The size should be a prime number to avoid a clustering problem.
#ifdef TEST
    // The hash table size of 7 is dumb. It is used only for testing purposes of htab_move function.
    htab_t *htab = htab_init(7);
#else
    htab_t *htab = htab_init(50177);
#endif
    
    if (htab == NULL) {
        fprintf(stderr, "Invalid htab: memory allocation failed.\n");
        return -1;
    }
    
    bool word_too_long_warning_printed = false;
    char word_buffer[MAX_WORD_CHAR];
    int word_length;
    while ((word_length = get_word(word_buffer, MAX_WORD_CHAR, stdin)) != EOF) {
        
        // If the word length is greater or equal to MAX_WORD_CHAR, a warning message should be printed.
        if (word_length >= MAX_WORD_CHAR && !word_too_long_warning_printed) {
            fprintf(stderr, "One or more of the words is longer than %d characters. I'm skipping the rest of the word.\n", MAX_WORD_CHAR);
            word_too_long_warning_printed = true;
        }
        
        htab_iterator_t iterator = htab_lookup_add(htab, word_buffer);
        if (!htab_iterator_valid(iterator)) {
            fprintf(stderr, "Invalid iterator: memory allocation failed.\n");
            htab_free(htab);
            return -1;
        }
        int value = htab_iterator_get_value(iterator);
        htab_iterator_set_value(iterator, value + 1);

#ifdef TEST
        // If the number of items in the hash table exceeds the bucket count,
        // the htab is realloced to a htab with twice as much bucket count as the previous htab.
        if (htab_size(htab) >  htab_bucket_count(htab)) {
            int new_htab_arr_size = htab_bucket_count(htab) * 2;
            htab_t *new_htab = htab_move(new_htab_arr_size, htab);
            htab_free(htab); // the old htab has to be freed, the htab_move only clears the htab
            
            if (new_htab == NULL) {
                fprintf(stderr, "Invalid htab: memory allocation failed.\n");
                return -1;
            }
            htab = new_htab;
        }
#endif
    }
    
    print_htab_content(htab);
    
    htab_free(htab);
    return 0;
}
