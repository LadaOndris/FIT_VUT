
# make run - compile all and test

CFLAGS=-std=c99 -Wall -pedantic -g

PROGS = malloc-free malloc-timing hdump-test dlist-test malloc-overhead memory-leak

all: $(PROGS)

hdump.o: hdump.c hdump.h
hdump-test: hdump-test.c hdump.o hdump.h
	$(CC) $(CFLAGS) -o $@ $< hdump.o

malloc-overhead: malloc-overhead.c hdump.o

dlist.o: dlist.c dlist.h
dlist-test: dlist-test.c dlist.o dlist.h
	$(CC) $(CFLAGS) -o $@ $< dlist.o

clean:
	rm -f $(PROGS) *.o

run: all
	valgrind --tool=memcheck ./memory-leak
	#valgrind --tool=memcheck --leak-check=full ./memory-leak
