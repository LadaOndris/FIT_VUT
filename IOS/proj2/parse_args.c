/**
 * @file parse_args.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * Parses arguments and saves them in Arguments_t struct.
 */

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "parse_args.h"

static void set_error_message(Arguments_t *args, char *message) {
    args->is_invalid = true;
    strcpy(args->error_message, message);
}

/**
 * Parses the argument and sets the variable. If an argument is invalid,
 * sets an error_message inside the args struct and returns nonzero value.
 * @return Returns 1 if an argument is invalid, otherwise returns 0.
 */
static int parse_argument(Arguments_t *args, unsigned int *variable, char *argument) {
    char *end_ptr;
    unsigned long value;
    
    errno = 0;
    value = strtoul(argument, &end_ptr, 10);
    if (errno != 0) {
        set_error_message(args, "Argument is invalid.\n");
        return 1;
    }
    if (end_ptr[0] != '\0') {
        set_error_message(args, "Argument is invalid.\n");
        return 1;
    }
    if (value > UINT_MAX) {
        set_error_message(args, "The value given is too large.\n");
        return 1;
    }
    *variable = value;
    
    return 0;
}

Arguments_t parse_arguments(int argc, char *argv[]) {
    Arguments_t args;
    args.is_invalid = false;
    
    if (argc != 7) {
        set_error_message(&args, "Wrong number of arguments.\n");
        return args;
    }
    
    if (parse_argument(&args, &args.persons, argv[1]) ||
        parse_argument(&args, &args.max_hackers_gen_interval, argv[2]) ||
        parse_argument(&args, &args.max_serfs_gen_interval, argv[3]) ||
        parse_argument(&args, &args.max_voyage_time, argv[4]) ||
        parse_argument(&args, &args.max_person_return_time, argv[5]) ||
        parse_argument(&args, &args.mole_capacity, argv[6])) {
        return args;
    }
    if (!(args.persons >= 2 && args.persons % 2 == 0)) {
        set_error_message(&args, "The range of the P argument is invalid.\n");
        return args;
    }
    if (!(args.max_hackers_gen_interval <= 2000)) {
        set_error_message(&args, "The range of the H argument is invalid.\n");
        return args;
    }
    if (!(args.max_serfs_gen_interval <= 2000)) {
        set_error_message(&args, "The range of the S argument is invalid.\n");
        return args;
    }
    if (!(args.max_voyage_time <= 2000)) {
        set_error_message(&args, "The range of the R argument is invalid.\n");
        return args;
    }
    if (!(args.max_person_return_time >= 20 && args.max_person_return_time <= 2000)) {
        set_error_message(&args, "The range of the W argument is invalid.\n");
        return args;
    }
    if (!(args.mole_capacity >= 5)) {
        set_error_message(&args, "The range of the C argument is invalid.\n");
        return args;
    }
    return args;
}
