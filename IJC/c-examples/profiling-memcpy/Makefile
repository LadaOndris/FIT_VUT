
# Test of memory transfer rate
# example of inline assembly - RDTSC

CFLAGS = -std=c99 -O2 -Wall -pedantic
PROG  = memcpy-bench

all: $(PROG)

run: $(PROG)
	./$(PROG) >x
	./$(PROG) >>x
	./$(PROG) >>x
	gnuplot x.plt
	@echo Output is in x.ps
clean:
	rm -f $(PROG) x x.ps
