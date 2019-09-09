CFLAGS=-O2 -Wall -std=c99 -pedantic
CC=gcc
PROGS=ackerman-o ackerman
all: $(PROGS)
run: $(PROGS)
	time ./ackerman-o
	time ./ackerman
clean:
	rm -f $(PROGS)
pack:
	tar czvf ackerman.tar.gz *.c Makefile
