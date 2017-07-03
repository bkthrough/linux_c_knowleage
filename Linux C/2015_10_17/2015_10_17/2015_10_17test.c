#include <stdio.h>
#include <string.h>

#if 1

//my_strcpy函数的声明（说明函数的使用方法）
char *my_strcpy(char *dest_str, const char *src_str);
char *my_strncpy(char *dest, const char *src, size_t n);

//my_strcpy函数的定义，函数的具体实现
char *my_strcpy(char *dest_str, const char *src_str)
{
    //建议：
    //
    //一般不建议对传入的指针参数直接进行使用
    char      *dest = dest_str;
    const char *src = src_str ;
   
    //1.首先要对传入的参数进行检测（防御式编程的思想）
    if(dest_str == NULL || src_str == NULL
    || dest_str == src_str){
        return dest_str;
    }

    //2.实现拷贝
   // while(*src != '\0'){
   //     *dest = *src;
   //     src++;
   //     dest++;
   // }
   // *dest = '\0';

    while((*dest++ = *src++) != '\0'){
        /*do nothing*/
    }
    return dest_str;
}

int main(int argc, char **argv)
{
    char *str = "hello, world";
    char str2[100] = {0};
    char *str3 = NULL;

    //把字符串str的内容拷贝到str2中
    //strcpy(str2, str);
    my_strcpy(str2, str);


    printf("%s\n", str2);

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    int i = 0;    //操作符的两边空格隔开

    int a = 10, b = 20;   //不建议

    //每行只出现一个表达式
    int a = 10;
    int b = 20;

    //函数体、分支、循环、switch语句代码需要进行缩进，四个空格，不可为tab

    if(a == b){
        printf("a == b!\n");
        for(i = 0; i < 20; ++i){
            /*do something*/
        }
    }

    return 0;
}

#endif

#if 0

//注释的三种方法：
//
//    1.   //                      （单行注释，从//起始到本行结束都为注释）
//    2.    /* do something  */     (块注释)
//
//    *推荐
//
//    3.   通过条件编译注释
//
//    #if  (1 | 0)                  (1取消注释，0注释)
//
//    #endif
//

int main(int argc, char **argv)
{
    int i = 0;  //计数器

    int/*元素个数*/count;

    //  in/*right*/t a; 
    //
    //  关键字和标识符
    //
    //  关键字：C语言自带的标识符，C语言中一共有多少个关键字？ 32
    //
    //  标识符：用户自定义的。
    //int 9s;

    //1.由数字字母下划线组成，必须以字母下划线开始。
    //  
    //  符合常见的命名规范：
    //
    //（1）
    //
    //windows版本：
    //
    // int ListNode;
    //
    //linux版本：
    //
    // int List_node;
    //
    //（2）
    // 见名识义
    //
    // (3)
    //
    // min && max
    //

    return 0;
}

#endif

#if 0

// *.c     (实现功能的文件) 
//
// 一般情况下，使用者值可以获取到.c文件编译后的动态库和静态库文件
//
// *.h     （功能说明文件）
//
// linux内核
//
// 1.编程规范
//
//
// 字符串中要注意特殊字符的使用，以及他们在计算字符串长度的问题。
// 
// *转义字符\
//
//
int main(int argc, char **argv)
{
    char str[] = "hello,\t\vworld!\a\a\a\a\a\a";

    printf("%s\n", str);

    printf("%d\n", strlen(str));

    return 0;
}	    

#endif

#if 0

//提高程序的局部性

int main(int argc, char **argv)
{
    int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 100}; 
    int i = 0;   //计数器
    int arr_len = sizeof(array) / sizeof(array[0]);

    for(i = 0; i < arr_len; ++i){
        printf("%d  ", array[i]);
    }
    


    return 0;
}

#endif


#if 0

int main(int argc, char **argv)
{
    int flag = 0;   // 4 bytes = 4 * 8 = 32 bits
    // eg:
    //
    //   00000000 00000000 00000000 00010001

    int array_condition[32];

    if(flag == TRUE){
        /*do something*/
    }else{
        /*do something*/
    }

    return 0;
}

#endif
