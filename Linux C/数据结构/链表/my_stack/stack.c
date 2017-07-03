#include "stack.h"
Stack init_stack(void)
{
    Stack stack = (Stack)Malloc(sizeof(struct stack));
    stack->stack_ctr = init_dlist();
    return stack;
}
void push_stack(Stack stack,void *value)
{
    push_front(stack->stack_ctr,value);
}
Boolean pop_stack(Stack stack)
{
    if(stack == NULL){
        return FALSE;
    }
    if(pop_front(stack->stack_ctr)){
        return TRUE;
    }
}
void destroy_stack(Stack *stack)
{
    if(stack == NULL || *stack == NULL){
        return ;
    }
    destroy_dlist(&(*stack)->stack_ctr);
    free(*stack);
    *stack = NULL;
}
Boolean get_top(Stack stack,void **value)
{
    if(stack == NULL){
        return FALSE;
    }
    if(value != NULL){
        get_front(stack->stack_ctr,value);
        return TRUE;
    }
}
Boolean stack_is_empty(Stack stack)
{
    if(stack->stack_ctr->count == ZERO){
        return TRUE;
    }
    else
        return FALSE;
}
int get_stack_count(Stack stack)
{
    return stack->stack_ctr->count;
}
