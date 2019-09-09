
CFLAGS = -std=c99 -O3

all: dep program

program: m1.o m2.o
	$(CC) $(CFLAGS) -o $@  $^

dep:
	gcc -MM *.c >dependency-list

-include dependency-list

clean:
	rm -f *.o program dependency-list
