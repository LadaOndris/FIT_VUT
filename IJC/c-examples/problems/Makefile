PROGS = problem1 problem2-O0 problem2-O3
CFLAGS = -Wall -std=c99 -pedantic

all: $(PROGS)

problem2-O0: problem2.c
	$(CC) $(CFLAGS) -O0 $^ -o $@
problem2-O3: problem2.c
	$(CC) $(CFLAGS) -O3 $^ -o $@

clean:
	rm -f $(PROGS)
