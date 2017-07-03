#include <stdio.h>

int main(int argc,char *argv[])
{
    int i = 3;
    int *y = &i;
    int **x = &y;
    void **a = x;
    *a = x;
    return 0;
}
