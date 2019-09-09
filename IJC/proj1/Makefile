
LC_ALL=cs_CZ.utf8
CC=gcc
CFLAGS= -O2 -std=c11 -Wall -pedantic


default:
	make primes
	make primes-i
	make steg-decode

run: primes primes-i
	time ./primes
	time ./primes-i

primes: primes.o eratosthenes.o error.o bit_array.o
	$(CC) $(CFLAGS) -o primes primes.o eratosthenes.o error.o bit_array.o -lm

primes-i: primes-i.o eratosthenes-i.o error.o bit_array-i.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o primes-i primes-i.o eratosthenes-i.o error.o bit_array-i.o -lm


primes.o: primes.c bit_array.h
	$(CC) $(CFLAGS) -c primes.c

primes-i.o: primes.c bit_array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o


error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c

ppm.o: ppm.c ppm.h error.h
	$(CC) $(CFLAGS) -c ppm.c


eratosthenes.o: eratosthenes.c eratosthenes.h bit_array.h
	$(CC) $(CFLAGS) -c eratosthenes.c

eratosthenes-i.o: eratosthenes.c eratosthenes.h bit_array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o


steg-decode: steg-decode.o error.o ppm.o eratosthenes.o bit_array.o
	$(CC) $(CFLAGS) -o steg-decode steg-decode.o error.o ppm.o eratosthenes.o bit_array.o -lm

steg-decode.o: steg-decode.c error.h ppm.h bit_array.h eratosthenes.h
	$(CC) $(CFLAGS) -c steg-decode.c


bit_array.o: bit_array.c bit_array.h
	$(CC) $(CFLAGS) -c bit_array.c

bit_array-i.o: bit_array.c bit_array.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bit_array.c -o bit_array-i.o



clean:
	rm -f *.o
	rm -f primes
	rm -f primes-i
	rm -f steg-decode
