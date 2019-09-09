CFLAGS=-std=c99 -Wall -pedantic -g -fprofile-arcs -ftest-coverage

PROGS = dlist-test

all: $(PROGS)

dlist.o: dlist.c dlist.h
dlist-test: dlist-test.c dlist.o dlist.h
	$(CC) $(CFLAGS) -o $@ $< dlist.o

run: dlist-test
	./dlist-test
	@echo ===================================
	gcov -f dlist-test.c
	@echo ===================================
	gcov -f dlist.c
	@echo ===================================
clean:
	rm -f $(PROGS) *.o  *.bb *.bbg *.c.gcov *.da *.gcda *.gcno

