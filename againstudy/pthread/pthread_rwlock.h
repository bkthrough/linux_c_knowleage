#pragma once

typedef struct
{
    int             ref_count;
    pthread_mutex_t mutex;
    pthread_cond_t  rcond;
    pthread_cond_t  wcond;
}my_pthread_rwlock_t;
