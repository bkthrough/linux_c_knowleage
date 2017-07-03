#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_t *tid;
typedef struct Array
{
    int    *a;
    int  left;
    int right;
}Array;
//把数组分成n块用快排
void q_sort(int *array,int left,int right)
{
    int i = left;
    int j = right - 1;
    int pivot = array[i];

    if(i > j){
        return ;
    }
    while(i < j){
        while(pivot < array[j] && i < j){
            j--;
        }
        if(i < j){
            array[i] = array[j];
            i++;
        }
        while(pivot > array[i] && i < j){
            i++;
        }
        if(i < j){
            array[j] = array[i];
            j--;
        }
    }
    array[i] = pivot;

    q_sort(array,left,i);
    q_sort(array,i+1,right);
}
int cpu_num(void)
{
    char cmd[100] = "cat /proc/cpuinfo | grep processor | awk -F \" \" '{print $3}'";
    FILE *fp = NULL;
    char str[3] = {0};
    int size = 0;

    fp = popen(cmd,"r");
    while(fread(str,1,3,fp)){
        size = atoi(str) > size ? atoi(str) : size;
    }

    return size+1;
}
//处理快排线程的参数
void *qsort_thread(void *pos)
{
    Array array;

    memcpy((void *)&array,pos,sizeof(Array));
    q_sort(array.a,array.left,array.right);

    pthread_exit(NULL);

    return NULL;
}

//把n块归并
void merge(int *a,int left,int mid,int right)
{
    int *tmp = NULL;
    int i = left;
    int j = mid+1;
    int k = 0;

    if(a == NULL){
        return ;
    }
    tmp = (int *)malloc((right-left+1) * sizeof(int));
    while(i <= mid && j <= right){
        if(a[i] < a[j]){
            tmp[k++] = a[i++];
        }else{
            tmp[k++] = a[j++];
        }
    }
    while(i <= mid){
        tmp[k++] = a[i++];
    }
    while(j <= right){
        tmp[k++] = a[j++];
    }

    for(i = left; i < right; ++i){
        a[i] = tmp[i-left];
    }
}

void *merge_thread(void *pos)
{
    Array *array;
    int mid = 0;

    array = (Array *)malloc(sizeof(Array));
    memcpy(array,(Array *)pos,sizeof(Array));
    mid = array->left + (array->right - array->left) / 2;
    merge(array->a,array->left,mid,array->right);

    pthread_exit(NULL);
    return NULL;
}

int deal_thread_num(int num)
{
    unsigned int bit = 1;
    int count = 32;

    bit <<= 31;
    while(0 == (num & bit)){
        bit >>= 1;
        if(bit == 1){
            return -1;
        }
    }
    bit >>= 1;
    if(num & bit){
        return bit * 4;
    }else{
        return bit * 2;
    }
}
void *thread(void *num)
{
    printf("ok\n");
}
#if 1
int main(int argc,char *argv[])
{
    int measure = 0;
    int c_num = 0;
    int thread_num = 0;
    int i = 0;
    int *a = NULL;
    int num = 0;
    Array *array;
    int unit = 0;

    //申请数组并且赋值
    printf("input array num!\n");
    scanf("%d",&num);
    a = (int *)malloc(num * 4);
    bzero(a,num * 4);
    for(i = 0; i < num; ++i){
        a[i] = rand() % num;
    }
    q_sort(a,0,num);
    c_num = cpu_num();
    //很精妙的一句，判断c_num是否是2^n
    thread_num = c_num * 2;
    if(0 != (thread_num & (thread_num-1))){
        thread_num = deal_thread_num(thread_num);
    }
    tid = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);
    unit = num / thread_num;
    array = (Array *)malloc(sizeof(Array) * thread_num);
    //快排的线程
    for(i = 0; i < thread_num; ++i){
        array[i].a = a;
        array[i].left = i * unit;
        //很精妙的一句，最后一个会加上余数
        array[i].right = array[i].left + unit + (i / (thread_num-1)) * (num % unit);
        pthread_create(&tid[i],NULL,qsort_thread,(void *)&array[i]);
    }
    for(i = 0; i < thread_num; ++i){
        pthread_join(tid[i],NULL);
    }
    //归并的线程
    int gap = 2;
    while(gap <= thread_num){
        for(i = 0; i < thread_num; i += gap){
            array[i].a = a;
            array[i].left = unit * i;
            array[i].right = array[i].left + (unit * gap);
            if(i + gap >= thread_num){
                array[i].right += num % unit;
            }
            pthread_create(&tid[i],NULL,merge_thread,&array[i]);
        }
        for(i = 0; i < thread_num; i += gap){
            pthread_join(tid[i],NULL);
        }
        gap *= 2;
    }

    measure = rand()%num - 10;
    for(i = measure; i < measure + 10; ++i){
        printf("%d ",a[i]);
    }
    printf("\n");
    return 0;
}
#endif
