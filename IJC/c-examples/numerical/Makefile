# Makefile for all examples

PROGRAMS = cos-tab flt-test epsilon

CFLAGS = -Wall -std=c89 -pedantic

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

cos-tab: cos-tab.c
	$(CC) $(CFLAGS) $^ -lm -o $@

