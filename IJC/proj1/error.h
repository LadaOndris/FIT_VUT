// error.h
// Řešení IJC-DU1, příklad a), 4.3.2019
// Autor: Ladislav Ondris, xondri07,FIT
// Přeloženo: gcc 7.3.0
//
// Popis: Rozhrani funkci pro vypis chybovych hlaseni.

#ifndef ERROR_H
#define ERROR_H

/**
 * Prints formatted message to stderr and prepends "CHYBA: " to the message.
 *
 * @param fmt The format specifier
 */
extern void warning_msg(const char *fmt, ...);

/**
 * Prints formatted message to stderr and prepends "CHYBA: " to the message
 * and calls exit(1).
 *
 * @param fmt The format specifier
 */
extern _Noreturn void error_exit(const char *fmt, ...);

#endif
