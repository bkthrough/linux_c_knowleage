#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#if 1

struct A
{
    char a;    //1
    double b;   //16
    short c;    //18
    union D   
    {
        int a;
        double c;
    } d;       //32
    double e;   //40
    int f;     //48
};

struct B
{
    char a;
    short b;
    int c;
    struct{
        char d;
        double e;
    } g;
    int f;
};


int main(int argc, char **argv)
{
    struct A a;
    
    printf("the size of:%d\n", sizeof(a));    

    return 0;
}

#endif


#if 0

#pragma pack(1)

typedef struct B{
    int a;    // 4
    char b;   // 5
    short c;  // 8
    char d;   // 9
    double e;   //24
    char f;     //32
}B;

typedef struct A{
    int a;    // 4
    char b;   // 5
    char d;   // 6
    short c;  // 8
    double e;   //16
    char f;     //24
}A;

#pragma pack()
/*
 *1.对于结构体的各个成员,第一个成员位于偏移量为 0 的位置,
以后每个数据成员的偏移量必须是 

    MIN(#pragma pack(x), 这个数据成员的自身长度)的倍数。

  2.在数据成员完成各自对齐之后,结构体本身也要进行对齐,对
齐将按照

    MIN(#pragma pack(x), 结构体(共用体)最大数据成员长度)
 *
 * */

int main(int argc, char **argv)
{
    struct A a;
    
    printf("the sizeof of A:%d\n", sizeof(a));

    return 0;
}

#endif

#if 0




typedef struct A{
    char   a;    //1
    short  b;    //2
    int    c;    //4
}A;


// -|------

int main(int argc, char **argv)
{
    A a;
    A *p = NULL;  
 
   // int *p = NULL;

   // p = (int *)malloc(0);

   // printf("the size of a:%d\n", sizeof(*p));
    printf("the size of A :%d\n", sizeof(a));

    p = &a;

    *((char *)p + 1) = 10;

    printf("a.a:%p\n", &a.a);
    printf("a.b:%p\n", &a.b);
    printf("a.c:%p\n", &a.c);


    return 0;
}

#endif

#if 0

//函数指针
typedef void (*Move)(void);

//结构体
struct People{
    //属性
    char name[100];
    short      age;
    char    id[20]; 

//private     私有的：
//protected 受保护的：
//public        公有：

    //操作
    Move move;  //move可以指向型如  void func(void)的函数
 
};

typedef struct A{
    int  a;
    char b;
}A;

typedef struct List_node{
    int               data;   //数据域
    struct List_node *next;   //指针域
    A                    a;
}List_node;
int main(int argc, char **argv)
{
  //  List_node node = {10, NULL};
    List_node node = {
        .data = 10,
        .next = NULL
    };
    List_node node2 = {0};
    List_node *p = &node;
   
    node.data = 20;
    node.next = &node2;
    (*p).data = 30;
    p->data = 40;

    node.a.b = 20;
   // struct People people1; 

   //  people1.age = 10;
    //定点数、浮点数
    //
    //数组：相同类型变量的集合
    //
    //char a[10];
   // char a = 10;
    // char b = 20;
    //
    // 人类：
    // 年龄
    // 性别
    // 身份证号
    //
    // 走路
    // struct

    return 0;
}

#endif
