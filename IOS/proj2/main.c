/**
 * @file main.c
 * @author Ladislav Ondris (xondri07)
 * @date 20.4.2019
 * 
 * This file is the starting point of the synchronization program. 
 * It calls an argument parser, creates two generator processes and 
 * waits for both of them to finish.
 */

/*
 * Every type of process has its own file.
 * The main process runs in main.c.
 * The two generating processes run in person_generator.c.
 * Hackers and serfs run in person.c.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h> // fork
#include <unistd.h>    // fork
#include <sys/types.h> // waitpid
#include <sys/wait.h>  // waitpid
#include "parse_args.h"
#include "person_generator.h"
#include "person.h"
#include "utils.h"
#include "shared_variables.h"


static pid_t create_person_generating_process(Arguments_t args, PersonType_t person_type, Shared_variables_t shared_variables) {
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(2);
    }
    if (pid == 0) { // child
        start_person_gen(args, person_type, shared_variables);
        exit(0);
    } else { // parent
        return pid;
    }
}

static void wait_for_generating_processes_to_finish(pid_t pid, pid_t pid2) {
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char *argv[]) {
    Arguments_t args = parse_arguments(argc, argv);
    if (args.is_invalid) {
        fprintf(stderr, args.error_message);
        return 1;
    }
    
    Shared_variables_t shared_variables;
    if (shared_variables_create(&shared_variables) != 0)
        return 1;

    pid_t pid = create_person_generating_process(args, Hacker, shared_variables);
    pid_t pid2 = create_person_generating_process(args, Serf, shared_variables);
    wait_for_generating_processes_to_finish(pid, pid2);
    
    shared_variables_destroy(&shared_variables);
    return 0;
}
