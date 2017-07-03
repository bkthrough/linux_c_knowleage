#include"pthread_rwlock.h"

int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rw)
{
    int result;
    if(rw->rw_magic != RW_MAGIC)
        return -1;

    if((result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
        return -1;

    if(rw->rw_refcount > 0)
        rw->rw_refcount--;
    else if(rw->rw_refcount == -1)
        rw->rw_refcount = 0;
    else
        printf("refcount error. refcount = %d\n",rw->rw_refcount);

    if(rw->rw_nwaitwriters > 0)
    {
        if(rw->rw_refcount == 0)
            result = pthread_cond_signal(&rw->rw_condwriters);
    }
    //广播所有读的人都可以解锁
    else if(rw->rw_nwaitreaders > 0)
        pthread_cond_broadcast(&rw->rw_condreaders);

    pthread_mutex_unlock(&rw->rw_mutex);
    return result;
}
