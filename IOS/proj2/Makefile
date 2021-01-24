SERVER = xondri07@merlin.fit.vutbr.cz
SERVER_DIR = ~/IOS/proj2/
ZIP_FILE = proj2.zip

CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic -g -pthread -lrt
EXECUTABLE = proj2
OBJS = main.o parse_args.o utils.o person_generator.o person.o shared_variables.o

.PHONY: all pack run clean upload

all: $(EXECUTABLE)
pack: proj2.zip
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(CMDLINE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) *.o $(ZIP_FILE)

proj2.zip:
	zip -j $(ZIP_FILE) *.c *.h Makefile

upload: $(ZIP_FILE)
	scp $(ZIP_FILE) $(SERVER):$(SERVER_DIR)
	ssh $(SERVER) "cd $(SERVER_DIR) && unzip $(ZIP_FILE) && make"

valgrind: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE) $(CMDLINE)

gdb: $(EXECUTABLE)
	gdb -ex ./$(EXECUTABLE) --args $(CMDLINE)

leaks: $(EXECUTABLE)
	valgrind --track-origins=yes --leak-check=full \
	--show-reachable=yes ./$(EXECUTABLE) $(CMDLINE)
