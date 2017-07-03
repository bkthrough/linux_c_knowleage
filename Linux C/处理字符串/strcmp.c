#include <stdio.h>
//实现库函数strcmp
int my_strcmp(const char *str1,const char *str2);
int my_strcmp(const char *str1,const char *str2)
{
//从头开始比较两个字符串，直到全部都比较完，或者一个结束，或者字符不相等
    if(*str1 == *str2){
        while(*str1 != '\0'&&*str2 != '\0'){
            str1++;
            str2++;
        }
    }
            //如果str1没有到'\0'，那么返回正数
            //如果str1和str2都结束，那么返回0
            //如果str1结且str2没有结束，那么返回负数
    if(*str1 != '\0')
        return 1;
    else if(*str1 == '\0'&&*str2 == '\0')
        return 0;
    else if(*str1 == '\0'&&*str2 != '\0')
        return -1;
}
int main(int argc,char *argv[])
{
    char *str1 = "hello";
    char *str2 = "hello";
    printf("%d\n",my_strcmp(str1,str2));
    return 0;
}
