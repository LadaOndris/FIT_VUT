// steg-decode.c
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Dekodovani zpravy z ppm obrazku technikou podobnou steganografii.

#include <limits.h>
#include <math.h>
#include "error.h"
#include "ppm.h"
#include "bit_array.h"
#include "eratosthenes.h"

/*
 * Estimates the number of primes that exist in the range <2,n>.
 * The estimate should be just a bit higher than the actual number of primes.
 *
 * @param n The upper limit of the range.
 */
int estimate_number_of_primes(double n) {
    if (n < 4) {
        return 2;
    }
    return (int)(n / (log(n) - 1.1));
}

/*
 * Decodes a message from ppm file using a method similar to steganography.
 *
 * @return Returns number of characters printed. If an error occurs or
 *         no null termination character was found, negative number is returned.
 */
int decode(struct ppm *p) {
    int bytes_count = p->xsize * p->ysize * 3;
    bit_array_alloc(message_bit_array, estimate_number_of_primes(bytes_count));
    bit_array_alloc(primes, bytes_count);
    Eratosthenes(primes);
    
    char *msg_arr_beginning = ((char *)message_bit_array) + sizeof(message_bit_array[0]);
    
    int prime_index = 0;
    for (int byte_index = 19; byte_index < bytes_count; byte_index++) {
        // if it is a prime
        if (!bit_array_getbit(primes, byte_index)) {
            // save the bit into a bit array
            bit_array_setbit(message_bit_array, prime_index, p->data[byte_index] & 0x1);
            prime_index++;
        }
        
        // if the last character is null termination character
        if (((prime_index + 1) % CHAR_BIT) == 0 && msg_arr_beginning[((prime_index + 1) / CHAR_BIT - 1)] == '\0') {
            int res = printf("%s", msg_arr_beginning);
    
            bit_array_free(primes);
            bit_array_free(message_bit_array);
            return res;
        }
    }
    
    // No null termination character found at this point
    bit_array_free(primes);
    bit_array_free(message_bit_array);
    return -1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        error_exit("Wrong number of arguments.\n");
    }

    struct ppm *p = ppm_read(argv[1]);
    if (!p) {
        error_exit("Unable to read file '%s'\n", argv[1]);
    }

    int resval = decode(p);
    if (resval < 0) {
        ppm_free(p);
        error_exit("Decoding failed - byte '\\0' not found.\n");
    }

    ppm_free(p);
    return 0;
}