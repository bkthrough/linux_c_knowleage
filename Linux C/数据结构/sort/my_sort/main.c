#include <stdio.h>
#include "sort.h"

#define SIZE        (10000)
#define MOD_SIZE    (1000000)
void init_array(int *a,int size);
void init_array(int *a,int size)
{
    int i = 0;
    for(i = 0; i < size; ++i){
        a[i] = rand() % MOD_SIZE;
    }
}
int main(int argc,char *argv[])
{
    clock_t start;
    clock_t end;
    double result;
    int i;
    int *a = (int *)Malloc(sizeof(int) * SIZE);

    init_array(a,SIZE);
    //for(i = 0; i < SIZE; ++i){
    //    printf("%d ",a[i]);
    //}
    printf("\n");
    start = clock();

    insert_sort(a,SIZE);
    //bubble_sort(a,SIZE);
    //select_sort(a,SIZE);
    //merge_sort(a,SIZE);
    //count_sort(a,SIZE,MOD_SIZE);
    quick_sort1(a,0,SIZE-1);
    //count_sort1(a,SIZE,0,MOD_SIZE-1);
    //base_sort1(a,SIZE);
    //shell_sort(a,SIZE);

    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf\n",result);

    start = clock();

    select_sort(a,SIZE);

    end = clock();
    result = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf\n",result);
    //for(i = 0; i < SIZE; ++i){
    //    printf("%d ",a[i]);
    //}
    printf("\n");
    free(a);
    return 0;
}
