/*
 * test of errorneous expression  i = i++
 * try with/without optimization
 * try various platforms
 *
 * use  gcc -Wall -std=c99 -pedantic
 *
 * From C-FAQ:
 *
 * 3.3: I've experimented with the code
 *
 *       int i = 3;
 *       i = i++;
 *
 *   on several compilers.  Some gave i the value 3, and some gave 4.
 *   Which compiler is correct?
 *
 *   A:      There is no correct answer; the expression is undefined.  See
 *   questions 3.1, 3.8, 3.9, and 11.33.  (Also, note that neither
 *   i++ nor ++i is the same as i+1.  If you want to increment i,
 *   use i=i+1, i+=1, i++, or ++i, not some combination.  See also
 *   question 3.12.)
 * 
 */


#include <stdio.h>

#define SIZE 5    /* should be odd */

#define TEST(expr) { printf(#expr "\n"); expr; }

int main()
{

    int i = 3;
    int index1, index2;
    int pole[SIZE] = { 0 };

    printf("i = %d\n", i);
    TEST(i = i++);  /* warning */
    printf("i = %d\n", i);

    for (index1 = 0, index2 = SIZE - 1; index1 < SIZE; index1++, index2--)
	TEST(pole[index1] = pole[index2]++); /* no warning !!! */

    printf("\n");
    for (index1 = 0; index1 < SIZE; index1++)
	printf("pole[%d] = %d \n", index1, pole[index1]);
    printf("\n");

    return 0;
}
