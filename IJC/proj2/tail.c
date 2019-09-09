// tail.c 
// IJC-DU2, part a), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: gcc 8.3.1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define LINE_MAX_CHAR (1023 + 1) 
#define DEFAULT_LINES_NUM 10

void free_array(char **arr, int items_count) {
    for (int i = items_count - 1; i >= 0; i--) {
        free(arr[i]);
    }
    free(arr);
}

char **alloc_string_array(int num_lines) {
    char **lines = malloc(num_lines * sizeof(char *));
    if (lines == NULL) {
        return NULL;
    }
    for (int i = 0; i < num_lines; i++) {
        lines[i] = malloc(LINE_MAX_CHAR);
        if (lines[i] == NULL) {
            free_array(lines, i);
            return NULL;
        }
    }
    return lines;
}

char *read_line(char *buffer, FILE *file, bool *whole_line_was_read) {
    if (fgets(buffer, LINE_MAX_CHAR, file) == NULL) {
        return NULL;
    }
    int buffer_len = strlen(buffer);
    *whole_line_was_read = buffer[buffer_len - 1] == '\n' ? true : false;
    
    if (buffer_len == LINE_MAX_CHAR - 1 && buffer[LINE_MAX_CHAR - 2] != '\n') {
        buffer[LINE_MAX_CHAR - 2] = '\n';
    }
    
    return buffer;
}

int read_and_print_lines(FILE *file, int num_lines, bool read_files_from_beginning) {
    if (num_lines == 0) {
        return 0;
    }
    
    int lines_counter = 0;
    char buffer[LINE_MAX_CHAR];
    bool skip_next = false;
    bool whole_line_was_read = false;
    bool line_trimmed = false;
    
    if (read_files_from_beginning) {
        while (read_line(buffer, file, &whole_line_was_read)) {
            if (!skip_next) {
                lines_counter++;
                if (lines_counter < num_lines) {
                    continue;
                }
                printf("%s", buffer);
            }
            skip_next = !whole_line_was_read;
            if (!whole_line_was_read) {
                line_trimmed = true;
            }
        }
        
        if (ferror(file)) {
            perror("Error");
            fprintf(stderr, "Error occurred while reading file. Lines read: %d\n", lines_counter);
            return -1;
        }
    }
    else {
        char **lines = alloc_string_array(num_lines);
        if (lines == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return -1;
        }
    
        int current_index = 0;
        
        while (read_line(buffer, file, &whole_line_was_read) != NULL) {
            if (!skip_next) {
                strcpy(lines[current_index], buffer);
                current_index = (current_index + 1) % num_lines;
                lines_counter++;
            }
            skip_next = !whole_line_was_read;
            if (!whole_line_was_read) {
                line_trimmed = true;
            }
        }
        
        if (ferror(file)) {
            perror("Error");
            fprintf(stderr, "Error occurred while reading file. Lines read: %d\n", lines_counter);
            free_array(lines, num_lines);
            return -1;
        }
    
        if (lines_counter != 0) {
        
            if (lines_counter < num_lines) {
                current_index = 0;
            }
        
            int starting_index = current_index;
            do {
                printf("%s", lines[current_index]);
                current_index = (current_index + 1) % num_lines;
            } while (current_index != starting_index && --lines_counter > 0);
        
        }
        free_array(lines, num_lines);
    }
    if (line_trimmed) {
        fprintf(stderr, "Line was trimmed because it was too long.\n");
    }
    return 0;
}

int parse_args(int argc, char *argv[], bool *plus_sign, int *lines_to_print, char **next_arg) {
    if (argc > 4) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }
    
    if (strcmp(argv[1], "-n") == 0) {
        if (argc >= 3) {
            if (argv[2][0] == '+')
                *plus_sign = true;
            
            errno = 0;
            char *endptr = NULL;
            *lines_to_print = strtol(argv[2], &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                fprintf(stderr, "Failed to parse argument -n.\n");
                return 1;
            }
            *next_arg = argv[3];
        }
        else {
            fprintf(stderr, "Wrong number of arguments.\n");
            return 1;
        }
    }
    else if (argc != 2) {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }
    *lines_to_print = abs(*lines_to_print);
    return 0;
}

int main(int argc, char *argv[]) {
    bool skip_lines = false;
    int lines_to_print = DEFAULT_LINES_NUM;
    char *next_arg = argv[1];
    
    if (next_arg != NULL) {
        int result = parse_args(argc, argv, &skip_lines, &lines_to_print, &next_arg);
        if (result != 0) {
            return result;
        }
    }

    FILE *file;
    if (next_arg == NULL) {
        file = stdin;
    }
    else {
        if ((file = fopen(next_arg, "r")) == NULL) {
            fprintf(stderr, "Failed to open file.\n");
            return 1;
        }
    }
    read_and_print_lines(file, lines_to_print, skip_lines);
    
    fclose(file);
    return 0;
}
