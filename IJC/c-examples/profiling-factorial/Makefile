# Makefile
CFLAGS=-O2 -g -Wall -pg

PROGS = mpfact mpfact-

all: $(PROGS)
#################################################################
mpfact: mpfact.c
	$(CC) $(CFLAGS) -o $@  $^ -lgmp
mpfact-: mpfact.c gmp.o
	$(CC) $(CFLAGS) -I. -o $@  $^
gmp.o: gmp.c
#################################################################
run: $(PROGS)
	time ./mpfact 5000   >mpfact.out
	time ./mpfact- 5000  >mpfact-.out
	gprof ./mpfact- >mpfact-.profile
#################################################################
profile: run
#################################################################
clean:
	rm -f *.o $(PROGS) *.out *.profile

