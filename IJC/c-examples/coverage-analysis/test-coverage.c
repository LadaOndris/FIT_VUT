
#include <stdio.h>

void f(void)
{
    int i;
    int sum = 0;

    for (i = 0; 
                i < 10; 
                        i++)
        sum += i;

    if (sum != 45)
        printf("Failure\n");
    else
        printf("Success\n");
}

int main(void)
{
    int i;
    for (i = 0; i < 5; i++)
        f();

    return 0;
}
