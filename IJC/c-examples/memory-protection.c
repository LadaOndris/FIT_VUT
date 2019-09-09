/*
 *
 * test ochrany pameti
 *
 */

#include <stdio.h>

int main() {
    int *ptr; 

    ptr=NULL;   /* zkuste vynechat ;-) */

    *ptr  = 5;  /* zde bude problem ;-) */
    
    printf("konec testu.\n");
    return 0;
}

