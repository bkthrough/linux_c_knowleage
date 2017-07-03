#include "array.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
//void print_int(Array *array);
//void print_int(Array *array)
//{
//    int i;
//    if(array == NULL){
//        return ;
//    }
//    for(i = 0; i < array->count; ++i){
//        printf("%d ",(array->data[i]));
//    }
//    printf("\n");
//}
int main(int argc,char *argv[])
{
    int size = 10;
    int i;
    int *x;
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    int length = sizeof(a)/sizeof(a[0]);
    Stack stack = init_stack();
    for(i = 0 ; i < length ; ++i){
        push(stack,&a[i]);
    }
    get_top(stack,(void **)&x);
    printf("%d\n",*x);
    //x = get_array_index(array,3);
    //printf("array->data[index] == %d\n",*x);
    //printf("%d\n",array->count);
    destroy_stack(&stack);
    return 0;
}
