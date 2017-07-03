#include <stdio.h>
//有转义符时,让字符串输出的时候转义符出现在字符串里
//如hello\nworld
//输出为hello\nworld
char *escape(char *s,const char *t);
char *escape(char *s,const char *t)
{
    if(t == NULL )
        return NULL;
    char *str=s;
    while(*t != '\0'){
        *s = *t;
        switch(*t){
            case'\n':*s++ = '\\';
                     *s = 'n';
                     break;
            case'\t':*s++ = '\\';
                     *s = 't';
                     break;
        }
        *s++;
        *t++;
    }
    return str;
}
int main(int argc,char *argv[])
{
    char *t="hello\nworld\n\t";
    char s[100]={0};
    printf("%s",escape(s,t));
    return 0;
}

