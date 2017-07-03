#ifndef _STACK_H_
#define _STACK_H_

#include "tools.h"
#include <stdio.h>
typedef struct Stack
{
    Array *array;
}*Stack;

Stack init_stack(void);
void destroy_stack(Stack *stack);
Boolean push(Stack stack,void *value);
Boolean pop(Stack stack);
Boolean get_top(Stack stack,void **value);
Boolean get_count(Stack stack,int *value);

#endif
