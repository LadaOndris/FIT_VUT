
/* 
 * crack input code generator
 *
 * TODO add exec
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long prog_bufaddr; /* buffer address from program */
#define PROG_BP      (prog_bufaddr+0x28) /* base pointer from program */
#define PROG_BP2     0xbffff8b8u   /* base pointer2 */
#define CORRECT_INPUT "1234"

// 0xbffff8a0:     0x00000000      0x00000000      0x00000000      0x00000000
// 0xbffff8b0:     0x00000000      0x4015d110      0xbffff8d8      0x0804849b
// 0xbffff8c0:     0x4015d110      0x40053943      0xbffff8d8      0x08048462

char code[] = {
 0xB8, 0x04, 0x00, 0x00, 0x00, /* mov  eax,4    ; cislo sluzby (write)  */
 0xBB, 0x01, 0x00, 0x00, 0x00, /* mov  ebx,1    ; parametr - file descriptor (stdout)  */
 0xB9, 0xFF, 0xFF, 0xFF, 0xFF, /* mov  ecx,msg  ; parametr - data pro zapis  */
 0xBA, 0x00, 0x00, 0x00, 0x00, /* mov  edx,len  ; parametr - delka dat  */
 0xCD, 0x80,                   /* int  0x80     ; volani sluzby specialni instrukci  */
 0xB8, 0x01, 0x00, 0x00, 0x00, /* mov  eax,1    ; cislo sluzby (exit)  */
 0x31, 0xDB,                   /* xor  ebx, ebx ; exit-code 0  */
 0xCD, 0x80,                   /* int  0x80     ; volani sluzby specialni instrukci  */
 '\n', /* konec vstupniho radku */
};


#define ADDR_SIZE       4
#define RETADDR_ADDR    (PROG_BP+ADDR_SIZE)

#define OLD_BP_OFFSET   (PROG_BP-prog_bufaddr)
#define RETADDR_OFFSET  (OLD_BP_OFFSET + ADDR_SIZE)
#define CODE_OFFSET     (RETADDR_OFFSET + ADDR_SIZE)

#define SZ              (CODE_OFFSET + sizeof(code))


int main(int argc, char *argv[])
{
    char *mybuf = malloc(SZ);
    if (mybuf == NULL)
	return 1;
    if(argc!=2)
        return 2;
    prog_bufaddr = strtoul(argv[1],NULL,0);

    /* vynulovat */
    memset(mybuf, 0, SZ);

    /* write correct input data */
    strncpy(mybuf, CORRECT_INPUT, SZ);
    /* patch old base pointer */
    *(unsigned *) (mybuf + OLD_BP_OFFSET) = PROG_BP2;
    /* patch return address */
    *(unsigned *) (mybuf + RETADDR_OFFSET) = RETADDR_ADDR + ADDR_SIZE;
    /* write crack code */
    memcpy(mybuf + CODE_OFFSET, code, sizeof(code));

    /**/ 
    *(unsigned *) (mybuf + CODE_OFFSET + 11) = prog_bufaddr;
    *(unsigned *) (mybuf + CODE_OFFSET + 16) = strlen(CORRECT_INPUT);
#if 0
    printf("%d %d\n", ((char*)memchr(mybuf,'\n',SZ)-mybuf), SZ-1);
#endif
    /* check data + code */
    if(((char*)memchr(mybuf,'\n',SZ)-mybuf)!=SZ-1)
        return 2;

    fwrite(mybuf, SZ, 1, stdout);

    return 0;
}
