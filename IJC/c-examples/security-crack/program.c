
#include <stdio.h>

static int get_input(void) {
    char buf[20];
    printf("%p\n", buf);
    memset(buf,0,sizeof(buf));
    gets(buf);   /* possible buffer overflow */
    return strtol(buf,NULL,0);
}

int main() {
    char pole[10];
    printf("input=%d\n", get_input());
    return 0;
}
