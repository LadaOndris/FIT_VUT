/**
 * @file parse_args.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * Parses arguments and saves them in Arguments_t struct.
 */

#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <stdbool.h>

typedef struct {
    unsigned int persons; /**< Number of persons generated in both categories (serfs and hackers). */
    unsigned int max_hackers_gen_interval; /**< Maximal number of milliseconds after which a new hacker process is generated. */
    unsigned int max_serfs_gen_interval; /**< Maximal number of milliseconds after which a new serf process is generated. */
    unsigned int max_voyage_time; /**< Maximal number of milliseconds that a voyage can take. */
    unsigned int max_person_return_time; /**< Maximal number of milliseconds, after which a person returns back to mole. */
    unsigned int mole_capacity; /**< A capacity of a mole. */
    
    bool is_invalid; /**< Indicates invalid arguments. */
    char error_message[50]; /**< Error message explaining why arguments are invalid. */
} Arguments_t;


/**
 * Parses given arguments and returns Arguments_t structure.
 * It contains all parsed arguments. If the number of arguments is incorrect,
 * an invalid argument is given or the argument's value is not in am expected range,
 * is_invalid variable is set to true in the Arguments_t struct and an error_message is set.
 * @pre Expects 7 arguments, the first is the name of the program.
 * @param argc The number of arguments.
 * @param argv The array of arguments.
 * @return Returns Arguments_t struct containing all parsed arguments and an error_message if occurs.
 */
Arguments_t parse_arguments(int argc, char *argv[]);

#endif // PARSE_ARGS_H