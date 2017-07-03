#include <stdio.h>
#include <stdlib.h>

#if 1

#define SIZE  (10)

int global_value = 10;   //全局区
static int static_value = 20;   //静态区

int *func1(void);

int *func1(void)
{
    //自动变量:
    //
    //函数调用时定义，函数结束时回收。
    int a = 10;
    int array[] = {12, 23, 34, 45, 56};
    int i = 0;   //计数器

    for(i = 0; i < sizeof(array) / sizeof(array[0]); ++i){
        printf("%d  ", array[i]);
    }
   
    a++;
    return array;
}

int main(int argc, char **argv)
{
    int a = 10;   //stack
    int *p_int = (int *)malloc(40);
    // p_int在stack上，malloc申请内存在heap
    if(p_int == NULL){
        fprintf(stderr, "the memeory is full!\n");
        exit(1);
    }
    p_int[0] = 1;

    func1();

    free(p_int);
    return 0;
}


#endif

#if 0

int a;
void func1(void);

void func1(void)
{
    printf("a = %d\n", a);
}

int a = 10;

int main(int argc, char **argv)
{
    int a = 20;
    {
        int a = 10;
        a++;
        printf("%d\n", a);
    }
    printf("a = %d\n", a);
    func1();
    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    int a = 10;
    const int b = 20;   //常变量在内存中是占有空间的，常量没有
    
    int *y = (int *)&b;

    *y = 23;
   

    int const c = 20;

   
    const int *p = &a;   //p所指向的对向的值不可被更改
   // *p = 50;
    a = 50; 
    int const *q = &a;
    int * const m = &a;
   // m  = &b;
    const int * const n = &a;

    //是否常变量不能被修改值？

   // int *x;

   printf("%d\n", b);
   // b++;

    return 0;
}

#endif

#if 0

#define TRUE  (1)
#define FALSE (0)
//类型重定义，例如布尔类型的定义
typedef unsigned char Boolean;   // 0-255  TRUE 1 /  FALSE 0


//**********************************************************

#define P_CHAR char *
typedef int    *p_int;


int main(int argc, char **argv)
{
    int q = 10;
    Boolean ok = TRUE;

    P_CHAR a, b;   // char * a, b ==> char *a, b; 
    p_int  c, d;   
   
   
    return 0;
}

#endif

#if 0
int b = 20;   //定义式

extern void func1(void);   //从其他.c文件中查找是否有func1 

int main(int argc, char **argv)
{
    int a = 10;   //这成为定义：既分配内存，又告诉内存的标记（a）
    int b,c; //wrong

    //定点数初始化为0
    int b = 0;
    int c = 0;
    //浮点数
    float d = 0.0;
    //指针初始化为空指针
    int *p_inter = NULL;
    //数组初始化为0
    char array[20] = {0};
    //struct List_node node = {0};

    //习惯：
    //
    //1.变量定义时必须初始化；
    //2.每一行只做一个操作；
    //3.不允许隐式声明，所有的变量必须是显式声明；
   

    *p_inter = 10;



    func1();   //使用外部函数

    return 0;
}

#endif

#if 0


//对位置进行标记
//
//如果进行部分初始化，未初始化的值从初始化的值向后依次加1，如果第一个
//元素都没有初始化，从0开始。
enum flag {
     INDEX1 = 0,
     INDEX2,
     INDEX3, 
     INDEX4 = 11,
     INDEX5 = 12,
     INDEX6 = 13 
};

int main(int argc, char **argv)
{
    enum flag a;

    //枚举类型的大小是4字节（和int相同）
    printf("the size of enum:%d\n", sizeof(a));
    

    return 0;
}

#endif

#if 0

//  内存布局：
//
//  由高地址到低地址如下排列：
//
//      1.内核空间
//      2.stack
//      3.share lib
//      4.heap
//      5.rw
//      6.ro
//      7.保留区(reserve)   NULL  
//
//      #define NULL ((void *)0)

int main(int argc, char **argv)
{
    //str1为指针（在栈上），指向了常量区的一个字符串，该字符串不能被修改
    //str2和str3为字符数组，在栈上
    char *str1 = "hello, world!";
    char str2[] = "hello, world!";
    char str3[6] = {0};

    //   str1
    //   \0
    //   !
    //   d
    //   l
    //   r
    //   o
    //   w
    //    
    //   ,         5
    //   o         4
    //   l         3
    //   l         2
    //   e         1
    //   h    str2[0]
    //
    //   \0
    //   \0
    //   \0
    //   \0
    //   \0
    //   \0


    //str2[1] = 'l';
    printf("before:%s\n", str2);
    
   // printf("str1:%p\n", str1);
   // printf("str2[0]:%p\n", &str2[0]);
   // printf("str2[1]:%p\n", &str2[1]);
   // printf("str2[2]:%p\n", &str2[2]);
   // printf("str2[3]:%p\n", &str2[3]);
   // printf("str3:%p\n", &str3[0]);

    str3[17] = 'l';
    printf("after:%s\n", str2);



    //第一个不能修改字符串的字符
    //第二三个可以修改
    //str1[1] = 'l';

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    int a = 10;
    int *p = &a;
    int **q = &p;

    // char *   =   int *
    char *m = (char *)&a;

    //void  s;   变量进行定义的时候一定要告诉编译器变量的大小

    void *n;

    //void *  = int *
    n = p;   
    q = (int **)n;

    //char x = 10;
    //int y = 20;
    //char z = 0;

    //x = y;


    //void *可以接受任意类型的指针赋值，它是我们泛型编程的基础

   //1.指针是一个变量，它在内存中也有地址
   //2.指针的功能是记录地址
   //3.指针具有类型限定（指类）

    //指针的大小：
    //
    //32位  4byte  
    //64位  8byte
    //
    //和long类型是同步的

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    //浮点数
    //
    //1.float     4bytes
    //2.double    8bytes
    //
    //
    //double的位表示：  （64）
    // 
    //（1）符号位       1
    //（2）指数位       11
    //（3）尾数位       52
    //
    //
    //2^52 ==  15,16位
    
    
    float a = 12.25;

    //浮点数的位存储形式：
    //
    //12.25 => 1100.01(二进制) = 1.10001 * 2^3 （二进制科学计数法）
    //
    //   3    （指数位）
    //   10001  （尾数）
    //   0    （符号位）
    //
    //  float  4bytes
    //
    //  00000000 00000000 00000000 00000000
    //
    //  规则如下：
    //
    //  IEEE:
    //
    //  （1）左起第一位是符号位，正数为0，负数为1；    1
    //  （2）指数位                                    8
    //  （3）尾数位                                    23
    //
    //
    //   2^23 = 7
    //
    //  00000001 1
    //    111111 1
    //  01000001 01000100 00000000 00000000
    //     
    //    41        44       00       00
    //
    //  01111111 0
    //
    //    0 - 255
    //
    //    -128 - 127 = -1
    //
    //
    //
    //    0x12345678   4byte
    //
    //    大端机器：数值上的高位放在内存上的低位
    //
    //    
    //
    //    小端机器：数值上的高位放在内存上的高位
    //
    //
    //    如何把一个浮点数转化为整数？
    //
    //    int ftoi(float value);
    //
    //
    //    12.25 ---> 12
    //
    //    0.5 ---> 0
    //
    //    -13.5 --->-13


    return 0;
}

#endif

#if 0

int comp_len(const char *str1, const char *str2);

int comp_len(const char *str1, const char *str2)
{
    //return strlen(str1) - strlen(str2) > 0;   //1  0 
    return strlen(str1) > strlen(str2);
           //  7    >   16   
    // size_t - size_t
    //
    // 1 - 2 = -1 = 1111 1111
}

int main(int argc, char **argv)
{
    char *str1 = "asdfasd";
    char *str2 = "adsfadsfasdfasdf";

     comp_len(str1, str2);

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    //定点数和浮点数基本数据类型的大小
    printf("size of char:%d\n", sizeof(char));
    printf("size of short:%d\n", sizeof(short));
    printf("size of int:%d\n", sizeof(int));
    printf("size of long:%d\n", sizeof(long));
    printf("size of long long :%d\n", sizeof(long long int));
    printf("size of float:%d\n", sizeof(float));
    printf("size of double:%d\n", sizeof(double));

    //定点数
    //
    //  有符号数 和 无符号数
    //
    int a = 10;    // 00000000 00000000 00000000 00001010
    int b = -1;    // 10000000 00000000 00000000 00000001 (wrong)

    //    -1 = 0 - 1 = 00000000 00000000 00000000 00000000 - 1
    //              = 100000000 00000000 00000000 00000000 - 1
    //              =  11111111 11111111 11111111 11111111
    //   
    //   对于正数：
    //
    //       原码和补码相等
    //
    //   10 = 0000 1010 
    //
    //   对于负数来说，原码和补码之间的关系：
    //
    //   -1 = 1000 0001   （原码：人对负数的认识，计算机并不承认）
    //
    //   *计算机只识别补码
    //
    //   -x = 0 - x = 0000000 - x (向上借位) 
    //
    //   *负数(原码)除符号位外，其他位按位取反，末位加1
    //
    //   -1 = 1000 0001 = 1111 1110 = 1111 1111
    //
    //    以1字节为例：
    //
    //    1101 0110 + 0010 1001 = 1111 1111
    //
    //    （1）  x + x(反) = 0xFF
    //    （2）  x + x(反)+1 = 0
    //    （3）  0 - x = x(反) + 1
    //
    //    2.无符号数
    //
    //    unsigned char a;   (0 - 255)  (0000000 - 11111111)
    //    char b;            (-128-127)
    //
    //    unsigned char c = 0;
    //    c--;   (00000000 - 1 = 11111111)
    //
    //    size_t == unsigned int
    //
    //    《深入理解计算机系统》


    return 0;
}

#endif
