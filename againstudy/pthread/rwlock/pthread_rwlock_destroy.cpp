#include"pthread_rwlock.h"

int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rw)
{
    if(rw->rw_magic != RW_MAGIC)
        return -1;
    if(rw->rw_refcount!=0 || rw->rw_nwaitreaders!=0 || rw->rw_nwaitwriters!=0)
        return -2;
    pthread_mutex_destroy(&rw->rw_mutex);
    pthread_cond_destroy(&rw->rw_condreaders);
    pthread_cond_destroy(&rw->rw_condwriters);
    rw->rw_magic = 0;

    return 0;
}
