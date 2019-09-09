// ppm.h
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Deklarace funkci poskytujicich praci s ppm typem souboru.

#ifndef PPM_H
#define PPM_H

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

/**
 * Reads PPM file and dynamically allocates ppm structure.
 * Prints error message and returns NULL, if the file format is not correct.
 *
 * @pre A file with a name 'filename' must exist.
 * @pre The file type has to be P6 nad max value 255.
 * @param filename The name of the file that will be read.
 * @return Returns a pointer to a dynamically allocated ppm structure
 *         if read was successfull, otherwise returns NULL.
 */
struct ppm * ppm_read(const char * filename);

/**
 * Writes the content of a ppm structure into a file in the PPM format.
 * Prints error message and returns negative number, if an error occurs.
 *
 * @pre p->xsize > 0 && p->ysize > 0
 * @param p A pointer to the ppm structure that will be written to a file.
 * @param filename A name of the file into the ppm structure will be written.
 * @return Returns negative number if the ppm structure could not be written correctly.
 */
int ppm_write(struct ppm *p, const char * filename);


/**
 * Frees the memory of dynamically allocated ppm struct.
 *
 * @param p A pointer to ppm struct to be deallocated.
 */
void ppm_free(struct ppm *p);

#endif
