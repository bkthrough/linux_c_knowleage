#include <stdio.h>
#include <stdlib.h>
//实现库函数strcpy的功能
char *my_strcpy(char *dest,const char *src);
char *my_strcpy(char *dest,const char *src)
{
    char *get_dest = dest;
    if(dest == NULL||src == NULL)
        return dest;
    while((*dest++ = *src++) != '\0');
    return get_dest;
}
int main(int argc,char *argv[])
{
    char *src;
    char *str;
    str = malloc(20);
    printf("%s",my_strcpy(str,src));
    return 0;
}
