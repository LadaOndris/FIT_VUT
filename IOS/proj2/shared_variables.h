/**
 * @file shared_variables.h
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * Contains declarations for functions for working 
 * with shared memory and semaphores. Provides a structure
 * Shared_variables_t to hold all those variables.
 */

#ifndef SHARED_VARIABLES_H
#define SHARED_VARIABLES_H

#include <stdio.h>
#include <semaphore.h> // sem_t

typedef struct {
    sem_t *mole_mutex;
    sem_t *mole_mutex2;
    sem_t *voyage_sem;
    sem_t *voyage_end_sem;
    sem_t *getting_off_sem;
    sem_t *hacker_queue_sem;
    sem_t *serf_queue_sem;
    sem_t *hackers_mole_sem;
    sem_t *serfs_mole_sem;
    sem_t *log_sem;
    sem_t *boarding_sem;
    int *waiting_hackers;
    int *waiting_serfs;
    int *mole_waiting_hackers;
    int *mole_waiting_serfs;
    int *reduced_hackers;
    int *reduced_serfs;
    int *queue_reduced;
    int *is_boat_in_dock;
    int *waiting_on_mole;
    int *counter;
    FILE *output_file;
} Shared_variables_t;

/**
 * Creates and initializes shared variables and sets them
 * into the Shared_variables_t struct given as a parameter.
 * 
 * @return Returns 0 on success, and nonzero if error.
 */
int shared_variables_create(Shared_variables_t *sv);
/**
 * Destroys shared variables set in Shared_variables_t struct 
 * given as a parameter. Destroys semaphores, unlinks shared
 * memory and closes file.
 */
void shared_variables_destroy(Shared_variables_t *sv);

#endif //SHARED_VARIABLES_H