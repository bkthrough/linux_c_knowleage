#include "stack.h"

Stack init_stack(void)
{
    Stack stack = (Stack)Malloc(sizeof(struct Stack));
    bzero(stack,sizeof(Stack));
    return stack;
}

void push_stack(Stack stack,int value)
{
    S_node *node = (S_node *)Malloc(sizeof(S_node));
    S_node *p = stack->next;
    node->ele = value;
    node->next = NULL;
    if(p == NULL){
        stack->next = node;
    }
    else{
        while(p->next){
            p = p->next;
        }
        p->next = node;
    }
}
Boolean pop_stack(Stack stack)
{
    if(stack == NULL){
        return FALSE;
    }
    S_node *node = stack->next;
    S_node *tmp = NULL;
    if(node->next == NULL){
        free(node);
        stack->next = NULL;
        return TRUE;
    }
    while(node->next->next){
        node = node->next;
    }
    tmp = node->next;
    node->next = NULL;
    free(tmp);
    return TRUE;
}
Boolean get_top(Stack stack,int **value)
{
    if(stack == NULL){
        return FALSE;
    }
    S_node *node = stack->next;
    while(node->next){
        node = node->next;
    }
    *value = &(node->ele);
    return TRUE;
}
void destroy_node(S_node *node)
{
    if(node == NULL){
        return ;
    }
    if(node->next){
        destroy_node(node->next);
    }
    free(node);
}
void destroy(Stack *stack)
{
    if(stack == NULL || *stack == NULL){
        return ;
    }
    S_node *node = (*stack)->next;
    destroy_node(node);
    free(*stack);
    *stack = NULL;
}
