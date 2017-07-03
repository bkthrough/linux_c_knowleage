#ifndef _ITERATOR_H_
#define _ITERATOR_H_

typedef struct Iterator{
     void *ptr;    //指向容器中元素的位置
     int  index;   //迭代器在当前容器中的下标
     int  size;    //迭代器指向的容器中有效元素的个数
}Iterator;


// docker
//
// github
//
// dochub
//
// 虚拟化

/*
 * 正向迭代器
 *
 * iterator 
 *
 * container（list、array、stack、queue）
 *
 * */
#define FOREACH(iter, container) \
     for(container->iter_head(&(iter), container); \
     (iter).ptr; \
     container->iter_next(&(iter), container))

#define foreach FOREACH

/*
 * 反向迭代器
 *
 * iterator 
 *
 * container
 *
 * */
#define FOREACH_REVERSE(iter, container) \
     for(container->iter_tail(&(iter), container); \
     (iter).ptr; \
     container->iter_prev(&(iter), container))

#define foreach_reverse FOREACH_REVERSE

#endif
