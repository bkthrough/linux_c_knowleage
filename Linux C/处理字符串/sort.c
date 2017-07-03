#include <stdio.h>
//泛型编程,交换节点
typedef int (*func)(void *,int);
void swap(void *x,void *y,size_t size);
int compare_int(void *x,void *y);
int compare_char(void *x,void *y);
int compare_float(void *x,void *y);
int compare_double(void *x,void *y);
int compare_long(void *x,void *y);
void sort(void *a,int size,int length,func callback);
//比较两个指针的大小，相等返回0,大于返回大于0的整数，小于返回小于0的整数
int compare_int(void *x,void *y)
{
    if((int *)x == (int *)y)
        return 0;
    else if((int *)x > (int *)y)
        return 1;
    else
        return -1;
}
int compare_char(void *x,void *y)
{
    if((char *)x == (char *)y)
        return 0;
    else if((char *)x > (char *)y)
        return 1;
    else
        return -1;
}
int compare_float(void *x,void *y)
{
    if((float *)x == (float *)y)
        return 0;
    else if((float *)x > (float *)y)
        return 1;
    else
        return -1;
}
int compare_double(void *x,void *y)
{
    if((double *)x == (double *)y)
        return 0;
    else if((double *)x > (double *)y)
        return 1;
    else
        return -1;
}
int compare_long(void *x,void *y)
{
    if((long *)x == (long *)y)
        return 0;
    else if((long *)x > (long *)y)
        return 1;
    else
        return -1;
}
//交换参数
void swap(void *x,void *y,size_t size)
{
    unsigned char *p =(unsigned char *)x;
    unsigned char *q =(unsigned char *)y;
    unsigned char tmp;
    while(size--){
        tmp = *p;
        *p = *q;
        *q = tmp;
        p++;
        q++;
    }
}
//func参数是指向比较函数
void sort(void *a,int size,int length,func callback)
{
    int i;
    for(i = 0;i < length-1;++i){
        if(callback(a+i*size,a+(i+1)*size) > 0)
            swap(a+i*size,a+(i+1)*size,size);
    }
}
int main(int argc,char *argv[])
{
    float a[3] = {3.3,1.2,2.1};
    int i;
    sort(a,sizeof(a[0]),sizeof(a)/sizeof(a[0]),compare_float);
    for(i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
        printf("%f ",a[i]);
    return 0;
}
