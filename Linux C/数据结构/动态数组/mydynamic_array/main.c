#include "array.h"
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
    int *x = NULL;
    int b;
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    int length = sizeof(a)/sizeof(a[0]);
    Array *array = init_array(size);
    for(i = 0 ; i < length ; ++i){
        array->push_back_array(array,&a[i]);
    }
    b = find_value(array,&a[3]);
    printf("find a[3] %d\n",b);
    //x = get_array_index(array,3);
    //printf("array->data[index] == %d\n",*x);
    delete_index_value(array,3);
    x = array->data[3];
    printf("%d\n",*x);
    array_prev_insert(array,3,&a[3]);
    //printf("%d\n",array->count);
    for(i = 0; i < array->count; ++i){
        x = get_array_index(array,i);
        printf("%d ",*x);
    }
    printf("\n");
    destroy_array(&array);
    return 0;
}
