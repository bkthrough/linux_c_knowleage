#ifndef INCLUDED_THREAD_POOL_H
#define INCLUDED_THREAD_POOL_H
#include <pthread.h>

/*常量宏值定义*/
#define MAX  (128)
#define ZERO (  0)
#define ONE  (  1)
#define TWO  (  2)

/*状态宏值定义*/
#define FALSE (  0)
#define TRUE  (  1)
#define NG    ( -1)
#define OK    (  0)


/*函数指针的重定义*/
typedef void *(*fn_t)(void *arg);

/*线程池的控制信息*/
typedef struct pthread_pool_ctl_s pthread_pool_ctl_t;
struct pthread_pool_ctl_s {
    int thanum;              //线程池的线程总数
    int thfnum;              //剩余的空闲线程总数
};

/*线程池的信息*/
typedef struct pthread_pool_s  pthread_pool_t;
struct pthread_pool_s {
    int       isbusy;
    pthread_t tid;
    fn_t      func;
    void      *arg;
    int       isexit;
    int       iswork;
};

/*线程参数信息*/
typedef union targ_u targ_t;
union targ_u {
    void *para;
    int  index;
};

/*线程池的创建*/
int pthread_pool_create(int thnum);
/*分配任务*/
int pthread_pool_mission(fn_t run, void *arg);
/*销毁线程池*/
int pthread_pool_end();


#endif /*INCLUDED_THREAD_POOL_H*/
