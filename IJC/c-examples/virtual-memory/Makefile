# Makefile for all examples

PROGRAMS = test-vm test-vm-old

CFLAGS = -Wall 

all: $(PROGRAMS)

run:
	./test-vm >test-vm.out

pack:
	tar czvf ijc-new-examples.tar.gz Makefile *.c 

clean:
	rm -f $(PROGRAMS) *.out

