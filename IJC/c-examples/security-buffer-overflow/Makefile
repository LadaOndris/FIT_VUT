# Makefile for all examples

PROGRAMS = buffer_overflow1 buffer_overflow2 \
           buffer_overflow1-efence  buffer_overflow1-dmalloc 

CFLAGS = -Wall -std=c99 -pedantic

all: $(PROGRAMS)

# tested with valgrind version 2.4.0 on Debian 3.1/Sarge
valgrind: buffer_overflow1
	valgrind ./buffer_overflow1

# not tested
dmalloc: buffer_overflow1-dmalloc
	#DMALLOC_OPTIONS=log=buffer_overflow1-dmalloc.log ./buffer_overflow1-dmalloc
buffer_overflow1-dmalloc: buffer_overflow1.c
	$(CC) $(CFLAGS) $^ -o buffer_overflow1-dmalloc -ldmalloc

# tested with Electric fence version 2.1 on Debian 3.1/Sarge
efence: buffer_overflow1-efence
	./buffer_overflow1-efence
buffer_overflow1-efence: buffer_overflow1.c
	$(CC) $(CFLAGS) $^ -o buffer_overflow1-efence -lefence

clean:
	rm -f $(PROGRAMS)

