#pragma once
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

typedef struct
{
    pthread_mutex_t rw_mutex;
    pthread_cond_t  rw_condreaders;
    pthread_cond_t  rw_condwriters;
    int             rw_magic;
    int             rw_nwaitreaders;
    int             rw_nwaitwriters;
    int             rw_refcount;
    //rw_refcount的值
    //-1表示一个写者正在写， 0表示没有任何的读写者， >=1表示读者的个数
}my_pthread_rwlock_t;

#define RW_MAGIC  0x19283746

#define MY_PTHREAD_RWLOCK_INITIALIZER {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,\
PTHREAD_COND_INITIALIZER,RW_MAGIC,0,0,0};

typedef int my_pthread_rwlockattr_t;

//////////////////////////////////////////////////////////////////
int my_pthread_rwlock_init(my_pthread_rwlock_t *, my_pthread_rwlockattr_t *);
int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *);
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *t);
int my_pthread_rwlock_destroy(my_pthread_rwlock_t *);

#define pthread_rwlock_t          my_pthread_rwlock_t
#define pthread_rwlock_init       my_pthread_rwlock_init
#define pthread_rwlock_rdlock     my_pthread_rwlock_rdlock
#define pthread_rwlock_wrlock     my_pthread_rwlock_wrlock
#define pthread_rwlock_tryrdlock  my_pthread_rwlock_tryrdlock
#define pthread_rwlock_trywrlock  my_pthread_rwlock_trywrlock
#define pthread_rwlock_unlock     my_pthread_rwlock_unlock
#define pthread_rwlock_destroy    my_pthread_rwlock_destroy



