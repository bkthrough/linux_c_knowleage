#include "hash.h"
#include <stdio.h>

int int_hash_func(const void *key);
void int_print(void *data);
void q_sort(Hash *hash,int left,int right);
void int_print(void *data)
{
    printf("%d ",*(int *)data);
}
int int_hash_func(const void *key)
{
    return *(int *)key;
}
//这个适用于数组，是指针时则需要转换地址上面的值
void q_sort(Hash *hash,int left,int right)
{
    int pivot;
    int i;
    int j;

    if(left > right || hash == NULL){
        return ;
    }
    pivot = hash->table[left]->repeat;
    i = left;
    j = right;
    while(i < j){
        while(pivot < hash->table[j]->repeat && i < j){
            j--;
        }
        if(i < j)
            hash->table[i++]->repeat = hash->table[j]->repeat;
        while(pivot > hash->table[i]->repeat && i < j){
            i++;
        }
        if(i < j)
            hash->table[j--]->repeat = hash->table[i]->repeat;
    }
    hash->table[i]->repeat = pivot;

    q_sort(hash,left,i-1);
    q_sort(hash,j+1,right);
}
void sort(Hash *hash,int left,int right)
{
    int i,j;
    int *tmp;
    for(i = left;i < right-1; ++i){
        for(j = i+1;j < right; ++j){
            if(hash->table[i]->repeat < hash->table[j]->repeat)
            {
                swap(&(hash->table[i]->repeat),&(hash->table[j]->repeat),4);
            }
        }
    }
}
int main(int argc,char *argv[])
{
    Hash *hash;
    int a[10];
    int i;
    hash = init_hash(10,int_hash_func);
    for(i = 0;i < sizeof(a)/sizeof(a[0]); ++i){
        a[i] = rand()%10;
        hash_insert(hash,&a[i]);
    }
    //printf("%d\n",hash->table[3]->repeat);
    sort(hash,0,9);
    //q_sort(hash,0,9);
    printf("top1 == %d\n",hash->table[0]->repeat);
    //printf("top2 == %d\n",hash->table[1]->repeat);
    //printf("top3 == %d\n",hash->table[2]->repeat);
    show_hash_table((const Hash *)hash,int_print);
    destroy_hash(&hash);
    return 0;
}
