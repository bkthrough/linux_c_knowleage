#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int array[100] = {0};   //case1

    int array1[] = {12, 23, 34, 45, 56, 67, 78};    //case2

    int *array3 = NULL;
 
    array3 = (int *)malloc(400);
    array3 = realloc(array3, 1000);

    

   
    free(array3);
    return 0;
}
