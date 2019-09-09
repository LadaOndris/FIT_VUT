# Makefile for linking test programs

#CFLAGS = -fPIC -Wall -ansi -pedantic
CFLAGS = -Wall -std=c99 -pedantic

#############################################################################
all: static dynamic
static: program-s
dynamic: program-d
#############################################################################
program-s: prog.o m1.o libtest.a
	$(CC) $(CFLAGS) -o program-s -static  prog.o m1.o -L. -ltest

program-d: prog.o m1.o libtest.so
	$(CC) $(CFLAGS) -o program-d  prog.o m1.o -L. -ltest

# create static library 
libtest.a: m2.o m3.o m4.o
	ar crs libtest.a  m2.o m3.o m4.o

# create shared library 
libtest.so: m2.o m3.o m4.o
	$(CC) $(CFLAGS) -shared -o libtest.so  m2.o m3.o m4.o
#############################################################################
run: program-s program-d
	./program-s
	LD_LIBRARY_PATH="." ./program-d

pack:
	tar czvf ijc-link-example.tar.gz Makefile *.c *.h

clean:
	rm -f *.o program-s program-d program libtest.a libtest.so

#############################################################################
