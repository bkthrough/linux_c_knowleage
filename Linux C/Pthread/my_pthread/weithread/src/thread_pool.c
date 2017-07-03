#include <thread_pool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
pthread_pool_t *phead         = NULL;
pthread_pool_ctl_t *phead_ctl = NULL;

void *pthread_run(void *arg)
{
    targ_t tmp;
    sigset_t set;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    memset(&tmp, 0, sizeof(tmp));
    tmp.para = arg;
    while(TRUE) {
        sleep(1);
        if (phead[tmp.index].iswork == TRUE) { 
            printf("thread run is test...\n");
            phead[tmp.index].func(phead[tmp.index].arg);
            phead[tmp.index].iswork = FALSE;
            phead[tmp.index].isbusy = FALSE;
            pthread_mutex_lock(&mutex);
            phead_ctl->thfnum++;
            pthread_mutex_unlock(&mutex);
        }
        if (phead[tmp.index].isexit == TRUE) {
            printf("thread_pool is destroy!\n");
            break;
        }
    }/*end while*/

    pthread_exit(NULL);
}

/*线程池的创建*/
int pthread_pool_create(int thnum)
{
    int index  = ZERO;
    int result = NG;
    targ_t tmp;

    phead_ctl = (pthread_pool_ctl_t *)malloc(sizeof(pthread_pool_ctl_t)
                                 + sizeof(pthread_pool_t) * thnum);
    if (!phead_ctl) {
        return result;
    }/*end if*/
    phead = (pthread_pool_t *)(phead_ctl + ONE);
    phead_ctl->thanum = thnum;
    phead_ctl->thfnum = thnum;
    memset(phead, ZERO, sizeof(pthread_pool_t) * thnum);
    memset(&tmp, ZERO, sizeof(targ_t));
    for (index = ZERO; index < thnum; ++index) {
        tmp.index = index;
        phead[index].isexit = FALSE;
        phead[index].iswork = FALSE;
        if (pthread_create(&(phead[index].tid), NULL,
                           pthread_run, tmp.para)) {
            break;
        }
        if (pthread_detach(phead[index].tid)) {
            break;
        }/*end if*/
    }/*end for*/

    if (index == thnum) {
        result = OK;
    }/*end if*/

    return result;
}

/*分配任务*/
int pthread_pool_mission(fn_t run, void *arg)
{
    int loop   = ZERO;
    int result = NG;

    if (!run) {
        printf("func is NULL!\n");
        return result;
    }/*end if*/

    if (phead_ctl->thanum <= ZERO) {
        printf("thread_pool is full!\n");
        return result;
    }/*end if*/

    for (loop = ZERO; loop < phead_ctl->thanum; ++loop) {
        if (!phead[loop].isbusy) {
            phead[loop].isbusy = TRUE;
            phead[loop].func   = run;
            phead[loop].arg    = arg;
            phead_ctl->thfnum--;
            phead[loop].iswork = TRUE;
            break;
        }/*end if*/
    }/*end for*/

    if (loop != phead_ctl->thanum) {
        result = OK;
    }/*end if*/

    return result;
}

/*销毁线程池*/
int pthread_pool_end()
{
    int loop = ZERO;

    for (loop = ZERO; loop < phead_ctl->thanum; ++loop) {
         phead[loop].isexit = TRUE;
    }/*end for*/
}
