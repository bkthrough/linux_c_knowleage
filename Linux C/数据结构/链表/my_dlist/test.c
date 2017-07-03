#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
    int *p = malloc(3);
    int a = 4;
    printf("%p",(int *)(unsigned long)(a));
    return 0;
}
