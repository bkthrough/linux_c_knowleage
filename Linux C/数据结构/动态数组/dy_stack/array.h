#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "iterator.h"
#define TRUE  (1)
#define FALSE (0)
#define MODE  (32)
#define ZERO  (0)
#define ONE   (1)

typedef unsigned char Boolean;

typedef struct Array
{
    //1.存储实体
    //2.动态数组申请大小
    //3.元素个数

    //4.拷贝函数指针
    //5.释放函数指针
    //6.匹配函数指针

    //7.头插
    //8.尾插
    //9.头删
    //10.尾删

    //迭代器
    //头位置
    //尾位置
    //向前迭代
    //向后迭代
    void **data;
    int capacity;
    int count;

    void *(*copy)(void *value);
    void (*free)(void *ptr);
    Boolean (*match)(void *value1,void *value2);
    Boolean (*push_front_array)(struct Array *array,void *value);
    Boolean (*push_back_array)(struct Array *array,void *value);
    Boolean (*pop_front_array)(struct Array *array);
    Boolean (*pop_back_array)(struct Array *array);

    void *(*iter_head_array)(Iterator *iter,struct Array *array);
    void *(*iter_tail_array)(Iterator *iter,struct Array *array);
    void *(*iter_next_array)(Iterator *iter,struct Array *array);
    void *(*iter_prev_array)(Iterator *iter,struct Array *array);
}Array;
/////////////////////////////////////////////////////////////////////////
//接口
Array *init_array(int size);
void destroy_array(Array **array);
void array_clean(Array *array);//清空
Boolean array_prev_insert(Array *array,int index,void *value);
//插入指定数组下标前面
Boolean array_next_insert(Array *array,int index,void *value);
//插入指定数组下标后面
int get_array_count(Array *array);
void *get_array_index(Array *array,int index);//指定下标元素地址
Boolean delete_index_value(Array *array,int index);//删除指定下标元素
Boolean delete_range_value(Array *array,int begin,int end);
//删除指定范围的元素
int find_value(Array *array,void *value);//查找指定元素的下标
void show_array(Array *array);
typedef void (*Print)(Array *);

#endif
