/*
 *
 * test zarovnavani polozek struktur
 *
 */

#include <stdio.h>

struct test {
    char c1;
    int i;
    char c2;
};

struct test st;

int main() {

    printf("\nsizeof(st) = %d\n", sizeof(st));
    printf("&st        = %p\n", &st);
    printf("&st.c1     = %p (%d)\n", &st.c1,   (char*)&st.c1  - (char*)&st);
    printf("&st.i      = %p (%d)\n", &st.i,    (char*)&st.i   - (char*)&st);
    printf("&st.c2     = %p (%d)\n", &st.c2,   (char*)&st.c2  - (char*)&st);
    printf("(&st)+1    = %p (%d)\n", &st + 1,  (char*)(&st+1) - (char*)&st);

    return 0;
}

