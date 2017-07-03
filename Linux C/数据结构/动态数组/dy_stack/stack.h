#ifndef _STACK_H_
#define _STACK_H_

#include "tools.h"
#include <stdio.h>

typedef struct Stack
{
    void *stack_ctr;
}*Stack;

/////////////////////////////////////////////////
//接口
Stack init_stack(int init_size);
void destroy_stack(Stack *stack);
void push_stack(Stack stack,void *value);
Boolean pop_stack(Stack stack);
Boolean get_top(Stack stack,void **value);
Boolean is_empty_stack(Stack stack);
int get_stack_count(Stack stack);

#endif
