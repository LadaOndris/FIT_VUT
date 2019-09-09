
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
CPP = g++
CPPFLAGS = -std=c++11 -pedantic -Wall

HTAB_OBJS = htab_init.o htab_free.o htab_hash_function.o htab_iterator.o htab_lookup_add.o htab_move.o htab_size.o htab_bucket_count.o

.PHONY: clean all zip

all: tail tail2 wordcount wordcount-dynamic libhtab.a libhtab.so

# sestaveni programu tail a tail2

tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

tail2: tail2.o
	$(CPP) $(CPPFLAGS) $^ -o $@

# sestaveni programu wordcount, wordcount-dynamic a wordcount-cpp

wordcount: wordcount.o custom_hash_function.o io.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^

wordcount-dynamic: wordcount.o custom_hash_function.o io.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^

wordcount-cpp: wordcount-cpp.o
	$(CPP) -std=c++11 -O2 $^ -o $@

wordcount-cpp.o: wordcount.cc
	$(CPP) -std=c++11 -O2 -c $^ -o $@

custom_hash_function.o: custom_hash_function.c htab_hash_function.h
	$(CC) $(CFLAGS) -c $< -o $@


# sestaveni staticke a dynamicke knihovny s hash table

libhtab.a: $(HTAB_OBJS)
	ar rcs $@ $^

libhtab.so: $(HTAB_OBJS)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $^ -o $@


# sestaveni io

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o
	rm -f tail
	rm -f tail2
	rm -f tail-g
	rm -f wordcount
	rm -f wordcount-cpp
	rm -f wordcount-dynamic
	rm -f libhtab.a
	rm -f libhtab.so
	rm -f xondri07.zip

zip:
	zip xondri07.zip *.c *.cc *.h Makefile
