/**
 * @file person_generator.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * The person_generator file contains code for 
 * a generating process, which generates either hackers or serfs.
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h> //fork
#include <unistd.h> // fork
#include "utils.h"
#include "parse_args.h"
#include "shared_variables.h"
#include "person_generator.h"
#include "person.h"


static pid_t generate_person(Person_data_t person_data, Arguments_t args, Shared_variables_t shared_variables) {
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(2);
    }
    if (pid == 0) { // child
        create_person(person_data, args, shared_variables);
        exit(0);
    } else { // parent
        return pid;
    }
}

static int get_max_gen_interval(Arguments_t *args, PersonType_t *person_type) {
    return person_type == Hacker ? args->max_hackers_gen_interval : args->max_serfs_gen_interval;
}

void start_person_gen(Arguments_t args, PersonType_t person_type, Shared_variables_t shared_variables) {
    int max_gen_interval = get_max_gen_interval(&args, &person_type);
        
    pid_t *persons_pids = malloc(sizeof(pid_t) * args.persons);
    
    srand(time(0));
    for (unsigned i = 0; i < args.persons; i++) {
        sleep_in_millis(0, max_gen_interval);
        Person_data_t person_data = {.type=person_type, .id=i+1};
        persons_pids[i] = generate_person(person_data, args, shared_variables);
    }
    
    wait_for_processes_to_finish(args.persons, persons_pids);
    
    free(persons_pids);
}