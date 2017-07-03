#include "convert.h"
#include <stdio.h>

Stack convert(Stack stack)
{
    int *value;
    Stack stack2 = init_stack();
    S_node *p = stack->next;
    while(stack->next){
        get_top(stack,&value);
        push_stack(stack2,*value);
        pop_stack(stack);
    }
    return stack2;
}
