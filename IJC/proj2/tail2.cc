// tail2.cc 
// IJC-DU2, part a), 24.4.2019 
// Author: Ladislav Ondris, FIT, xondri07@stud.fit.vutbr.cz
// Compiled: g++ 8.3.1

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

#define DEFAULT_LINES_NUM 10

int read_and_print_lines(istream *stream, int num_lines, bool read_files_from_beginning) {
    if (num_lines == 0) {
        return 0;
    }
    
    int lines_counter = 0;
    string line;

    if (read_files_from_beginning) {

        while (getline(*stream, line)) {

            lines_counter++;
            if (lines_counter >= num_lines) 
                cout << line << endl;
        }
        if (cin.bad() || !cin.eof()) {
            // IO error || format error (not possible with getline but possible with operator>>)
            cerr << "Error occurred while reading file. Lines read: " << lines_counter << endl;
            return 1;
        } 
    }
    else {
        queue<string> queue;

        while (getline(*stream, line)) {
            lines_counter++;
            queue.push(line);
            if (lines_counter > num_lines)
                queue.pop();
        }

        if ((*stream).eof()) {
            // format error (not possible with getline but possible with operator>>)
            // or end of file (can't make the difference)
            while (!queue.empty()) {
                cout << queue.front() << endl;
                queue.pop();
            }
        }
        else {
            cerr << "Error occurred while reading file. Lines read: " << lines_counter << endl;
            return 1;
        }
    }
    return 0;
}

int parse_args(int argc, char *argv[], bool *plus_sign, int *lines_to_print, char **next_arg) {
    if (argc > 4) {
        cerr << "Wrong number of arguments." << endl;
        return 1;
    }
    string argv1(argv[1]);
    if (!argv1.compare("-n")) {
        if (argc >= 3) {
            if (argv[2][0] == '+')
                *plus_sign = true;
            
            errno = 0;
            char *endptr = NULL;
            *lines_to_print = strtol(argv[2], &endptr, 10);
            if (errno != 0 || *endptr != '\0') {
                cerr << "Failed to parse argument -n." << endl;
                return 1;
            }
            
            *next_arg = argv[3];
        }
        else {
            cerr << "Wrong number of arguments." << endl;
            return 1;
        }
    }
    else if (argc != 2) {
        cerr << "Wrong number of arguments." << endl;
        return 1;
    }
    *lines_to_print = abs(*lines_to_print);
    return 0;
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    bool skip_lines = false;
    int lines_to_print = DEFAULT_LINES_NUM;
    char *next_arg = argv[1];
    
    if (next_arg != NULL) {
        int result = parse_args(argc, argv, &skip_lines, &lines_to_print, &next_arg);
        if (result != 0) {
            return result;
        }
    }

    std::istream *stream;
    std::ifstream fs;
    if (next_arg == NULL) {
        stream = &cin;
    }
    else {
        fs.open(next_arg);

        if (!fs.is_open()) {
            cerr << "Failed to open file.\n";
            return 1;
        }
        stream = &fs;
    }
    read_and_print_lines(stream, lines_to_print, skip_lines);
    
    if (fs.is_open()) {
        fs.close();
    }
    return 0;
}
