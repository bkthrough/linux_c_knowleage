#include <stdio.h>
//除法的二进制表示
int division(int x,int y);
int division1(int x,int y);
//除数大于被除数则返回0,get_y小于x的时候，就继续右移。否则计算get_y左移一次
//如果用x减去它小于y则返回1<<移动次数。否则记录下移动次数，继续循环。
int division1(int x,int y)
{
    int get_y = y;
    int count = 0;
    int a = 0;
    if(x < y)
        return 0;
    for(;;){
        while(x > get_y){
            count++;
            get_y = y << count;
        }
        a += 1 << (count-1);
        get_y >>= 1;
        if((x - get_y) < y){
            break;
        }
        else{
            x -= get_y;
        }
    }
    return a;
}
int division(int x,int y)
{
    int get_y = y;
    int count = 0;
    if(x < y)
        return 0;
    while(x > get_y){
        count++;
        get_y = y << count;
    }
    count--;
    if(x - (get_y >> 1) < y)
        return 1 << count;
    else
        return (division(x - (get_y >> 1),y)+(1 << count));
}
int main(int argc,char *argv[])
{
    int x = 80;
    int y = 9;
    printf("x/y = %d\n",division1(x,y));
    return 0;
}
