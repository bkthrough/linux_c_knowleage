#include <stdio.h>
//计算int型变量的二进制的1的个数以及二进制的表示形式
//比如3
//输出2 个 1
//00000000 00000000 00000000 00000011
int A[32]={0};
int count_bit(int x);
int count_bit(int x)
{
    int count = 0;
    int i;
    //如果x与1相与等于1说明最后一位是1
    if((x&1) == 1){
        count++;
        A[0] = 1;
    }
    //把x循环右移，如果x与1相与等于1,那么就说明移动后的最后一位等于1
    for(i = 1;i < 32;i++){
        x >>= 1;
        if(x&1){
            count++;
            A[i] = 1;
        }
    }
    return count;
}
int main(int argc,char *argv[])
{
    int i;
    printf("%d\n",count_bit(100));
    for(i = 31;i >= 0;i--)
        printf("%d",A[i]);
    return 0;
}
