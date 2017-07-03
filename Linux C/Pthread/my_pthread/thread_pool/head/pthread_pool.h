#ifndef _PTHREAD_POOL_H_
#define _PTHREAD_POOL_H_

#include <pthread.h>

#define TRUE  (1)
#define FALSE (0)

typedef unsigned char Boolean;
//每个线程的信息
typedef struct Pthread
{
    int      flag;
    int   is_wait;
    void      *fn;
    void     *arg;
    pthread_t tid;
    int       num;
}Pthread;

//线程控制信息
typedef struct Pthread_ctl
{
    int        thnum;
    Pthread *pthread;
}Pthread_ctl;

Boolean pthread_pool_create(int thnum);
Boolean pthread_pool_mission(void *(*fn)(void *arg),void *arg);
Boolean pthread_pool_end(void);
void *fn(void *arg);

#endif
