/*
 *  介绍C语言中的关键字
 * */
#include <stdio.h>
#include <time.h>
#include <string.h>

#if 1

#define TRUE  (1)
#define FALSE (0)

typedef unsigned char Boolean;

Boolean func1(void);
Boolean func2(void);
Boolean func3(void);


Boolean func1(void)
{
    return FALSE;
}

Boolean func2(void)
{
    return FALSE;
}

Boolean func3(void)
{
    return FALSE;
}

int main(int argc, char **argv)
{
    Boolean ok = TRUE;
    int *p_int = NULL;

   
    //内存中申请了资源
    p_int = (int *)malloc(sizeof(int) * 10);
    if(p_int == NULL){
        printf("the memory is full\n");
        exit(1);
    }

    //分别调用函数
    ok = func1();
    if(ok == FALSE){
        free(p_int);
        exit(1);
    }

    ok = func2();
    if(ok == FALSE){
        free(p_int);
        exit(1);
    }

    ok = func3();
    if(ok == FALSE){
        free(p_int);
        exit(1);
    }

    //程序即将结束正常释放
    free(p_int);
    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    //对数组和链表等数据结构的遍历

    for(/*循环初始化*/;/*循环判定条件*/;/*步进长度*/){
        /*循环体*/
    }


    //初始化部分
    while(/*循环判定条件*/){
         /*循环体和步进长度*/
    }

    do{
       /*循环体和步进长度*/
    }while(/*循环判定条件*/);

    return 0;
}

#endif


#if 0

//switch case

int main(int argc, char **argv)
{
    int a = 10;

    switch(a){
        case 12:
            printf("a == 12!\n");
            break ;
        case 35:
            printf("a == 35!\n");
            break ;
        case 67:
            printf("a == 67!\n");
            break ;
        case 100:
            printf("a == 100!\n");
            break ;
        case 200:
            printf("a == 200!\n");
            break ;
        case 230:
            printf("a == 230!\n");
            break ;
        case 300:
            printf("a == 300!\n");
            break ;
        default :
            break ;  
    }   
 
    return 0;
}

#endif

#if 0

#define TRUE  (1)
#define FALSE (0)

typedef unsigned char Boolean;

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    float c = 5.60000001;    //5.600000
    float f = 5.60000002;    //5.600000
    double d = 7.5;
    int *p = &a;    

    if(){

    }else{
    
    }


    //零值的判断
    //
    //整型
    if(a == 0){
        
    }else{
 
    }

    //浮点类型
    if((c - f) >= -0.000001 && (c - f) <= 0.000001){
        printf("c == f!\n");
    }else{
        printf("c != f!\n");
    }

    if(c == f){
        printf("c == f!\n");
    }else{
        printf("c != f!\n");
    }

 
    if(c == 0){  
        printf("c == 0\n");
    }else{
        printf("c != 0\n");
    }

    //指针类型
    if(p){
       
    }else{

    }

    if(p != NULL){
 
    }else{
    
    }

    if(NULL != p){
   
    }else{

    }

 
    //每个语句只能占一行

    //顺序执行的语句
    //1.

    //分支语句
    //if(/*表达式*/){    //注释1
    //   /*do something*/ 
    //}else{    //注释2
    //   /*do something*/ 
    //}

    if(a > 0){
        if(b > 0){
            printf("b > 0!\n");
        }else{
            printf("a <= 0\n");
        }
    }


    return 0;
}

#endif

#if 0


//建议：尽量使用有符号类型
float sum_float_elements(float *arr, int length)
{
    int i = 0;
    float result = 0.0;
    for(i = 0; i <= length - 1; ++i){
        result += arr[i];
    }
    return result;
}
int main(int argc, char **argv)
{
    //unsigned    (0 - 255) 
    //
    //signed      (-128 - 127)
    float array[] = {12.4, 2.5, 0.6, 123.5, 22.3, 50.6};
    float result = 0.0;    

    result = sum_float_elements(array, 0);
    printf("the result is:%f\n", result);
  

    //类型提升问题：一般来讲,signed 遇到 unsigned类型，会提升为unsigned.

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    //char a = 10;

    //printf("%d\n", sizeof(a += 10));
    char str1[] =  "hello,world\0asdfasdfa";
    char *str2 = "hello,world";

    printf("strlen :%d\n", strlen(str1));    //1.
    printf("sizeof:%d\n", sizeof(str1));     //2.
    printf("strlen :%d\n", strlen(str2));    //3.
    printf("sizeof:%d\n", sizeof(str2));     //4.
   

    return 0;
}

#endif

#if 0

void func1(void);

void func1(void)
{

}

int main(int argc, char **argv)
{
    int a = 10;

    printf("the size of int:%d\n", sizeof(int));
    printf("the size of int:%d\n", sizeof(a));
//    printf("the size of int:%d\n", sizeof int);
    printf("the size of int:%d\n", sizeof a);

    func1();

    return 0;
}

#endif

#if 0

//编程实现： int ftoi(float value);   
//
//eg;
//
//  int result = ftoi(-0.5) // result = 0
//
//
//  float分为三部分：
//
//  1.符号位      1
//  2.指数位      8
//  3.尾数位      23

#endif

#if 0

int global_value = 0;
static int static_global_value = 10;


void func1(void);
void func2(void);

//////////////////////////////////////////////
void func3(void);
static void func4(void);


void func3(void)
{

}

static void func4(void)
{

}

void func1(void)
{
    int a = 0;
    a++;
    printf("a = %d\n", a);
}
void func2(void)
{
    static int b = 0;
    b++;
    printf("b = %d\n", b);
}
int main(int argc, char **argv)
{
    int i = 0;   //计数器
   
    for( i = 0; i < 10; ++i){
        func1();
        func2();
    }

    //static静态
    //
    //1.static可以修饰变量：
    //     （1）静态全局变量：
    //           static全局变量和普通全局变量有什么区别？
    //           (1)二者都先于主函数创建；
    //           (2)声明周期贯穿整个程序；
    //           (3)都存在于内存的静态区；
    //           (4)全局变量可以被外部.c文件识别使用，而静态局部变量不可以
    //           ，只能被本文件使用（并且是从它定义的位置向下开始）
    //
    //           链接到底做了设么？ 符号表
    //
    //
    //     （2）静态局部变量：
    //
    //          放在函数内定义
    //2.static可以修饰函数：
    //     (1)没加static函数：可以被其他.c文件识别;
    //     (2)static修饰函数：只能在本文件使用；
    //

    return 0;
}

#endif

#if 0

//register 尽量    把变量放在寄存器里，可以提高程序运行效率。
//
//
// register int array[10000] = {0};
//
//
// register有修饰限制：
//
// 1.自动变量         可以
// 2.静态变量         不可以
// 3.全局变量         不可以
// 4.对于函数参数     可以

//static register int static_value = 10;

//register int global_value = 10;

void func2(register int i);

void func2(register int i)
{
    register int j = 10;
    printf("%d\n", i);
}


#define LENGTH (1000000000)

int main(int argc, char **argv)
{
    register int i = 0;   //计数器
    clock_t start = 0;// long long int
    clock_t end = 0;  
    double use_time = 0.0;

    start = clock();

    for(i = 0; i < LENGTH; ++i){
        /*do something*/
        
    }

    end = clock();

    use_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("use time:%lf\n", use_time);

    return 0;
}

#endif

#if 0

void func1(void);

void func1(void)
{
    auto int a = 10;   //其等价于 int a = 10;
}

int main(int argc, char **argv)
{
    //auto 自动变量
   
    //程序员的自我修养（编译、链接和库） 
    int a = 10;   //由函数内部定义的变量，该变量存在于栈上，该变量的
                  //生存周期函数调用时定义，函数调用结束时被释放。
    func1();


    return 0;
}

#endif
