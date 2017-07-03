#include "convert.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
    Stack stack = init_stack();
    Stack queue = NULL;
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    int length = sizeof(a)/sizeof(a[0]);
    int i;
    int *value = NULL;
    for(i = 0; i < length; ++i){
        push_stack(stack,a[i]);
    }
    queue = convert(stack);
    for(i = 0; i < length; ++i){
        get_top(queue,&value);
        printf("%d ",*value);
        pop_stack(queue);
    }
    printf("\n");
    destroy(&stack);
    destroy(&queue);
    return 0;
}
