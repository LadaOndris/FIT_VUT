/**
 * @file person.h
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * Contains declarations of PersonType_t, Person_data_t, 
 * Message_type_t structures and create_person function, which 
 * starts a new hacker or a serf.
 */

#ifndef PERSON_H
#define PERSON_H

#include "parse_args.h"
#include "shared_variables.h"

typedef enum {
    Hacker, Serf
} PersonType_t;

typedef struct {
    PersonType_t type;
    int id;
} Person_data_t;

typedef enum {
    Starts,
    Waits,
    Boards,
    Member_exits,
    Captain_exits,
    Leaves_queue,
    Is_back
} Message_type_t;


/**
 * The code the hacker or a serf runs.
 * First it retrieves shared variables and then runs the algorithm
 * and prints messages in a file.
 * @param person_data The details of a person: the type of a person (hacker or serf) and its index.
 * @param args Arguments that contain all needed information for carrying out the synchronization algorithm.
 */
void create_person(Person_data_t person_data, Arguments_t args, Shared_variables_t shared_variables);

#endif //PERSON_H
