#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1

void my_bzero(void *src, size_t n);


void my_bzero(void *src, size_t n)
{
    memset(src, 0, n);
}

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    int c = 30; 
    int d = 40;

    int array[10] = {12, 23, 34};   //不完全赋值
    char str[20] = {0};
    int *p = &a; //定义一个指针，该指针记录下了int a的地址
    memset(str, 0, sizeof(str));
    bzero(str, sizeof(str));
    // 0 - 9,数组下标不要越界,预防差1和多1错误。
    array[5] = 10;  
    //array = p; //数组名是一个常量，记录下数组首元素的地址,且不可以被修改
    p = array;
    //是否相同?
    p[1] = 15;   // p[1] == *(p + 1) 
    array[1] = 14;
    p + 1;  //
//    int **q = &array;   //   int **
    int (*q)[10] = &array;

    *((int *)(q + 1) - 1) = 20;

    printf("array[9]:%d\n", array[9]);

    // int array[5];
    //int[5]  array;
    //
    //     int[5] *q = &array;
    //
    //     int (*q)[5] = &array;
    //
    //     12 23 34 45 56 234234
    //
    //     q + 1;

    p = array;  // int * = int *
   

    q + 1;

    return 0;
}

#endif
