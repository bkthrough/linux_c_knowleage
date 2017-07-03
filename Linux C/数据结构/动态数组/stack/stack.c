#include "array.h"
#include "stack.h"
Stack init_stack(void)
{
    Stack stack;
    stack = (Stack)Malloc(sizeof(struct Stack));
    stack->array = init_array(32);
    return stack;
}
void destroy_stack(Stack *stack)
{
    if(stack == NULL || *stack == NULL)
        return ;
    destroy_array(&((*stack)->array));
    *stack = NULL;
}
Boolean push(Stack stack,void *value)
{
    if(stack == NULL || value == NULL){
        return FALSE;
    }
    stack->array->push_front_array(stack->array,value);
    return TRUE;
}
Boolean pop(Stack stack)
{
    if(stack == NULL)
        return FALSE;
    stack->array->pop_back_array(stack->array);
    return TRUE;
}
Boolean get_top(Stack stack,void **value)
{
    if(stack == NULL || stack == NULL){
        return FALSE;
    }
    *value = get_array_index(stack->array,stack->array->count-1);
}
Boolean get_count(Stack stack,int *value)
{
    if(stack == NULL || value == NULL)
        return FALSE;
    *value = stack->array->count;
    return TRUE;
}
