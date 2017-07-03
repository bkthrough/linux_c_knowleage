#include <stdio.h>
#include <stdlib.h>
//给定一个字符串,并且给定一个判定条件,只要满足条件就截断字符串并输出直到末尾
//如hello(wor,ld)man!        条件 (),!
//输出为hello
//wor
//ld
//man
char *my_strtok(char *str,const char *delim);
char *my_strtok(char *str,const char *delim)
{
    char *str_fan = NULL;
    //用静态变量存储字符串,可以达到截断前面字符串,只剩后面的字符串的效果
    static char *str_jilu;
    int i = 0;
    int j = 0;
    int k = 0;

    if(str != NULL)
        str_jilu = str;
    else if(str == NULL){
        str = str_jilu;
    }
    //静态变量存储str
    if(delim == NULL||*str_jilu == '\0')
	    return NULL;
    //记录delim字符串的个数
    for(i = 0;delim[i];i++);

    str_fan = str_jilu;
    //如果匹配到所给字符，就直接返回
    for(;;){
        //如果结束就直接返回
        if(*str_jilu == '\0'){
            return NULL;
        }
        //如果找到匹配到的字符就退出
        for(k = 0;k < i;k++){
            if(*str_jilu == delim[k])
                break;
        }
        if(*str_jilu == delim[k]){
            *str_jilu = '\0';
            str_jilu++;
            break;
        }
        else{
            str_jilu++;
        }
    }
    return str_fan;
}
int main(int argc,char *argv[])
{
    char str[] = "hello,w(orl)d,1(!)1";
    char *delim = ",()";
    char *p;
    int i;
    printf("%s\n",my_strtok(str,delim));
    while((p = my_strtok(NULL,delim)) != NULL){
        printf("%s\n",p);
    }
    return 0;
}
