#ifndef _STACK_H_
#define _STACK_H_
#include "tools.h"
#include <stdio.h>

#define TRUE  (1)
#define FALSE (0)
#define ZERO  (0)
#define ONE   (1)

typedef unsigned char Boolean;
typedef struct Stack{
    int ele;
    struct Stack *next;
}*Stack,S_node;

Stack init_stack(void);
void push_stack(Stack stack,int value);
Boolean pop_stack(Stack stack);
Boolean get_top(Stack stack,int **value);
void destroy(Stack *stack);

#endif
