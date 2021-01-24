#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define LINE_LEN 1002
#define COMMANDS_LEN 100

void print_help();
bool read_commands(const char *file_name, char commands[][LINE_LEN]);
int process_command(char *command, char *line, int *command_index, 
		bool *end_of_stdin_reached, bool *is_next_line_read, char last_printed_line[]);
int process_i(char *command);
int process_b(char *command, char *line);
int process_a(char *command, char *line);
int process_d(char *command, char *line, bool *end_of_stdin_reached, bool *is_next_line_read);
int process_r(char *command, char *line);
int process_n(char *command, char *line, bool *end_of_stdin_reached, 
		bool *is_next_line_read, char last_printed_line[]);
int process_q(char *command, bool *end_of_stdin_reached);
int process_g(char *command, int *current_cmd_index);
int process_s(char *command, char *line);
int process_S(char *command, char *line);
int process_f(char *command, char *line, bool *end_of_stdin_reached, 
		bool *is_next_line_read, char last_printed_line[]);
int process_c(char *command, char *line, int *command_index);
int process_e(char *command, char *line);
int process_replacement(char *command, char *line, bool replace_all_occurrences);
bool get_pattern_replacement(char *command, char *pattern, char **replacement);
char *replace(char *line, const char *pattern, const char *replacement);
void remove_eol(char *str);
char *move_to_next_line(char *line);
char *read_next_line(char *str, int maxlen);
int check_line_len(char *line, char *source);
int get_reps(char *str);
void print_EOL_if_not_present(char *line);

int main(int argc, char *argv[]) {
	// Check arguments and print help eventually.
	if (argc != 2) {
		print_help();
		return 0;
	}

	char commands[COMMANDS_LEN][LINE_LEN] = {0};
	char line[LINE_LEN];
	char last_printed_line[LINE_LEN] = {0};
	int command_index = 0;
	char *command;
	bool end_of_stdin_reached = false;
	bool commands_passed[COMMANDS_LEN] = { false };

	if (read_commands(argv[1], commands) == false) { 
		return 1;
	}
	if (read_next_line(line, LINE_LEN) == NULL) {
		return 0; 
	}
	else if (check_line_len(line, "Input text") != 0) { 
		return 1;
	}

	// Process all commands until the end of stdin is reached.
	while (end_of_stdin_reached == false && command_index != COMMANDS_LEN) {
		if (commands_passed[command_index] == true) { // endless loop check
			fprintf(stderr, "Line %d: Endless loop detected.\n", command_index + 1);
			return 1;
		}
		commands_passed[command_index] = true;
		
		command = commands[command_index][0] != '\0' ? commands[command_index] : "n";
		bool is_next_line_read = false;
		int result = process_command(command, line, &command_index, &end_of_stdin_reached, 
				&is_next_line_read, last_printed_line);
		if (result < 0)
			return -1;

		if (is_next_line_read == true) { // needed for endless loop detection
			memset(commands_passed, false, sizeof commands_passed);
		}
		command_index++;
	}
	print_EOL_if_not_present(last_printed_line);
	return 0;
}

void print_help() {
	printf(
		"Project 1 - Text editor\n"
		"2018, Ladislav Ondris\n"	
		"-------------------------\n"
		"HELP:\n"
		"Description:\n"
		"The editor processes commands from a file given as an argument and edits input text accordingly."
		" The input text to be edited is read from stdin.\n"
		"Commands:\n"
		"iCONTENT - inserts a new line before the current line\n"
		"bCONTENT - prepends CONTENT to the beginning of the current line\n"
		"aCONTENT - appends CONTENT at the end of the current line\n"
		"d - deletes current line\n"
	    "r - removes EOL from the end of the current line\n"
		"s:PATTERN:REPLACEMENT - replace the first occurrence of PATTERN in the current line by REPLACEMENT\n"
		"S:PATTERN:REPLACEMENT - replace all occurrences of PATTERN in the current line by REPLACEMENT\n"
		"n - write current line and move to the next\n"
		"q - quit editing\n"
		"fPATTERN - read input lines from stdin until there is an occurrence of PATTERN in the current line\n"
		"cX PATTERN - conditioned goto, if the current line contains PATTERN jump to X-th command\n"
		"e - appends EOL at the end of the current line\n\n\n"	
	);
}

// Reads all commands from file with specified file_name
// and saves it to the commands array.
// Returns false if length of the line is too long or 
// the maximal number of commands is exceeded, otherwise true.
bool read_commands(const char *file_name, char commands[][LINE_LEN]) {
	int line_index = 0;
	char line_buffer[LINE_LEN];
	
	FILE *fr;
	if ((fr = fopen(file_name, "r")) == NULL) {
		return 0;
	}

	while (fgets(line_buffer, LINE_LEN, fr) != NULL) {
		if (line_index == COMMANDS_LEN) {
			fprintf(stderr, "Maximum number of commands exceeded. Only 100 commands is allowed.\n");
			fclose(fr);
			return false;
		}
		remove_eol(line_buffer);
		if (check_line_len(line_buffer, "Commands file") != 0) {
			fclose(fr);
			return false;
		}
		strcpy(commands[line_index++], line_buffer);
	}
	fclose(fr);
	return true;
}

// Processes a command for the given line.
// Returns 0 if success, otherwise non-zero number.
int process_command(char *command, char *line, int *command_index, 
	bool *end_of_stdin_reached, bool *is_next_line_read, char last_printed_line[]) {
	switch (command[0]) {
		case 'i': return process_i(command);
		case 'b': return process_b(command, line);
		case 'a': return process_a(command, line);
		case 'd': return process_d(command, line, end_of_stdin_reached, is_next_line_read);
		case 'r': return process_r(command, line);
		case 'n': return process_n(command, line, end_of_stdin_reached, is_next_line_read, last_printed_line);
		case 'q': return process_q(command, end_of_stdin_reached);
		case 'g': return process_g(command, command_index); 
		case 's': return process_s(command, line);
		case 'S': return process_S(command, line);
		case 'f': return process_f(command, line, end_of_stdin_reached, is_next_line_read, last_printed_line);
		case 'c': return process_c(command, line, command_index);
		case 'e': return process_e(command, line);
		default: {  
			fprintf(stderr, "Command |%c| is not supported.\n", command[0]); 
			return -1;
		}
	}
}

// Prints specified text as a new line.
// Returns 0.
int process_i(char *command) {
	puts(&command[1]);
	return 0;
}

// Prepands specified text to the beginning of the current line.
// Returns -1 if an error occurs, otherwise 0.
int process_b(char *command, char *line) {
	if (strlen(&command[1]) + strlen(line) >= LINE_LEN) {
		fprintf(stderr, "Command 'b' could not be executed. Line would be too long.\n");
		return -1;
	}

	int len = strlen(&command[1]);
	memmove(line + len, line, strlen(line) + 1);
    
	for (int i = 0; i < len; ++i)
		line[i] = command[i + 1];
	
	return 0;
}

// Appends specified text to the current line.
// The specified text is appended before EOL if EOL exists at the end of the line.
// Returns -1 if an error occurs, otherwise 0.
int process_a(char *command, char *line) {
	if (strlen(&command[1]) + strlen(line) >= LINE_LEN) {
		fprintf(stderr, "Command 'a' could not be executed. Line would be too long.\n");
		return -1;
	}
	char *new_line_char = strchr(line, '\n');
	remove_eol(line);
	strcat(line, &command[1]);
	if (new_line_char != NULL) {
		strcat(line, "\n");
	}
	return 0;
}

// Moves to the next line without printing the current one.
// Repeats N times if specified, default is 1.
// If end of stdin is reached, sets the end_of_stdin_reached to true.
// Sets is_next_line_read to true if new line is read.
// Returns -1 if an error occurs, otherwise 0.
int process_d(char *command, char *line, bool *end_of_stdin_reached, bool *is_next_line_read) {
	int reps = strlen(&command[1]) == 0 ? 1 : get_reps(&command[1]);
	if (reps <= 0) { 
		fprintf(stderr, "Format error: command 'd' not specified properly.\n");
		return -1;
	}
	for (int i = 0; i < reps; i++) {
		if (read_next_line(line, LINE_LEN) == NULL) {
			*end_of_stdin_reached = true;
			return 0; 
		}
		else if (check_line_len(line, "Command 'd'") != 0) { 
			return -1;
		}
		*is_next_line_read = true;
	}
	return 0;
}

// Removes EOL character from the end of line.
// If a format error occurs, returns -1. Otherwise returns 0.
int process_r(char *command, char *line) {
	if (strlen(command) != 1) {
		fprintf(stderr, "Format error: command 'r' not specified properly. No text can follow the 'r' command.\n");
		return -1;
	}
	remove_eol(line);
	return 0;
}

// Prints current line and moves to the next. 
// It goes through N lines if specified in the command, 
// default is 1. If end of stdin is reached, sets the end_of_stdin_reached to true.
// At the end of every line prints a new line character if print_eol is not set to false. 
// Sets is_next_line_read to true if new line is read.
// Returns -1 if an error occurs, otherwise 0.
int process_n(char *command, char *line, bool *end_of_stdin_reached,
	   	bool *is_next_line_read, char last_printed_line[]) {
	int reps = strlen(&command[1]) == 0 ? 1 : get_reps(&command[1]);
	if (reps <= 0) { 
		fprintf(stderr, "Format error: command 'n' not specified properly.\n");
		return -1;
	}
	for (int i = 0; i < reps; i++) {
		strcpy(last_printed_line, line);
		if (move_to_next_line(line) == NULL) {
			*end_of_stdin_reached = true;
			return 0;
		}
		else if (check_line_len(line, "Command 'n'") != 0) { 
			return -1;
		}
		*is_next_line_read = true;
	}
	return 0;
}

// Checks the format of a q command. 
// If a format error occurs, returns -1. Otherwise returns 0.
int process_q(char *command, bool *end_of_stdin_reached) {
	if (strlen(command) != 1) {
		fprintf(stderr, "Format error: command 'q' not specified properly. No text can follow the 'q' command.\n");
		return -1;
	}
	*end_of_stdin_reached = true;
	return 0;
}

// Processes g command and sets the current command index.
// Returns -1 if an error occurs, otherwise 0.
int process_g(char *command, int *current_cmd_index) {
	int cmd_index = get_reps(&command[1]);
	if (cmd_index <= 0 || strlen(&command[1]) == 0) {
		fprintf(stderr, "Format error: command 'g' not specified properly.\n");
		return -1;
	}
	cmd_index--;
	if (cmd_index >= COMMANDS_LEN) {
		fprintf(stderr, "Command 'g' at index %d jumps to nonexisting command index (%d).", *current_cmd_index, cmd_index);
		return -1;
	}	
	*current_cmd_index = cmd_index - 1;
	return 0;
}

// Replaces first occurrence of pattern by replacement in the line.
int process_s(char *command, char *line) {
	return process_replacement(command, line, false);
}

// Replaces all occurences of pattern by replacement in the line.
int process_S(char *command, char *line) {
	return process_replacement(command, line, true);
}

// Replaces one or all occurrences of pattern by replacement in 
// the line.
// Return -1 if an error occurs, otherwise 0.
int process_replacement(char *command, char *line, bool replace_all_occurrences) {
	if (strlen(command) < 4) {
		fprintf(stderr, "Command 's' not specified properly. Command length is too short to work.\n");
		return -1;
	}
	char pattern[LINE_LEN];
	char *replacement;

	bool result = get_pattern_replacement(command, pattern, &replacement);
	if (result == false) {
		return 0;
	}
	char *p_char = line;
	while ((p_char = replace(p_char, pattern, replacement)) != NULL && replace_all_occurrences);
	return 0;
}

// Searches lines one after the other until it finds specified string
// following the f command. Searching stops when the specified string 
// is found or end of stding is reached. Sets is_next_line_read to true if new line is read.
// Returns -1 if an error occurs, otherwise 0. 
int process_f(char *command, char *line, bool *end_of_stdin_reached,
	   	bool *is_next_line_read, char last_printed_line[]) {
	char *pattern = &command[1];
	if (strlen(pattern) == 0) {
		fprintf(stderr, "Command 'f' not specified properly. Pattern has to be specified.\n");
		return -1;
	}
	do {
		strcpy(last_printed_line, line);
		if (move_to_next_line(line) == NULL) {
			*end_of_stdin_reached = true;
			return 0;
		}
		else if (check_line_len(line, "Command 'f'") != 0) { 
			return -1;
		}
		*is_next_line_read = true;
	} while (strstr(line, pattern) == NULL);	
	return 0;
}


// Jumps to specified command if the line contains specified string.
// Returns -1 if an error occured, otherwise 0.
int process_c(char *command, char *line, int *command_index) {
	if (strlen(command) < 4) {
		fprintf(stderr, "Command 'c' not specified properly. Command length is too short to work.\n");
		return -1;
	}
	
	char *p_end; 	
	int cmd_index = strtol(&command[1], &p_end, 10);
	if (p_end[0] != ' ' || cmd_index <= 0) {
		fprintf(stderr, "Format error: command 'c' not specified properly.\n");
		return -1;
	}
	if (strstr(line, &p_end[1]) != NULL)
		*command_index = cmd_index - 2;
	return 0;
}

// Appends new line character to the line.
// Returns -1 if an error occured, otherwise 0.
int process_e(char *command, char *line) {
	if (strlen(command) != 1) {
		fprintf(stderr, "Format error: command 'e' not specified properly. No text can follow the 'e' command.\n");
		return -1;
	}
	if (strlen(line) + 1 >= LINE_LEN) {
		fprintf(stderr, "Command 'e' could not be processed. Line would be too long.\n");
		return -1;
	}
	strcat(line, "\n");
	return 0;
}


// Takes pointer to a command "s:pattern:replacement", parses it and 
// sets the pattern and replacement accordingly.
// Returns false if a parse error occured, otherwise true.
bool get_pattern_replacement(char *command, char *pattern, char **replacement) {
	char *separator = &command[1];
	if (!isprint(*separator)) {
		fprintf(stderr, "Pattern replacement: Separator is not a printable character.\n");
		return false;
	}
	
	char *second_separator = strchr(&separator[1], separator[0]);
	if (second_separator == NULL) {
		fprintf(stderr, "Pattern replacement: Pattern and replacement could not be determined. Separator missing.\n");
		return false;
	}	
	char *p_pattern = &separator[1];
	*replacement = &second_separator[1];
	int pattern_len = (second_separator - separator - 1) / sizeof *separator;
	memcpy(pattern, p_pattern, pattern_len);
	pattern[pattern_len] = '\0';
	if (strlen(pattern) == 0) {
		fprintf(stderr, "Pattern replacement: Pattern cannot be empty.\n");
		return false;
	}
	return true;
}

// Searches the line for specified pattern and replaces it with replacement.
// Returns a pointer to char which comes after the last char of found occurence. 
// If pattern is not found, returns NULL.
char *replace(char *line, const char *pattern, const char *replacement) {
	int pattern_len = strlen(pattern);
	char *p_char = line;
	char *occurrence = strstr(p_char, pattern);
	if (occurrence == NULL)
		return NULL;
	p_char += pattern_len;
	char temp_line[LINE_LEN];
	memcpy(temp_line, line, occurrence - line);
	temp_line[occurrence - line] = '\0';
	if (strlen(line) + strlen(replacement) - pattern_len >= LINE_LEN) {
		fprintf(stderr, "Command for pattern replacement could not be processed. Line would be too long.\n");
		return NULL;
	}
	strcat(temp_line, replacement);
	strcat(temp_line, occurrence + pattern_len);
	strcpy(line, temp_line);
	return p_char;
}

// Removes EOL character from the end of a str.
void remove_eol(char *str) {
	int len = strlen(str);
	if (str[len-1] == '\n') {
		str[len-1] = '\0';
	}	
}

// Writes current line to stdout and reads new line for editing.
// Returns NULL if end of file occurs. Otherwise returns pointer to str.
char *move_to_next_line(char *line) {
	fputs(line, stdout);
	return read_next_line(line, LINE_LEN);
}

// Reads a line to str and removes its EOL. 
// Returns NULL if end of file occurs. Otherwise returns pointer to str.
char *read_next_line(char *str, int maxlen) {
	char *ptr = fgets(str, maxlen, stdin);
	return ptr;
}

// Checks that the length of the line is under particular value.
// If the line is too long, prints message and returns -1, otherwise returns 0.
int check_line_len(char *line, char *source) {
	if (strlen(line) >= LINE_LEN - 1) {
		fprintf(stderr, "%s: Line is too long. The line begins with %.7s...\n", source, line);
		return -1;
	}
	return 0;
}

// Converts str to int. 
// If an error occurs or simply str does not contain a number, 0 is returned.
// Otherwise returns integer.
int get_reps(char *str) {
	char *pEnd;
	int reps = strtol(str, &pEnd, 10);
	if (*pEnd != '\0') 
		 return 0;
	return reps;
}

void print_EOL_if_not_present(char *last_printed_line) {
	int last_printed_line_len = strlen(last_printed_line);
	if (last_printed_line_len > 0 &&
		last_printed_line[last_printed_line_len - 1] != '\n') {
		printf("\n");
	}
}
