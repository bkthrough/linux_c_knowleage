#include "pthread_pool.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define IDLE   (0)
#define BUSY   (1)
#define WAKE   SIGUSR1
#define END    SIGUSR2
#define NO     (0)
#define YES    (1)
#define FREE   (0)

int run = 1;
Pthread_ctl *pthread_ctl;
typedef void *(*Func)(void *);

static void *Malloc(int size)
{
    void *result;

    result = malloc(size);
    if(result == NULL){
        fprintf(stderr,"can't malloc");
    }
    return result;
}
void _sig_wake(int sig)
{
    //continue
}
void _sig_end(int sig)
{
    run = 0;
}
void *fn(void *arg)
{
    Pthread pthread;
    Func func;
    void *argv;

    pause();
    argv = Malloc(sizeof(Pthread));
    while(run){
        bzero(&pthread,sizeof(Pthread));
        //memset(argv,0x00,sizeof(Pthread));
        memcpy((void *)&pthread,arg,sizeof(Pthread));
        func = pthread.fn;
        printf("%p\n",func);
        argv = pthread.arg;
        //执行用户函数
        func(argv);
        ((Pthread *)arg)->flag = IDLE;
        pthread.is_wait = NO;
        //memset(argv,0x00,sizeof(Pthread));
        pause();
    }

    pthread_exit(NULL);
    return NULL;
}

//给线程分配任务
Boolean pthread_pool_mission(void *(*fn)(void *arg),void *arg)
{
    int i = 0;
    Pthread *pthread = NULL;

    for(i = 0; i < pthread_ctl->thnum; ++i){
        pthread = (Pthread *)(pthread_ctl+1) + i;
        if(pthread->flag == BUSY){
            printf("i'm busy\n");
        }
        //如果线程是闲的状态,那么就给它分配任务
        else if(pthread->flag == IDLE){
            pthread->flag = BUSY;
            printf("pthread is idle\n");
            pthread->fn = fn;
            pthread->arg = arg;
            pthread_kill(pthread->tid,WAKE);
            break;
        }
    }

    return TRUE;
}

//线程池的创建
Boolean pthread_pool_create(int thnum)
{
    int loop = 0;
    Pthread *pthread;

    if(thnum <= 0){
        printf("Thnum error\n");
        return FALSE;
    }
    //给pthread_ctl和pthread空间
    pthread_ctl = (Pthread_ctl *)Malloc(sizeof(Pthread_ctl) +
                                        sizeof(Pthread) * thnum);
    pthread_ctl->thnum = thnum;
    pthread_ctl->pthread = (Pthread *)Malloc(sizeof(Pthread) * thnum);
    for(loop = 0; loop < thnum; ++loop){
        signal(WAKE,_sig_wake);
        signal(END,_sig_end);
        //pthread的第一个元素地址就等于pthread_ctl的首地址加1
        pthread = (Pthread *)(pthread_ctl + 1) + loop;
        pthread->flag = IDLE;
        pthread->is_wait = YES;
        pthread->num = loop;
        pthread_create(&(pthread->tid),NULL,fn,(void *)pthread);
        //pthread_ctl->pthread[loop].flag = IDLE;
        //pthread_ctl->pthread[loop].is_wait = YES;
        //pthread_create(&(pthread_ctl->pthread[loop].tid),NULL,fn,(void *)&(pthread_ctl->pthread[loop]));
    }
    return TRUE;
}

//结束线程池
Boolean pthread_pool_end(void)
{
    int loop = 0;
    Pthread *pthread;

    for(;loop < pthread_ctl->thnum; ++loop){
        pthread = (Pthread *)(pthread_ctl + 1) + loop;
        if(pthread->flag == IDLE){
            continue;
        }else{
            printf("please wait,one thread is running!!\n");
            sleep(3);
            if(pthread->flag == BUSY){
                pthread_cancel(pthread->tid);
            }
        }
    }
    for(loop = 0; loop < pthread_ctl->thnum; ++loop){
        pthread = (Pthread *)(pthread_ctl + 1) + loop;
        if(pthread->is_wait == YES){
            pthread_kill(pthread->tid,END);
        }
        if(0 != pthread_join(pthread->tid,NULL)){
            printf("join error\n");
        }
    }

    return TRUE;
}

