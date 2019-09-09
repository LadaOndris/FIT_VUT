// io.c 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include "io.h"


int get_word(char *s, int max, FILE *f) {
    assert(max > 0);
    assert(f != NULL);
    assert(s != NULL);
    
    int char_count = 0;
    int c;
    
    while ((c = getc(f)) != EOF && isspace(c)) {
        c = getc(f);
    }
    
    if (c == EOF)
        return EOF;
    
    s[char_count] = c;
    char_count++;
    
    while ((c = getc(f)) != EOF && !isspace(c)) {
        if (char_count < max - 1) {
            s[char_count] = c;
            char_count++;
        }
        else {
            char_count++;
        }
        if (char_count == max - 1) {
            s[char_count] = '\0';
        }
    }
    
    if (char_count < max - 1) {
        s[char_count] = '\0';
    }
    return char_count;
}
