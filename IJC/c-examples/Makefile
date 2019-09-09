# Makefile for all examples

#CC=gcc-3.4

PROGRAMS = date-time echo-- memory-protection suchar2 suchar2-err \
           prototype

CFLAGS = -Wall -std=c99 -pedantic

############################################################

all: $(PROGRAMS)

hash_string.o: hash_string.c
	$(CC) $(CFLAGS) -c -o hash_string.o hash_string.c

date-time: date-time.c
	$(CC) -Wall $^ -o $@

suchar2-err: suchar2.c
	$(CC) $(CFLAGS) -DWITH_ERROR $^ -o $@

############################################################

pack: clean-all
	(cd ..; tar czvf ijc-priklady-`date -I`.tar.gz c-examples)

clean:
	rm -f $(PROGRAMS)

clean-all: clean
	for i in `find . -type d | grep -v '\.svn'` ; do (cd $$i; make clean); done

all-dirs: all
	export CC=$(CC); \
	for i in `find . -type d | grep -v '\.svn'` ; do (cd $$i; make); done

############################################################
