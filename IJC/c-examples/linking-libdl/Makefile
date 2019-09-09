CFLAGS=-g -ldl
PROG=program
LIBS=libtest1.so libtest2.so
all: $(PROG)

all: $(PROG) $(LIBS)
libtest1.so: libtest1.c
	gcc -g -shared -o libtest1.so $^
libtest2.so: libtest2.c
	gcc -g -shared -o libtest2.so $^

run: $(PROG)
	./program

clean:
	rm -f $(PROG) $(LIBS)
