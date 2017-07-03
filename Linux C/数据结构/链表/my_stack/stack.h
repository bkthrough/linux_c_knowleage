#ifndef _STACK_H_
#define _STACK_H_
#include "mydlist.h"
#include "tools.h"

typedef struct stack{
    Dlist stack_ctr;
}*Stack;

/////////////////////////////////
//接口
void destroy_stack(Stack *stack);
void push_stack(Stack stack,void *value);
Boolean pop_stack(Stack stack);
Stack init_stack(void);
Boolean get_top(Stack stack,void **value);
Boolean stack_is_empty(Stack stack);
int get_stack_count(Stack stack);

#endif
