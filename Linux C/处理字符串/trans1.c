#include <stdio.h>
//这个方法好,从后向前遍历,不过要先统计一下空格数量
void transform_blank(char *str,int length);
void transform_blank(char *str,int length)
{
    int i;
    int j;
    int k = 0 ;
    int m = 0;
//统计空格个数
    for(i = 0;str[i];i++);
    for(j = 0;str[j]; j++){
        if(str[j] == ' ')
            k++;
    }
//如果遇到空格+2，那么赋值0;+1,赋值2;0,赋值%
        m = i+k*2;
    for(j = i;j > 0;j--){
        if(str[j] == ' '){
            str[m] = '0';
            str[m-1] = '2';
            str[m-2] = '%';
            m -= 3;
        }
        else
            str[m--] = str[j];
    }
}
int main(int argc,char *argv[])
{
    char str[100] = "he l lo";
    transform_blank(str,100);
    printf("%s",str);
    return 0;
}
