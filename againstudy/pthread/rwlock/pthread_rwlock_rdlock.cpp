#include"pthread_rwlock.h"

int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return -1;

    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return result;
    //如果有人正在写，或者等着写，那么就等条件变量
    //这样也保证了先写后读(因为只要有人等待写，那么我就得等这个人)
    while(rw->rw_refcount<0 || rw->rw_nwaitwriters>0)
    {
        rw->rw_nwaitreaders++;
        result = pthread_cond_wait(&rw->rw_condreaders, &rw->rw_mutex);
        rw->rw_nwaitreaders--;
        if(result != 0)
            break;
    }
    if(result == 0)
        rw->rw_refcount++;
    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}
