#include <stdio.h>

void func(void)
{
    printf("asd\n");
}

int main()
{
    void (*a)() = func;

    a();
    return 0;
}
