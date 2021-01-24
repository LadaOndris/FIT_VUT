/**
 * @file utils.h
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * This file contains declarations of other useful functions.
 */

#ifndef UTILS_H
#define UTILS_H

#include <semaphore.h> // sem_t

/**
 * Generates a random number in the interval from lower to upper including.
 * It doesn't call srand. A caller has to do it himself.
 * @pre lower <= upper
 * @param lower The lower limit of the interval to generate number.
 * @param upper The upper limit of the interval to generate number.
 * @return Returns a random integer from the given interval.
 */
int gen_random_number(int lower, int upper);

/**
 * Calls usleep for a number of milliseconds randomly
 * chosen from the interval between from and to including.
 * @pre from <= to
 * @param from The lower limit of the interval.
 * @param to The uppoer limit of the interval. 
 */
void sleep_in_millis(int from, int to);

/**
 * Waits for all given processes to finish.
 * @pre pids_count > 0
 * @param pids_count Number of processes in hackers_pids array.
 * @param hackers_pids An array of pids of processes.
 */
void wait_for_processes_to_finish(int pids_count, pid_t *hackers_pids);

#endif //UTILS_H
