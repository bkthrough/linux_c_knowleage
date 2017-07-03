#ifndef _ITER_H_
#define _ITER_H_

typedef struct Iter
{
    void *ptr;
    Dlist_node current_node;
    Dlist_node node;
}Iter;
void *iter_head(Iter *iter,Dlist dlist);
void *iter_next(Iter *iter,Dlist dlist);

#define FOREACH(iter,container) \
        for(iter.ptr = iter_head(&(iter),container); \
        iter.ptr; \
        iter.ptr = iter_next(&(iter),container))
#define foreach FOREACH

#endif
