/**
 * @file person_generator.h
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * The person_generator file contains code for 
 * a generating process, which generates either hackers or serfs.
 */

#ifndef PERSON_GENERATOR_H
#define PERSON_GENERATOR_H

#include "parse_args.h"
#include "shared_variables.h"
#include "person.h"

/**
 * Generates required number of hackers or serfs.
 * The generating process running this function sleeps 
 * for random number of milliseconds from an interval set by args.
 * After all processes (hackers or serfs) are generated, it
 * waits for them to finish.
 */
void start_person_gen(Arguments_t args, PersonType_t person_type, Shared_variables_t shared_variables);

#endif //PERSON_GENERATOR_H
