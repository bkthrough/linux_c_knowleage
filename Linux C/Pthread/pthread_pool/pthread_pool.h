#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_

#include <apue.h>

#define TIDMAX 1024
#define FREE   0
#define BUSY   1

typedef struct pth_stat{
    int is_free;
    pthread_t tid;
    void *(* task)(void *ag);
    void *ag;
}_pth_stat;

typedef struct pth_ctl{
    int pthnums;
    _pth_stat *pth;
}_pth_ctl;
int pthread_pool_create(int thnum);
int pthread_pool_mission(void * (*fn)(void *arg), void *arg);
int pthread_pool_end(void);

#endif
