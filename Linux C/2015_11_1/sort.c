#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int *array, int length);
void sort_array(int *array, int length);

void print_array(int *array, int length)
{
    int i = 0;

    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            printf("%d  ", array[i]);
        }
        printf("\n");
    }
}

static void swap(void *a, void *b, int length)
{
    void *temp = malloc(length);
    if(temp == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    
    memcpy(temp, a, length);
    memcpy(a, b, length);
    memcpy(b, temp, length);
    
    free(temp);
}

void sort_array(int *array, int length)
{
    int i = 0;
    int j = 0;

    if(array != NULL && length > 1){
        for(i = 0; i < length; ++i){
            for(j = i + 1; j < length; ++j){ 
                if(array[j] < array[i]){
                    swap(&array[i], &array[j], sizeof(int));
                    // int a = 10;
                    // int b = 20; 
                    //  
                    // swap(a, b);
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    //1.获取输入，把输入转化为int类型，申请合适的内存存储输入数据
    //
    //2.排序
    //
    //3.显示排序结果
    //
    //4.资源回收
    int *p_int = NULL;    
    int i = 0;

    if(argc < 2){
        fprintf(stderr, "input error!\nthe usage:./sort num1 num2 num3 ...\n");
        exit(1);
    }

    p_int = (int *)malloc(sizeof(int) * (argc - 1));
    if(p_int == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }

    //把命令行参数转换到申请的空间中
    for(i = 0; i < argc - 1; ++i){
        p_int[i] = atoi(argv[i + 1]);
    }

    //打印数组
    printf("before sort:\n");
    print_array(p_int, argc - 1);
    //排序
    sort_array(p_int, argc - 1);
    //打印排序后数组
    printf("after sort:\n");
    print_array(p_int, argc - 1);

    return 0;
}
