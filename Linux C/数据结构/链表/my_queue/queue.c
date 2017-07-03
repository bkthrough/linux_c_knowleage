#include "queue.h"
#include <stdio.h>

Queue init_queue(void)
{
    Queue queue = (Queue)Malloc(sizeof(struct Queue));
    queue->queue_ctr = init_dlist();
    return queue;
}
void in(Queue queue,void *value)
{
    if(value == NULL){
        return ;
    }
    push_front(queue->queue_ctr,value);
}
Boolean out(Queue queue)
{
    if(queue == NULL){
        return FALSE;
    }
    pop_back(queue->queue_ctr);
    return TRUE;
}
Boolean get_queue_front(Queue queue,void **value)
{
    if(queue == NULL){
        return FALSE;
    }
    get_back(queue->queue_ctr,value);
    return TRUE;
}
Boolean is_queue_empty(Queue queue)
{
    if(queue->queue_ctr->count == ZERO){
        return TRUE;
    }
    else
        return FALSE;
}
int get_queue_count(Queue queue)
{
    return queue->queue_ctr->count;
}
void destroy_queue(Queue *queue)
{
    if(queue == NULL){
        return ;
    }
    destroy_dlist(&((*queue)->queue_ctr));
    free(*queue);
    *queue = NULL;
}
