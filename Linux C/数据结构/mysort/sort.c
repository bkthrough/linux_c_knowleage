#include <stdio.h>
#include "tools.h"
#include <time.h>

#define SIZE     (1000000)
#define MOD_SIZE (100000000)


void select_sort(int *a,int length);
void init_array(int *a,int length);
void merge_sort(int *a,int length);
static void Merge_sort(int *a,int left,int right,int *temp);
static void merge_array(int *a,int left,int mid,int right,int *temp);

////////////////////////////////////////////////////////////////////
//接口实现
void count(int *a,int length)
{
    
}
static void merge_array(int *a,int left,int mid,int right,int *temp)
{
    int i = left;
    int j = mid+1;
    int m = mid;
    int n = right;
    int k = 0;

    while(i <= m && j <= n){
        if(a[i] > a[j]){
            temp[k++] = a[j++];
        }
        else{
            temp[k++] = a[i++];
        }
    }
    while(i <= m){
        temp[k++] = a[i++];
    }
    while(j <= n){
        temp[k++] = a[j++];
    }
    for(i = 0;i < k; ++i){
        a[left+i] = temp[i];
    }
    //while(i <= mid && j <= right){
    //    if(a[i] < a[j])
    //        temp[k++] = a[i++];
    //    else
    //        temp[k++] = a[j++];
    //}
    //while(i <= mid)
    //    temp[k++] = a[i++];
    //while(j <= right)
    //    temp[k++] = a[j++];
    //for(i = 0; i < k; i++)
    //    a[left+i] = temp[i];
}
void merge_sort(int *a,int length)
{
    int *temp = NULL;

    if(NULL == a|| length < 2){
        return ;
    }
    //temp用来接收数组，一会用作中转
    temp = (int *)malloc(sizeof(int) * length);
    Merge_sort(a,0,length-1,temp);
}
static void Merge_sort(int *a,int left,int right,int *temp)
{
    int mid = 0;

    if(left < right){
        mid = left + ((right-left) >> 1);
        Merge_sort(a,left,mid,temp);
        Merge_sort(a,mid+1,right,temp);
        //合并有序数组
        merge_array(a,left,mid,right,temp);
    }
}
//选择排序：先找到0到length-1中最小的值，然后把它和a[0]交换，然后把它和
//从1到length-1找最小的值，和a[1]交换，如此循环。
void select_sort(int *a,int length)
{
    int i = 0;
    int j = 0;
    int min_index = 0;

    for(i = 0; i < length-1; ++i){
        min_index = i;
        for(j = i+1; j < length; ++j){
            if(a[j] < a[min_index]){
                min_index = j;
            }
        }
        if(i != min_index)
            swap(&a[i],&a[min_index],sizeof(int));
    }
}
void init_array(int *a,int size)
{
    int i;
    if(a != NULL && size > 0){
        for(i = 0; i < size; ++i){
            a[i] = rand() % MOD_SIZE;
        }
    }
}
int main(int argc,char *argv[])
{
    int *a = (int *)Malloc(sizeof(int) * SIZE);
    int i = 0;
    clock_t start;
    clock_t end;
    double result;

    init_array(a,SIZE);
    //for(i = 0;i < SIZE; ++i){
    //    printf("%d ",a[i]);
    //}
    //printf("\n");
    //select_sort(a,SIZE);
    start = clock();

    merge_sort(a,SIZE);

    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    printf("use time %lf\n",result);
    //for(i = 0;i < SIZE; ++i){
    //    printf("%d ",a[i]);
    //}
    //printf("\n");
    return 0;
}
