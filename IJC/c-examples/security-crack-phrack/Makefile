CFLAGS=-std=c99 -pedantic -Wall
test1: test1.c

run: test1
	./test1
	./test1 canary
clean:
	rm -f test1

pack:
	tar czvf phrack-crack.tar.gz Makefile *.c *.txt
