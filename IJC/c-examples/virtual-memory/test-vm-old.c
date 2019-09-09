/*
 * test-vm-old.c 
 *
 * pruzkum logickeho adresoveho prostoru 
 * + ochrana pameti
 * + C signaly [nefunguje na novych verzich Linuxu/GCC]
 *
 * testovano na Linuxu, FreeBSD, DOS/DJGPP 
 *
 */

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#define VMPAGESIZE 4096		/* velikost stranky virtualni pameti */

jmp_buf buf;			/* pro setjmp() a longjmp() */

int flag = 0;			/* aby se nevypisovalo zbytecne mnoho informaci */

/*
 * sigsegv() -- obsluha signalu SIGSEGV (poruseni ochrany pameti)
 */
void sigsegv(int sig)
{
    if (flag != SIGSEGV) {
	printf(" SIGSEGV\n");
	flag = SIGSEGV;
    }
#ifdef __linux__
    signal(SIGSEGV, sigsegv);	/* Linux: musime obnovit nastaveni */
#endif
    longjmp(buf, 1);		/* jinak by neprekrocil instrukci */
}

#ifdef __FreeBSD__
/*
 * sigbus() -- obsluha signalu SIGBUS (poruseni ochrany pameti)
 */
void sigbus(int sig)
{
    if (flag != SIGBUS) {
	printf(" SIGBUS\n");
	flag = SIGBUS;
    }
    longjmp(buf, 1);		/* jinak by neprekrocil instrukci */
}
#endif

int main()
{
    char *ptr;			/* ukazatel pro pristup do pameti */
    signal(SIGSEGV, sigsegv);	/* nastaveni obsluhy signalu */
#ifdef __FreeBSD__
    signal(SIGBUS, sigbus);	/* nastaveni obsluhy signalu */
#endif
    ptr = NULL;
    do {
	if (setjmp(buf) == 0) {
	    int x;
	    x = *ptr;		/* pristup do pameti -- CTENI */
	    printf("%8p ", ptr);	/* tiskneme jen pro pristupne adresy */
	    printf("r");	/* muzeme cist */
	    flag = 0;
	    *ptr = x;		/* pristup do pameti -- ZAPIS */
	    printf("w\n");	/* muzeme cist i psat */
	}
	ptr += VMPAGESIZE;
    } while (ptr != NULL);	/* projdeme cely virtualni adresovy prostor */
    printf("\n");
    return 0;
}

