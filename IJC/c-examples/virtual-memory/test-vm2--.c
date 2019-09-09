/*
 * test-vm2.c -- test signalu a prace s virtualni pameti II
 *
 * vyzaduje POSIX signaly, testovano na Linuxu a FreeBSD
 *
 */

#include <stdio.h>		/* printf() */
#include <signal.h>		/* sigaction(), atd. */
#include <setjmp.h>		/* setjmp(), longjmp() */
#include <stdlib.h>		/* malloc(), getenv() */

#define VMPAGESIZE 4096		/* velikost stranky virtualni pameti */

sigjmp_buf buf;			/* pro setjmp() a longjmp() */
struct sigaction act;		/* popis obsluhy signalu */

char *ptr=NULL;			/* ukazatel pro pristup do pameti */

/*
 * sigsegv() -- obsluha signalu SIGSEGV (poruseni ochrany pameti)
 */
void sigsegv(int sig)
{
    siglongjmp(buf, 1);		/* bez longjmp neprekroci instrukci */
}

int main()
{
    int automatic_var = 0;

    /* nastaveni obsluhy signalu SIGSEGV - poruseni ochrany pameti */
    act.sa_handler = &sigsegv;	/* nastavime signal handler */
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);  /* neblokuje zadne signaly */
    if (sigaction(SIGSEGV, &act, NULL) < 0) {	/* nastaveni obsluhy */
	fprintf(stderr, "sigaction failed\n");
	return 1;
    }
    if (sigaction(SIGBUS, &act, NULL) < 0) {	/* nastaveni obsluhy (FreeBSD) */
	fprintf(stderr, "sigaction failed\n");
	return 1;
    }

#if 1
    /* tisk pozic ruznych objektu v pameti */
    printf("code: %p\n", &main);
    printf("constant data: %p\n", "");
    printf("initialized var: %p\n", &ptr);
    printf("uninitialized var: %p\n", &buf);
    printf("small dynamic data: %p\n", malloc(10));
    printf("standard library stub: %p\n", &printf);
    printf("standard library table: %p\n", *(void**)(((char*)&printf)+2));
    printf("standard library: %p\n", *(void**)((char*)(*(void**)(((char*)&printf)+2))+0));
    printf("big dynamic data: %p\n", malloc(1024*1024L));
    printf("stack: %p\n",&automatic_var);
    printf("environment: %p\n", getenv("PATH"));
    printf("\n");
#endif

    ptr = NULL;
    do {
	if (sigsetjmp(buf,1) == 0) {
	    int x;
	    x = *ptr;		/* pristup do pameti -- CTENI */
	    printf("\n%p ", ptr);	/* tisk jen pro pristupne adresy */
	    printf("r");	/* muzeme cist */
	    *ptr = x;		/* pristup do pameti -- ZAPIS */
	    printf("w");	/* muzeme cist i psat */
	}
	ptr += VMPAGESIZE;
    } while (ptr != NULL);	/* projdeme cely virtualni adresovy prostor */
    printf("\n");

    return 0;
}
