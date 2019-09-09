/* bitcount.c
 * test efektivity algoritmu
 * POZOR: program predpoklada 32 bitovy unsigned long
 */

/* bitcount1
 * pocet bitu 1 v cisle d
 */
unsigned bitcount1(unsigned long d)
{
    int count=0;
    while(d!=0) {
        count += (d & 1);
        d >>= 1;
    }
    return count;
}

   /*********************************************************************
      
      NAME		: Count
      
      INPUT		: unsigned int w
      
      RESULT		: int
      
      EFFECT		: computation of 1-bits in an unsigned int.

      AUTHOR		: Torsten Sillke (1994)
      
      ----------------------------------------------------------------------
      Algorithm:
        - Edward M. Reingold, Jurg Nievergelt, and Narsingh Deo,
	  "Combinatorial algorithms - theory and practice"
	  Prentice-Hall, Englewood Cliffs, 1977.
	  (ISBN 0-13-152447-X)
          pages 2-6

        - Jon Bentley,
          "Programming Pearls", 1st ed., p 173

        - Paeth, Alan W., and Schilling, David, 
	  Of Integers, Fields, and Bit Counting, 
	  p. 371-376, code: p. 610-611,
	  in: Graphics Gems II, James Arvo (editor), 
	      Academic Press, 1991, ISBN: 0120644819.
          http://www.graphicsgems.org/

        - ftp://38.168.214.175/pub/bitcount/BITC.ZIP

      A direct implementation of there algorithm gives:

      int Count (unsigned int w)
      {
        // binary technique for 32 bit words
        w = (0x55555555 & w) + (0x55555555 & (w>> 1));
        w = (0x33333333 & w) + (0x33333333 & (w>> 2));
        w = (0x0f0f0f0f & w) + (0x0f0f0f0f & (w>> 4));
        w = (0x00ff00ff & w) + (0x00ff00ff & (w>> 8));
        w = (0x0000ffff & w) + (0x0000ffff & (w>>16));
        return w;
      }
      
      Now observe that the bit-count is small.  

      The standard method proceeds:
	 |   a   |   b   |   c   |   d   |     at step n
	 |     a + b     |     c + d     |     at step n+1
	 |         a + b + c + d         |     at step n+2

      The modified method proceeds:
	 |   a   |   b   |   c   |   d   |     at step n
	 |   a   |  a+b  |  b+c  |  c+d  |     at step n+1
	 |   a   |  a+b  | a+b+c |a+b+c+d|     at step n+2

      This avoids using this expensive bit masks. 
      If the blocks cannot hold the values any more,
      you must enlarge your blocks.
      At last select the result.
      
      One instruction can be excluded in the first step.
      The resulting algorithm can therefore be improved
      in all stages except the second.

      The performance of the algorithm below for a RISC
      with word-width 2**n bits (for n>=3) is

	LOAD   :   1 + A(n)
	AND    :   2 + A(n)
	ADD,SUB:   n
	SHIFT  :   n
	SELECT :   1

        CountTot(n) = 2*n + 3*A(n) + 5

	(LOAD counts 2 steps all other 1 step)

      The groath of A(n) is like the iterated logarithm.
      Let n(1) = 3 and n(i+1) = 2**(n(i)-1) then define
      A(k) = #{ i | n(i)<=k }. I think you will never need n>=128.

       n  : 3 4 5 6 7 8 9 ... 127 128 ... 2**127-1 2**127
      A(n): 1 2 2 2 2 3 3 ...   3   4 ...        4      5

      Compare this with the parity algorithm:

      unsigned int Parity (unsigned int w)
      {
         // parity of the number of 1-bit
         // 0 if even; 1 if odd
         // implementation for 32 bit words
         w ^= w>>1;
         w ^= w>>2;
         w ^= w>>4;
         w ^= w>>8;
         w ^= w>>16;
         return w & 1;
      }

      The number of steps for this algorithm for word-width 2**n is:

	XOR    :   n
	SHIFT  :   n
	SELECT :   1

        ParityTot(n) = 2*n + 1

      Total number of steps used for small n:

      n            :  3  4  5  6  7  8  9 10 11 12 13 14 15 16
      CountTot(n)  : 14 19 21 23 25 30 32 34 36 38 40 42 44 46
      ParityTot(n) :  7  9 11 13 15 17 19 21 23 25 27 29 31 33
      
      There are other ways to count the number of bits.
      Bob Stout's "Snippets" collection has a whole bucket full of them.
      It has a benchmarking program so that you can easily determine 
      which is fastest for you system. URL http://www.snippets.org/.
      Or see my collection of bitmanipulation functions
      URL http://www.mathematik.uni-bielefeld.de/~sillke/ALGORITHMS/bitmani/

   **********************************************************************/
   
int bitcount2(unsigned long w)
{
  // binary technique for 2**n bit words with n=5.
  const unsigned long mask1h = (~0UL) /  3  << 1;
  const unsigned long mask2l = (~0UL) /  5;
  const unsigned long mask4l = (~0UL) / 17;
  w -= (mask1h & w) >> 1;
  w = (w & mask2l) + ((w>>2) & mask2l);
  w += w >> 4;     //   8 bit fold.
  w &= mask4l;     //  set width=8.
  w += w >> 8;     //  16 bit fold.
  w += w >> 16;    //  32 bit fold.
  // w += w >> 32;    //  64 bit fold.
  return w & 0xff;    // select 8 bits. (4<=n<8)
}

unsigned empty(unsigned long d)
{
    return 0;
}

