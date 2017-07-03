#include <stdio.h>
#include <string.h>
//特大数相加
int get_b[30];
int get_a[30];
int max;
int *data_add(char a[],char b[]);
//如果一个长度比另一个大,那么另一个前面补0,然后从后向前按位相加
int *data_add(char a[],char b[])
{
    int jw = 0;
    int i;
    int count_a = strlen(a);
    int count_b = strlen(b);
    max = count_a > count_b ? count_a : count_b;
    for(i = count_a - 1; i >= 0 ; --i){
        get_a[count_a - 1 - i] = (int)a[i] - '0';
    }
    for(i = count_a; i < max; ++i){
        get_a[i] = 0;
    }
    for(i = count_b - 1; i >= 0; --i){
        get_b[count_b - 1 - i] = (int)b[i] - '0';
    }
    for(i = count_b; i < max; ++i){
        get_b[i] = 0;
    }
    for(i = 0; i < max; ++i){
        if(get_a[i] + get_b[i] + jw >= 10){
            get_a[i] = get_a[i] + get_b[i] + jw - 10;
            jw = 1;
        }
        else{
            get_a[i] = get_a[i] + get_b[i] + jw;
            jw = 0;
        }
    }
    if(jw == 1)
       get_a[i] = 1;
    return get_a;
}
int main(int argc,char *argv[])
{
    char a[] = "1456789";
    char b[] = "387654321";
    int *p;
    int i;
    p = data_add(a,b);
    if(a[max] == 1){
        printf("%d",a[max]);
    }
    for(i = max-1;i >= 0; --i)
        printf("%d",p[i]);
    printf("\n");
    return 0;
}
