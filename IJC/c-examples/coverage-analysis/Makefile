
CFLAGS = -fprofile-arcs -ftest-coverage 
CC = gcc
PROG = test-coverage

all: $(PROG)

run: $(PROG)
	./$(PROG)
	gcov $(PROG).c
	#gcov -a $(PROG).c    # +basic blocks
	#gcov -b $(PROG).c    # +branch analysis

clean:
	rm -f $(PROG) *.gcov *.gcda *.gcno

