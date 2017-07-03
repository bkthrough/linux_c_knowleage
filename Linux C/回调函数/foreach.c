#include <stdio.h>

#if 0

void print_int_array(int *array, int length);
void print_float_array(float *array, int length);




void print_float_array(float *array, int length)
{
 
}

void print_int_array(int *array, int length)
{
    int i = 0;

    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            printf("%d  ", array[i]);
        }
        printf("\n");
    }
}

#endif

#if 1
//定义函数指针类型Print_func

typedef void (*Print_func)(void *, int);

void foreach(void *array, int length, Print_func print);
static void print_int(void *array, int index);

static void print_float(void *array, int index);


static void print_float(void *array, int index)
{
    printf("%f ", *((float *)array + index));
}

static void print_int(void *array, int index)
{
    printf("%d ", *((int *)array + index));
}
//函数指针做参数
void foreach(void *array, int length, Print_func print)
{
    int i = 0;

    for(i = 0; i < length; ++i){
        //打印当前值
        print(array, i);
    }
    printf("\n");
}

#endif

int main(int argc, char **argv)
{
    int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 100};
    float array1[] = {12.4, 1.3, 4.6, 0.54};
    int length = sizeof(array) / sizeof(array[0]);
    int length1 = sizeof(array1) / sizeof(array1[0]);
 
    foreach(array, length, print_int);
    foreach(array1, length1, print_float);
 
    return 0;
}
