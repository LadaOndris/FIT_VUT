// io.h 
// IJC-DU2, part b), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#ifndef IO_H
#define IO_H

/**
 * Reads one word from file f into the buffer s.
 * Reads maximum of max characters. If the word is too long,
 * reads max-1 characters and the rest is ignored.
 *
 * @param s A buffer into which the word is read.
 * @param max The maximum number of characters that will be read.
 * @param f File to read from.
 * @return Returns length of the word read.
 */
int get_word(char *s, int max, FILE *f);

#endif // IO_H
