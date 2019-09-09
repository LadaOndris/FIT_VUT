PROGS=program crack
CFLAGS=-g
all: $(PROGS)
run: $(PROGS)
	./crack 0xbffff850 | ./program
pack:
	tar czvf crack-test.tar.gz *.c Makefile
clean:
	rm -f $(PROGS)
