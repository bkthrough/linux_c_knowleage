#include <stdio.h>
//二进制实现加法
int bitadd(int a,int b)
{
    int get_a = 0;
    int get_b = 0;
    int jw = a & b;
    int sum = a ^ b;
    while(jw){
        get_a = jw << 1;
        get_b = sum;
        jw = get_a & get_b;
        sum = get_a ^ get_b;
    }
    return sum;
}
int main(int argc,char *argv[])
{
    printf("a + b = %d\n",bitadd(4,3));
    return 0;
}
