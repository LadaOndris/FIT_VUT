
# make run - spusti test

CFLAGS=-O3 -Wall -std=c99 -pedantic -g
#CFLAGS=-O2 -Wall -std=c99 -pedantic -g -pg
CC=gcc
PROGS = list list-o

all: $(PROGS)
run: $(PROGS)
	time ./list  10000000
	#gprof ./list >list.profile
	time ./list-o  10000000
	#gprof ./list-o >list-o.profile
clean:
	rm -f $(PROGS)

