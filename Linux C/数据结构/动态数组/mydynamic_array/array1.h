#ifndef _ARRAY_H_
#define _ARRAY_H_

//防止头文件出现重复的包含

#include "iterator.h"

#define TRUE    (1)
#define FALSE   (0)
#define MODE    (32)
#define ZERO    (0)
#define ONE     (1)

typedef unsigned char Boolean;
typedef struct Array Array;

//定义动态数组的结构体
typedef struct Array{
   void **data ;    // 1.存储实体
   int capacity;    // 2.动态数组的申请大小
   int count   ;    // 3.当前元素个数
   
   //4.拷贝函数指针
   void *(*copy)(void *src_value)
   //5.匹配函数指针
   Boolean (*match)(void *value1, void *value2);
   //6.释放函数指针
   void (*free)(void *ptr);

   //7.头部插入
   Boolean (*push_front)(Array *array, void *value);
   //8.尾部插入
   Boolean (*push_back)(Array *array, void *value);
   //9.头部删除
   Boolean (*pop_front)(Array *array);
   //10.尾部删除
   Boolean (*pop_back)(Array *array);

   //迭代器操作
   //11.指向数组头部的位置
   void *(*iter_head_array)(Iterator *iter, Array *array);
   //12.指向数组尾部的位置
   void *(*iter_tail_array)(Iterator *iter, Array *array);
   //13.指向后一个元素的位置
   void *(*iter_next_array)(Iterator *iter, Array *array);
   //14.指向前一个元素的位置
   void *(*iter_prev_array)(Iterator *iter, Array *array);
}Array;

//动态数组操作接口
Array   *init_array(int init_size)  ;    //动态数组的初始化
void    destroy_array(Array **array);    //动态数组的销毁
void    array_clean(Array *array)   ;    //动态数组清空
//插入到指定下标的前边
Boolean array_prev_insert(Array *array,
            int index, void *value);
//插入到指定下标的后边
Boolean array_next_insert(Array *array,
            int index, void *value);
int     get_array_count(Array *array)              ;    //得到动态数组的个数
void    *get_array_index(Array *array, int index)  ;    //得到指定下标的元素
Boolean delete_index_value(Array *array, int index);    //删除指定下标元素
Boolean delete_range_value(Array *array, 
                           int begin, int end)     ;    //删除指定下标范围的元素
int     find_value(Array *array, void *value)      ;   //查找指定元素的下标


#endif
