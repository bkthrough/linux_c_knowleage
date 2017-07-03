#include "array.h"

static Boolean array_push_front(Array array,void *value);
static Boolean array_push_back(Array array,void *value);
static Boolean array_pop_front(Array array);
static Boolean array_pop_back(Array array);
int adjust_array(int size);
static void array_grow(Array array,int size);
static Boolean array_push_front(Array array,void *value)
{}
static Boolean array_push_back(Array array,void *value)
{}
static Boolean array_pop_front(Array array)
{}
static Boolean array_pop_back(Array array)
{}
int adjust_array(int size)
{
    size += (MODE-1);
    size /= MODE;
    size *= MODE;
    return size;
}
static void array_grow(Array array,int size)
{
    int adjust;
    adjust = adjust_array(size);
    array->capacity = adjust;
    if(array->data){
        array->data = (void **)Realloc(array,size);
    }
    else{
        array->data = (void **)Malloc(size);
    }
}
Array init(int init_size)
{
    Array array;
    array->data = NULL;
    array->capacity = init_size;
    if(init_size > 0){
        array_grow(array,init_size);
    }
    array->count = 0;

    array->free = NULL;
    array->match = NULL;
    array->push_front = array_push_front;
    array->pop_back = array_pop_back;
    array->push_back = array_push_back;
    array->pop_front = array_pop_front;

    return array;
}

