#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
int main(int argc,char *argv[])
{
    Stack stack = init_stack();
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    int length = sizeof(a)/sizeof(a[0]);
    int i;
    int *value = NULL;
    for(i = 0; i < length; ++i){
        push_stack(stack,&a[i]);
    }
    for(i = 0; i < length;++i){
        get_top(stack,(void **)&value);
        printf("%d ",*value);
        pop_stack(stack);
    }
    destroy_stack(&stack);
}
