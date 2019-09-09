CC=gcc -Wall -std=c99 -pedantic -fomit-frame-pointer
test-O3: test.o bitpos.c Makefile
	$(CC) -O0 test.o bitpos.c -o test-O0
	$(CC) -O0 bitpos.c -o bitpos-O0.s -S
	$(CC) -O1 test.o bitpos.c -o test-O1
	$(CC) -O1 bitpos.c -o bitpos-O1.s -S
	$(CC) -O2 test.o bitpos.c -o test-O2
	$(CC) -O2 bitpos.c -o bitpos-O2.s -S
	$(CC) -O3 test.o bitpos.c -o test-O3
	$(CC) -O3 bitpos.c -o bitpos-O3.s -S

test.o: test.c

run: test-O3 test-O2 test-O1 test-O0
	./test-O0 >test-O0.out
	./test-O1 >test-O1.out
	./test-O2 >test-O2.out
	./test-O3 >test-O3.out
	cat test-O[0123].out | sort -u >test.out
clean:
	rm -f test.o test-O[0123] test-O[0123].out test.out \
	      bitpos-O[0123].s bitpos[12] bitpos.ps

plot: run
	grep bitpos1 <test.out | cut --output-delimiter=" " -c1-6,21,32 >bitpos1
	grep bitpos2 <test.out | cut --output-delimiter=" " -c1-6,21,32 >bitpos2
	gnuplot bitpos.plt
	@echo Vysledek je v bitpos.ps

