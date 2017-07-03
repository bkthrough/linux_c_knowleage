#include <stdio.h>

#define MAXSIZE  (100000000)


#if 1

//素数的处理可以采用筛法.

#endif

#if 0

#define LENGTH (256)
#define ZERO   (0)

int main(int argc, char **argv)
{
    //以空间换取时间：
    //
    //     时间的宝贵程度一般是大于空间的
    //
    //     ascii 256 0-127
    //
    //     256种字符，
    //
    //     int ascii_count[256] = {0};
    //
    //     a     97    ascii_count[97]++;   // 0 ---> 1
    //     A     65
    //     0     48
    //     \n    10
    int ascii_count[LENGTH] = {0};  
    // ascii        count
    // 0              0
    // 1              0
    // 2              0
    // 3              0
    // 4              0
    // ...            0
    // 255            0
    char ch = 0;
    int i = 0;   //计数器

    printf("please input the string:\n");
    while((ch = getchar()) != EOF){
        ascii_count[ch]++;
    }

    for(i = 0; i < LENGTH; ++i){
        if(ascii_count[i] != ZERO){
            printf(" the count of [%c] = %d\n", i, ascii_count[i]);
        }
    }

    return 0;
}

#endif

#if 0

//test1:
//
//1.输入任意字符串，统计出其中\n、\t、空格的数量
//
//
//2.输入任意字符串，统计出其中所有字符出现的数量
int main(int argc, char **argv)
{
    char ch = 0;
    int blank_count = 0;
    int enter_count = 0;
    int tab_count   = 0;
  
    printf("please input the string:\n");
    while((ch = getchar()) != EOF){   //如果没有输入EOF，继续输入
        if(ch == '\n'){
            enter_count++;
        }else if(ch == '\t'){
            tab_count++;  
        } else if(ch == ' '){
            blank_count++;
        }     
    }

    printf("the count of blank:%d\n", blank_count);
    printf("the count of tab:%d\n", tab_count);
    printf("the count of enter:%d\n", enter_count);

    return 0;
}


#endif

#if 0

int main(int argc, char **argv)
{
    //素数：
    //
    //除了1和本身之外，不能够被其他数整除的数字
    //eg:
    //
    // 2 3 5 7 11 13 ...
    int i = 0;   //计数器
    int j = 0;

    for(i = 2; i < MAXSIZE; ++i){    //被判断的数的范围
        //从2到i-1开始进行检测，判断i能否被整除，如果不能被整出，则是
        //素数
        for(j = 2; j < sqrt(i); ++j){
            if(i % j == 0){
               break ;
            }
        }
       
        if(i == j){
            printf("the %d is sushu.\n", i);
        }
    }

    return 0;
}

#endif
