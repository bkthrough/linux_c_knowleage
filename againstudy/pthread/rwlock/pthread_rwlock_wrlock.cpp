#include"pthread_rwlock.h"

int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return -1;

    if((result=pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;

    while(rw->rw_refcount != 0)
    {
        //等待写者+1，直到可以写了，写者-1
        rw->rw_nwaitwriters++;
        result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
        rw->rw_nwaitwriters--;
        if(result != 0)
            break;
    }
    //返回0说明成功，那么引用计数设置为-1，表示有一个人在写
    if(result == 0)
        rw->rw_refcount = -1;

    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}


