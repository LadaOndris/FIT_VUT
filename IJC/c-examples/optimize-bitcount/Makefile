CC=gcc -Wall -std=c99 -pedantic -fomit-frame-pointer
test-O3: test.o bitcount.c Makefile
	$(CC) -O0 test.o bitcount.c -o test-O0
	$(CC) -O0 bitcount.c -o bitcount-O0.s -S
	$(CC) -O1 test.o bitcount.c -o test-O1
	$(CC) -O1 bitcount.c -o bitcount-O1.s -S
	$(CC) -O2 test.o bitcount.c -o test-O2
	$(CC) -O2 bitcount.c -o bitcount-O2.s -S
	$(CC) -O3 test.o bitcount.c -o test-O3
	$(CC) -O3 bitcount.c -o bitcount-O3.s -S

test.o: test.c

run: test-O3 test-O2 test-O1 test-O0
	./test-O0 >test-O0.out
	./test-O1 >test-O1.out
	./test-O2 >test-O2.out
	./test-O3 >test-O3.out
	cat test-O[0123].out | sort -u >test.out
clean:
	rm -f test.o test-O[0123] test-O[0123].out test.out \
	      bitcount-O[0123].s bitcount[12] bitcount.ps

plot: run
	grep bitcount1 <test.out | cut --output-delimiter=" " -c1-6,23,34 >bitcount1
	grep bitcount2 <test.out | cut --output-delimiter=" " -c1-6,23,34 >bitcount2
	gnuplot bitcount.plt
	@echo Vysledek je v bitcount.ps

