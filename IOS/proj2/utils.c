/**
 * @file utils.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * This file contains other useful functions.
 */

#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h> // usleep
#include <sys/wait.h> // waitpid
#include "utils.h"

int gen_random_number(int lower, int upper) {
    assert(lower <= upper);
    return (rand() % (upper - lower + 1)) + lower;
}

void sleep_in_millis(int from, int to) {
    assert(from <= to);
    int sleep_time_millis = gen_random_number(from, to);
    if (sleep_time_millis == 0)
        return;
    usleep(sleep_time_millis * 1000);
}


void wait_for_processes_to_finish(int pids_count, pid_t *hackers_pids) {
    assert(pids_count > 0);
    for (int i = 0; i < pids_count; i++) {
        waitpid(hackers_pids[i], NULL, 0);
    }
}
