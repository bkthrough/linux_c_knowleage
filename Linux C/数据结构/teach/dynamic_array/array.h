#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "tools.h"
#include <stdio.h>

#define TRUE  (1)
#define FALSE (0)
#define MODE  (32)

typedef unsigned char Boolean;
typedef struct Array *Array;
struct Array{
    void **data;
    int capacity;//容量
    int count;//数组元素个数

    void (*free)(void *ptr);
    Boolean (*match)(void *value1,void *value2);
    Boolean (*push_front)(Array array,void *value);
    Boolean (*pop_front)(Array array);
    Boolean (*push_back)(Array array,void *value);
    Boolean (*pop_back)(Array array);
};
////////////////////////////////////////////////////
//接口
Array init(int init_size);
void destroy(Array *array);
int find_index(Array array,void *value);
void *find_ele(Array array,int index);
Boolean delete_index(Array array,int index);
Boolean delete_range(Array array,int begin,int end);
Boolean insert_prev(Array array,int index,void *value);

#endif
