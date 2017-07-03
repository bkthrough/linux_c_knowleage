#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef struct Iterator
{
    void *ptr;    //元素位置
    int index;    //迭代器在当前容器中的下标
    int size;     //迭代器指向的容器中有效元素的个数
}Iterator;

//正向迭代器
#define FOREACH(iter,container) \
    for(container->iter_head_array(&(iter),container); \
    iter.ptr; \
    container->iter_next_array(&(iter),container))
#define foreach FOREACH

//反向迭代器
#define FOREACH_REVERSE(iter,container) \
    for(container->iter_tail_array(&(iter),container); \
    iter.ptr; \
    container->iter_prev_array(&(iter),container))
#define foreach_reverse FOREACH_REVERSE

#endif
