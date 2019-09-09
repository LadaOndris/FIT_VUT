# Makefile for all examples

PROGRAMS = getline-test copy-test

CFLAGS = -Wall -std=c99 -pedantic -g

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS) *.o copy-test-input copy-test-output

getline-test: getline-test.c getline.o

run: copy
copy: copy-test
	dd if=/dev/zero of=copy-test-input bs=1024 count=10000
	./copy-test copy-test-input copy-test-output
