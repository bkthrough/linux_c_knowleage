#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE   (1)
#define FALSE  (0)

typedef unsigned char Boolean;
typedef  void (*Sort_Func)(void *, int, int);

/*
 * sort
 * 1.功能：实现对任意类型数组的排序
 *
 * 2.参数说明：
 *    (1)指向数组的第一个元素的指针 (void *)
 *    (2)数组元素数量
 *    (3)每个元素的长度
 *    (4)指向比较的回调函数
 * */
void sort(void *array, int length,
         int element_size, Sort_Func sort_func);

static void sort_int(void *array, int length, int element_size);

static void swap(void *a, void *b, int size);

Boolean int_cmp(int a, int b);

Boolean int_cmp(int a, int b)
{
    return a > b;
}

//  12, 2, 44, 322, 4543, 4, 1, 3, 999, 23

static void swap(void *a, void *b, int size)
{
    void *temp = malloc(size);
    if(temp == NULL){ 
         fprintf(stderr, "the memory is full!\n");
         exit(1);
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
   
    free(temp); 
}

static void sort_int(void *array, int length, int element_size)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < length - 1; ++i){ 
        for(j = i + 1; j < length; ++j){ 
            if(int_cmp( *((int *)array + i), *((int *)array + j))){
                swap((int *)array + i, (int *)array + j, element_size);
            }
        }
    }
}

void sort(void *array, int length,
         int element_size, Sort_Func sort_func)
{
    if(array == NULL || length <= 0
    || element_size <= 0 || sort_func == NULL){
        return ;
    }
    
    sort_func(array, length, element_size);
}

void printf_int_array(int *array, int length);

void printf_int_array(int *array, int length)
{
    int i = 0;

    if(array != NULL && length >= 0){
        for(i = 0; i < length; ++i){ 
            printf("%d ", array[i]);
        }
        printf("\n");
    }
}


int main(int argc, char **argv)
{
    int array[] = {12, 2, 44, 322, 4543, 4, 1, 3, 999, 23};
    int length = sizeof(array) / sizeof(int);
    int int_size = sizeof(int);


    printf("before sort:\n");
    printf_int_array(array, length);
    sort(array, length, int_size, sort_int);
    printf("after sort:\n");
    printf_int_array(array, length);
   

    return 0;
}
