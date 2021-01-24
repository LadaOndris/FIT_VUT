/**
 * @file shared_variables.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * Contains definitions of functions working 
 * with shared memory and semaphores. 
 */

#include <unistd.h> // close
#include <sys/mman.h> // shm_open, shm_unlink, mmap
#include <sys/stat.h> // shm_open, shm_unlink - For mode constants
#include <fcntl.h> // shm_open, shm_unlink - For O_* constants
#include <semaphore.h> // sem_open, sem_unlink
#include "shared_variables.h"

#define COUNTER_SIZE sizeof(int)
#define FILE_NAME "proj2.out"

static size_t shm_size = 11 * sizeof(sem_t);
static sem_t *sem;
static int *shm_variables;
static size_t shm_varibles_size = 10 * sizeof(int);

int init_sem(sem_t *from, sem_t **to, int value) {
    *to = from;
    return sem_init(*to, 1, value);
}

void init_var(int *from, int **to, int value) {
    *to = from;
    **to = value;
}

int shared_variables_create(Shared_variables_t *sv) {
    sem = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shm_variables = mmap(NULL, shm_varibles_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (sem == MAP_FAILED || shm_variables == MAP_FAILED) {
        fprintf(stderr, "Error: mmap failed.\n");
        return 1;
    }

    int result = init_sem(sem, &(sv->log_sem), 1)
            | init_sem(sem + 1, &(sv->mole_mutex), 1)
            | init_sem(sem + 2, &(sv->mole_mutex2), 1)
            | init_sem(sem + 3, &(sv->voyage_sem), 0)
            | init_sem(sem + 4, &(sv->voyage_end_sem), 0)
            | init_sem(sem + 5, &(sv->getting_off_sem), 0)
            | init_sem(sem + 6, &(sv->hacker_queue_sem), 0)
            | init_sem(sem + 7, &(sv->serf_queue_sem), 0)
            | init_sem(sem + 8, &(sv->hackers_mole_sem), 0)
            | init_sem(sem + 9, &(sv->serfs_mole_sem), 0)
            | init_sem(sem + 10, &(sv->boarding_sem), 0);
    if (result != 0) {
        fprintf(stderr, "Error: init_sem failed.\n");
        shared_variables_destroy(sv);
        return 1;
    }

    init_var(shm_variables, &(sv->counter), 0);
    init_var(shm_variables + 1, &(sv->waiting_hackers), 0);
    init_var(shm_variables + 2, &(sv->waiting_serfs), 0);
    init_var(shm_variables + 3, &(sv->mole_waiting_hackers), 0);
    init_var(shm_variables + 4, &(sv->mole_waiting_serfs), 0);
    init_var(shm_variables + 5, &(sv->is_boat_in_dock), 1);
    init_var(shm_variables + 6, &(sv->waiting_on_mole), 0);
    init_var(shm_variables + 7, &(sv->reduced_hackers), 0);
    init_var(shm_variables + 8, &(sv->reduced_serfs), 0);
    init_var(shm_variables + 9, &(sv->queue_reduced), 0);

    remove(FILE_NAME);
    sv->output_file = fopen(FILE_NAME, "a");
    if (sv->output_file == NULL) {
        fprintf(stderr, "Couldn't open %s file.\n", FILE_NAME);
        shared_variables_destroy(sv);
        return 1;
    }
    else {
        setbuf(sv->output_file, NULL);
    }
    return 0;
}

void shared_variables_destroy(Shared_variables_t *sv) {
    int result = sem_destroy(sv->log_sem)
            | sem_destroy(sv->mole_mutex)
            | sem_destroy(sv->mole_mutex2)
            | sem_destroy(sv->voyage_sem)
            | sem_destroy(sv->voyage_end_sem)
            | sem_destroy(sv->getting_off_sem)
            | sem_destroy(sv->hacker_queue_sem)
            | sem_destroy(sv->serf_queue_sem)
            | sem_destroy(sv->hackers_mole_sem)
            | sem_destroy(sv->serfs_mole_sem)
            | sem_destroy(sv->boarding_sem);
    if (result != 0) {
        fprintf(stderr, "Error: sem_destroy failed.\n");
    }
    if (munmap(sem, shm_size) != 0 ||
        munmap(shm_variables, COUNTER_SIZE) != 0) {
        fprintf(stderr, "Error: munmap failed.\n");
    }
    if (fclose(sv->output_file) != 0) {
        fprintf(stderr, "Error: fclose failed.\n");
    }

}