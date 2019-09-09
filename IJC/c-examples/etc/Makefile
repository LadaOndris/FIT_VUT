PROGS = kbhit-unix-test pentium-bug time-profile \
	huff ship # watch the warnings for old code

CFLAGS = -O2 -g -Wall

all: $(PROGS)

kbhit-unix-test: kbhit-unix-test.c kbhit-unix.c

run: $(PROGS)
	./time-profile >time-profile.out
	gnuplot time-profile.plt
	gv time-profile.ps
clean:
	rm -f *.o $(PROGS) *.out *.ps
