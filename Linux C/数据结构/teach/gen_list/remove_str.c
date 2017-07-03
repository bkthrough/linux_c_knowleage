#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//先剥离外面的括号，然后内部的括号如果匹配了，那么就输出这个值，并且把这个字符串
//减去拷贝了多少。继续循环执行

void remove_bracket(char *string,char *str);
void remove_str(char *str);
char *my_strcpy(char *dst,const char *src);

char *my_strcpy(char *dst,const char *src)
{
    if(src == NULL || dst == NULL){
        return NULL;
    }

    while(*dst++ = *src++);

    return dst;
}
void remove_bracket(char *string,char *str)
{
    int str_len = strlen(str);
    if(str == NULL){
        return ;
    }

    strncpy(string,str+1,str_len-2);
}
void remove_str(char *str)
{
    int flag = 0;
    int i = 0;
    int count = 0;

    if(str == NULL){
        return ;
    }
    //如果str[i]没到结尾，那么就依序遍历，如果括号匹配了，并且str[i]等于','
    //那么就输出这个值，并且把字符串减去（拷贝了多少+1）
    while(i < strlen(str)){
        if(str[i] == '('){
            flag++;
        }
        else if(str[i] == ')'){
            flag--;
        }
        if(flag == 0 && str[i] == ','){
            while(count < i){
                printf("%c",str[count]);
                count++;
            }
            printf("\n");
            break;
        }
        i++;
    }

    my_strcpy(str,str+i+1);
}
int main(int argc,char *argv[])
{
    char *str = "(a,b,c,d,(1,2))";
    char *string = (char *)malloc(sizeof(char) * strlen(str));

    remove_bracket(string,str);
    printf("%s\n",string);
    remove_str(string);
    remove_str(string);
    remove_str(string);
    remove_str(string);
    remove_str(string);
    remove_str(string);
    remove_str(string);

    return 0;
}
