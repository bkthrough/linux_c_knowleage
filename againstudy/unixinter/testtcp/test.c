#include <stdio.h>

typedef struct test
{
    struct tes{
        int a;
    };
}test;
int main()
{
    int len = sizeof(test);

    printf("%d\n",len);
}
