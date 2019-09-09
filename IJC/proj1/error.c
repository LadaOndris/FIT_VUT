// error.c
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Implementace funkci definovanych v error.h pro vypis chybovych hlaseni.

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

static void write_error_msg(const char *fmt, va_list args) {
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, args);
}

void warning_msg(const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    write_error_msg(fmt, args);
    va_end (args);
}

_Noreturn void error_exit(const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);
    write_error_msg(fmt, args);
    va_end (args);
    exit(1);
}

