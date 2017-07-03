#include <stdio.h>
//在转义符前加一个脱义符,让其输出是可以忽视脱义符
//比如hello\\nworld输出为
//hello
//world
char *unescape(char *s,const char *t)
{
    if(t == NULL)
        return NULL;
    char *str = s;
    while(*t != '\0'){
        if(*t == '\\'){
            *t++;
            if(*t == 'n'){
                *t++;
                *s++ = '\n';
            }
            else if(*t == 't'){
                *t++;
                *s++ = '\t';
            }
        }
        else
            *s++ = *t++;
    }
    *s = '\0';
    return str;
}
int main(int argc,char *argv[])
{
    char s[100]={0};
    char *t="hello\\n,world\\t\\n!";
    printf("%s\n",t);
    printf("%s\n",unescape(s,t));
    return 0;
}
