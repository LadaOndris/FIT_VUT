// ppm.c
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Implementace funkci poskytujicich praci s ppm typem souboru.

#include <stdlib.h>
#include <stdio.h>
#include "error.h"
#include "ppm.h"

struct ppm * ppm_read(const char * filename) {
    FILE *file;
    if ((file = fopen(filename, "rb")) == NULL) {
        warning_msg("File '%s' couldn't be opened.\n", filename);
        return NULL;
    }
    
    int xsize, ysize, max_value;
    if (fscanf(file, "P6 %d %d %d ", &xsize, &ysize, &max_value) != 3) { // reads header
        warning_msg("File format does not match PPM P6 file.\n");
        fclose(file);
        return NULL;
    }
    
    if (xsize <= 0 || ysize <= 0) {
        warning_msg("Image size cannot be zero. Image size given: %d x %d\n", xsize, ysize);
        fclose(file);
        return NULL;
    }
    
    if (max_value != 255) {
        warning_msg("Max value must equal to 255. Max value given %d is not supported.\n", max_value);
        fclose(file);
        return NULL;
    }
    
    unsigned int data_bytes_length = 3 * xsize * ysize;
    struct ppm *ppm_obj = malloc(sizeof(struct ppm) + data_bytes_length);
    if (!ppm_obj) {
        warning_msg("Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }
    ppm_obj->xsize = xsize;
    ppm_obj->ysize = ysize;
    
    if (fread(ppm_obj->data, 1, data_bytes_length, file) != data_bytes_length) { // reads data
        warning_msg("Failed to read the file '%s'.\n", filename);
        free(ppm_obj);
        fclose(file);
        return NULL;
    }
    
    if (getc(file) != EOF) {
        warning_msg("Read %d bytes of data as specified in header, but EOF was not reached.\n", data_bytes_length);
        free(ppm_obj);
        fclose(file);
        return NULL;
    }
    
    fclose(file);
    
    return ppm_obj;
}

int ppm_write(struct ppm *p, const char * filename) {
    if (!p) {
        warning_msg("Parameter of type 'struct ppm *' cannot be NULL.\n");
        return -1;
    }
    if (p->xsize <= 0 || p->ysize <= 0) {
        warning_msg("The xsize and ysize of ppm cannot be less or equal to zero.\n");
        return -1;
    }
   
    FILE *file;
    if ((file = fopen(filename, "wb")) == NULL) {
        warning_msg("File '%s' couldn't be opened.\n", filename);
        return -1;
    }
    
    if (fprintf(file, "P6\n%d %d\n255\n", p->xsize, p->ysize) < 0) {
        warning_msg("Failed to write the header of the ppm file.\n");
        fclose(file);
        return -1;
    }
    unsigned data_length = 3 * p->xsize * p->ysize;
    if (fwrite(p->data, 1, data_length, file) != data_length) { // writes data
        warning_msg("Failed to write to a file '%s'.\n", filename);
        fclose(file);
        return -1;
    }
    
    fclose(file);
    return 0;
}

void ppm_free(struct ppm *p) {
    free(p);
}
