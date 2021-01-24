/**
 * @file person.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * Contains all the synchronization of hackers and serfs.
 * All of the code of hacker and serf processes is here.
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>

#include "person.h"
#include "utils.h"
#include "shared_variables.h"
#include "parse_args.h"

#define OUTPUT_FILE

/**
 *  Formats given message and prints it into the given file
 *  if there is OUTPUT_FILE macro defined, otherwise the message is
 *  printed on stdout.
 */
static void write_msg(FILE *file, const char *fmt, ...)
{
    (void)file;
    va_list args;
    va_start(args, fmt);

#ifdef OUTPUT_FILE
    vfprintf(file, fmt, args);
    fflush(file);
#else
    vfprintf(stdout, fmt, args);
#endif
    va_end(args);
}

static void print_message(Message_type_t message_type, Person_data_t person_data, Shared_variables_t shared_variables) {
    char *name = person_data.type == Hacker ? "HACK" : "SERF";

    sem_wait(shared_variables.log_sem);
    *shared_variables.counter += 1;
    
    FILE *output_file = shared_variables.output_file;
    switch (message_type) {
        case Starts:
            write_msg(output_file, "%d: %s %d: starts\n", *shared_variables.counter, name, person_data.id);
            break;
        case Waits:
            write_msg(output_file, "%d: %s %d: waits: %d: %d\n", *shared_variables.counter, name, person_data.id,
                    *shared_variables.mole_waiting_hackers,
                    *shared_variables.mole_waiting_serfs);
            break;
        case Boards:
            write_msg(output_file, "%d: %s %d: boards: %d: %d\n", *shared_variables.counter, name, person_data.id, 
                   *shared_variables.mole_waiting_hackers,
                   *shared_variables.mole_waiting_serfs);
            break;
        case Member_exits:
            write_msg(output_file, "%d: %s %d: member exits: %d: %d\n", *shared_variables.counter, name, person_data.id,
                   *shared_variables.mole_waiting_hackers,
                   *shared_variables.mole_waiting_serfs);
            break;
        case Captain_exits:
            write_msg(output_file, "%d: %s %d: captain exits: %d: %d\n", *shared_variables.counter, name, person_data.id,
                   *shared_variables.mole_waiting_hackers,
                   *shared_variables.mole_waiting_serfs);
            break;
        case Leaves_queue:
            write_msg(output_file, "%d: %s %d: leaves queue: %d: %d\n", *shared_variables.counter, name, person_data.id,
                   *shared_variables.mole_waiting_hackers,
                   *shared_variables.mole_waiting_serfs);
            break;
        case Is_back:
            write_msg(output_file, "%d: %s %d: is back\n", *shared_variables.counter, name, person_data.id);
            break;
        default:
            fprintf(stderr, "Unknown message type.\n");
    }
    sem_post(shared_variables.log_sem);
}

static void sem_signal(sem_t *sem, int num) {
    for (int i = 0; i < num; i++) {
        sem_post(sem);
    }
}

static void sem_wait_n(sem_t *sem, int num) {
    for (int i = 0; i < num; i++) {
        sem_wait(sem);
    }
}

static void try_to_release_combination(Shared_variables_t shared_variables) {
    if (*shared_variables.mole_waiting_hackers >= 4) {
        sem_signal(shared_variables.hackers_mole_sem, 4);
        *shared_variables.mole_waiting_hackers -= 4;
        *shared_variables.is_boat_in_dock = false;
        *shared_variables.queue_reduced = true;
    } else if (*shared_variables.mole_waiting_serfs >= 4) {
        sem_signal(shared_variables.serfs_mole_sem, 4);
        *shared_variables.mole_waiting_serfs -= 4;
        *shared_variables.is_boat_in_dock = false;
        *shared_variables.queue_reduced = true;
    } else if (*shared_variables.mole_waiting_hackers >= 2 && *shared_variables.mole_waiting_serfs >= 2) {
        sem_signal(shared_variables.hackers_mole_sem, 2);
        sem_signal(shared_variables.serfs_mole_sem, 2);
        *shared_variables.mole_waiting_hackers -= 2;
        *shared_variables.mole_waiting_serfs -= 2;
        *shared_variables.is_boat_in_dock = false;
        *shared_variables.queue_reduced = true;
    }
    else {
        *shared_variables.is_boat_in_dock = true;
    }
}

void create_person(Person_data_t person_data, Arguments_t args, Shared_variables_t shared_variables) {
    //Shared_variables_t shared_variables;
    //shared_variables_open(&shared_variables);
    
    int *boarding_group1 = person_data.type == Hacker ? shared_variables.waiting_hackers : shared_variables.waiting_serfs;
    int *boarding_group2 = person_data.type == Serf ? shared_variables.waiting_hackers : shared_variables.waiting_serfs;
    int *mole_waiting_group1 = person_data.type == Hacker ? shared_variables.mole_waiting_hackers : shared_variables.mole_waiting_serfs;
    sem_t *sem_group1 = person_data.type == Hacker ? shared_variables.hacker_queue_sem : shared_variables.serf_queue_sem;
    sem_t *sem_group2 = person_data.type == Serf ? shared_variables.hacker_queue_sem : shared_variables.serf_queue_sem;
    sem_t *sem_mole_group1 = person_data.type == Hacker ? shared_variables.hackers_mole_sem : shared_variables.serfs_mole_sem;
    
    print_message(Starts, person_data, shared_variables);
    
    while (true) {
        bool is_captain = false;
        sem_wait(shared_variables.mole_mutex);

        // If the number of processes in the queue was reduced, but
        // no Boards message appeared, wait on semaphor until the Boards message is printed.
        sem_wait(shared_variables.mole_mutex2);
        if (*shared_variables.queue_reduced == true) {
            *shared_variables.reduced_hackers += 1;
            sem_post(shared_variables.mole_mutex2);
            sem_post(shared_variables.mole_mutex);
            sem_wait(shared_variables.boarding_sem);
            continue;
        }
        else {
            sem_post(shared_variables.mole_mutex2);
        }

        // Check if the mole is full and behave accordingly. 
        if (*shared_variables.mole_waiting_hackers + *shared_variables.mole_waiting_serfs + 1 > (int)args.mole_capacity) {
            print_message(Leaves_queue, person_data, shared_variables);
            
            // Release 4 processes if there is available enough processes in a possible combination.
            if (*shared_variables.is_boat_in_dock == true) {
                try_to_release_combination(shared_variables); 
            }

            sem_post(shared_variables.mole_mutex);

            sleep_in_millis(20, args.max_person_return_time);
            print_message(Is_back, person_data, shared_variables);
            continue;
        }
    
        // Increment the number of processes in a queue.
        *mole_waiting_group1 += 1;
        print_message(Waits, person_data, shared_variables);
        
        // Release 4 processes if there is available enough processes in a possible combination.
        if (*shared_variables.is_boat_in_dock == true) {
            try_to_release_combination(shared_variables); 
        }

        sem_post(shared_variables.mole_mutex);
        
        // Make sure the processes wait on the mole here, until there is 4 of them.
        sem_wait(sem_mole_group1);
        
        // Boarding of 4 already prepared processes. 
        sem_wait(shared_variables.mole_mutex);
        *boarding_group1 += 1;
        if (*boarding_group1 == 4) {
            sem_signal(sem_group1, 4);
            *boarding_group1 = 0;
            is_captain = true;
            sem_wait(shared_variables.mole_mutex2);
            print_message(Boards, person_data, shared_variables);
            *shared_variables.queue_reduced = false;
            sem_signal(shared_variables.boarding_sem, *shared_variables.reduced_hackers);
            sem_post(shared_variables.mole_mutex2);
        } else if (*boarding_group1 == 2 && *boarding_group2 == 2) {
            sem_signal(sem_group1, 2);
            sem_signal(sem_group2, 2);
            *boarding_group2 = 0;
            *boarding_group1 = 0;
            is_captain = true;
            sem_wait(shared_variables.mole_mutex2);
            print_message(Boards, person_data, shared_variables);
            *shared_variables.queue_reduced = false;
            sem_signal(shared_variables.boarding_sem, *shared_variables.reduced_hackers);
            sem_post(shared_variables.mole_mutex2);
        } 
        sem_post(shared_variables.mole_mutex);
        sem_wait(sem_group1);

        // Getting off the boat.
        if (is_captain) {
            // Let 3 members to board (they print "member exits").
            sem_signal(shared_variables.voyage_sem, 3); 

            sleep_in_millis(0, args.max_voyage_time);

            // Wait for 3 members to get off the boat (when they print "member exits").
            sem_wait_n(shared_variables.voyage_end_sem, 3); 
            
            sem_wait(shared_variables.mole_mutex);
            print_message(Captain_exits, person_data, shared_variables);
            
            // Release 4 processes if there is available enough processes in a possible combination.
            try_to_release_combination(shared_variables); 
            
            sem_post(shared_variables.mole_mutex);
        } else {
            // Wait for captain to allow me to continue to board.
            sem_wait(shared_variables.voyage_sem);

            sem_wait(shared_variables.mole_mutex);
            print_message(Member_exits, person_data, shared_variables);
            sem_post(shared_variables.mole_mutex);

            // Allow the captain continue to get off the boat (let him print "captain exits").
            sem_post(shared_variables.voyage_end_sem);
        }
        break;
    }
    //shared_variables_close(shared_variables);
}