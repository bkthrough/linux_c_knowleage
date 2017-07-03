#include "dynamic_array.h"
#include "tools.h"

static Boolean array_push_front(Array *array, void *value);
static Boolean array_push_back(Array *array, void *value);
static Boolean array_pop_front(Array *array);
static Boolean array_pop_back(Array *array);

static void *array_iter_head(Iterator *iter, Array *array);
static void *array_iter_tail(Iterator *iter, Array *array);
static void *array_iter_next(Iterator *iter, Array *array);
static void *array_iter_prev(Iterator *iter, Array *array);

static void array_grow(Array *array, int size);

//头插、尾插、头删、尾删
static Boolean array_push_front(Array *array, void *value)
{

}

static Boolean array_push_back(Array *array, void *value)
{

}

static Boolean array_pop_front(Array *array)
{

}

static Boolean array_pop_back(Array *array)
{

}

//动态数组迭代器操作
static void *array_iter_head(Iterator *iter, Array *array)
{

}

static void *array_iter_tail(Iterator *iter, Array *array)
{

}

static void *array_iter_next(Iterator *iter, Array *array)
{

}

static void *array_iter_prev(Iterator *iter, Array *array)
{

}

//动态数组增长的操作
static void array_grow(Array *array, int size)
{
    
}

//动态数组操作接口
Array   *init_array(int init_size)    //动态数组的初始化
{
    Array *array = (Array *)Malloc(sizeof(Array));
    
    //对控制信息成员进行初始化
    array->count = 0;
    
    //数组元素拷贝、比较、释放指针初始化为NULL
    array->free = NULL;
    array->match = NULL;
    array->copy = NULL;

    //头插、尾插、头删、尾删
    array->push_front = array_push_front;
    array->push_back = array_push_back;
    array->pop_front = array_pop_front;
    array->pop_back = array_pop_back;

    //迭代器操作
    array->iter_head = array_iter_head;
    array->iter_tail = array_iter_tail;
    array->iter_next = array_iter_next;
    array->iter_prev = array_iter_prev;

    array->data = NULL;
    //对申请元素个数做判断
    if(init_size > 0){
        array_grow(array, init_size); 
    }else{
        array->capacity = 0;
    }

    return array;
}

void    destroy_array(Array **array)    //动态数组的销毁
{

}

void    array_clean(Array *array)    //动态数组清空
{

}

//插入到指定下标的前边
Boolean array_prev_insert(Array *array,
            int index, void *value)
{

}

//插入到指定下标的后边
Boolean array_next_insert(Array *array,
            int index, void *value)
{

}

int     get_array_count(Array *array)    //得到动态数组的个数
{

}

void    *get_array_index(Array *array, int index)    //得到指定下标的元素
{

}

Boolean delete_index_value(Array *array, int index);    //删除指定下标元素
Boolean delete_range_value(Array *array, 
                           int begin, int end)     ;    //删除指定下标范围的元素
int     find_value(Array *array, void *value)      ;   //查找指定元素的下标

