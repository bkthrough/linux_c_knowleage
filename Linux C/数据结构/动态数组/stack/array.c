#include "array.h"
#include "tools.h"
static void *iter_head(Iterator *iter,Array *array);
static void *iter_tail(Iterator *iter,Array *array);
static void *iter_next(Iterator *iter,Array *array);
static void *iter_prev(Iterator *iter,Array *array);

static Boolean push_front(Array *array,void *value);
static Boolean push_back(Array *array,void *value);
static Boolean pop_front(Array *array);
static Boolean pop_back(Array *array);

static void array_grow(Array *array,size_t size);
static int adjust_array(size_t size);
//迭代器操作
static int adjust_array(size_t size)
{
    size += (MODE-1);
    size /= MODE;
    size *= MODE;
    return size;
}
static void array_grow(Array *array,size_t size)
{
    int adjust = 0;
    if(array->capacity >= size){
        return ;
    }
    adjust = adjust_array(size);
    array->capacity = adjust;
    //元素
    if(array->data == NULL){
        array->data = (void **)Malloc(sizeof(void *)*adjust);
    }
    else{
        array->data = (void **)Realloc(array->data,sizeof(void *)*adjust);
    }
}
static void *iter_head(Iterator *iter,Array *array)
{
    if(iter == NULL || array == NULL){
        return NULL;
    }
    iter->index = 0;
    iter->size = array->count;
    if(array->data == NULL || iter->size == ZERO){
        iter->ptr = NULL;
    }
    else{
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
static void *iter_tail(Iterator *iter,Array *array)
{
    if(iter == NULL || array == NULL){
        return NULL;
    }
    iter->index = array->count-1;
    iter->size = array->count;
    if(array->data == NULL || iter->size == ZERO){
        return NULL;
    }
    else{
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
static void *iter_next(Iterator *iter,Array *array)
{
    if(iter == NULL || array == NULL){
        return NULL;
    }
    iter->index++;
    if(iter->index >= iter->size){
        iter->ptr = NULL;
    }
    else{
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
static void *iter_prev(Iterator *iter,Array *array)
{
    if(iter == NULL || array == NULL){
        return NULL;
    }
    iter->index++;
    if(iter->index < ZERO){
        iter->ptr = NULL;
    }
    else{
        iter->ptr = array->data[iter->index];
    }
    return iter->ptr;
}
//插入删除元素
static Boolean push_front(Array *array,void *value)
{
    return array_prev_insert(array,0,value);
}
static Boolean push_back(Array *array,void *value)
{
    if(array == NULL || value == NULL){
        return FALSE;
    }
    if(array->capacity == array->count){
        return FALSE;
    }
    array->data[array->count] = value;
    array->count++;
    return TRUE;
}
static Boolean pop_back(Array *array)
{
    void *delete = NULL;
    if(array == NULL || array->count == ZERO){
        return FALSE;
    }
    delete = array->data[array->count-1];
    if(array->free){
        array->free(delete);
    }
    array->count--;
    return TRUE;
}
static Boolean pop_front(Array *array)
{
    int i = 0;
    void *delete = NULL;
    if(array == NULL || array->count == ZERO){
        return FALSE;
    }
    delete = array->data[0];
    if(array->free){
        array->free(delete);
    }
    for(i = 0;i < array->count-1; ++i){
        array->data[i] = array->data[i+1];
    }
    array->data[i] = NULL;
    array->count--;
    return TRUE;
}
Array *init_array(int size)
{
    Array *array = (Array *)Malloc(sizeof(Array));
    //控制信息初始化
    array->data = NULL;
    array->capacity = 0;
    if(size > 0){
        array_grow(array,size);
    }
    array->count = 0;
    //数组元素信息的初始化
    array->copy = NULL;
    array->free = NULL;
    array->match = NULL;

    array->push_front_array = push_front;
    array->push_back_array = push_back;
    array->pop_front_array = pop_front;
    array->pop_back_array = pop_back;

    array->iter_head_array = iter_head;
    array->iter_head_array = iter_tail;
    array->iter_next_array = iter_next;
    array->iter_prev_array = iter_prev;
    return array;
}
void destroy_array(Array **array)
{
    if(array == NULL || *array == NULL){
        return ;
    }
    //释放数组元素
    //data
    //array
    if((*array)->free){
        while((*array)->count){
            pop_back(*array);
        }
    }
    free(*array);
    *array = NULL;
}
void array_clean(Array *array)
{
    int i;
    if(array == NULL){
        return ;
    }
    if(array->free){
        while(array->count){
            pop_back(array);
        }
    }
}
Boolean array_prev_insert(Array *array,int index,void *value)
{
    int i;
    if(array == NULL || value == NULL){
        return FALSE;
    }
    if(array->capacity - array->count < ONE){
        array_grow(array,array->capacity+ONE);
    }
    for(i = array->count; i > index; --i){
        array->data[i] = array->data[i-1];
    }
    array->data[index] = value;
    array->count++;
    return TRUE;
}
Boolean array_next_insert(Array *array,int index,void *value)
{
    int i;
    if(array == NULL || value == NULL){
        return FALSE;
    }
    if(array->capacity - array->count < ONE){
        array_grow(array,array->capacity+ONE);
    }
    for(i = array->count ; i > index+1; --i){
        array->data[i] = array->data[i-1];
    }
    array->data[index+1] = value;
    return TRUE;
}
int get_array_count(Array *array)
{
    if(array == NULL)
    {
        return -1;
    }
    return array->count;
}
void *get_array_index(Array *array,int index)
{
    if(array == NULL || index < ZERO){
        return NULL;
    }
    return array->data[index];
}
Boolean delete_index_value(Array *array,int index)
{
    int i;
    void *tmp = NULL;
    if(array == NULL || index < ZERO){
        return FALSE;
    }
    if(index == ZERO){
        pop_front(array);
    }
    else{
        tmp = array->data[index];
        for(i = index; i < array->count-1; ++i){
            array->data[i] = array->data[i+1];
        }
    }
    if(array->free){
        array->free(tmp);
    }
    array->count--;
    return TRUE;
}
Boolean delete_range_value(Array *array,int begin,int end)
{
    if(array == NULL || begin - end > 0){
        return FALSE;
    }
    int i = end-begin;
    do{
        delete_index_value(array,begin++);
    }while(i--);
    return TRUE;
}
int find_value(Array *array,void *value)
{
    int i = array->count;
    if(array == NULL || value == NULL){
        fprintf(stderr,"error");
        exit(1);
    }
    while(i-- && array->data[i] != value);
    return i;
}
