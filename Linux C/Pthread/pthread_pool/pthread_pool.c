#include "pthread_pool.h"

int run = 1;
_pth_stat *task_arr;
_pth_ctl *ptctl;

void *pthgroups(void *ptharg);
int pthread_pool_create(int thnum);
int pthread_pool_mission(void * (*fn)(void *arg), void *arg);
int pthread_pool_end(void);
void _sig_reg(int sig);

void _sig_reg(int sig)
{

}

void *pthgroups(void *ptharg)
{
    _pth_stat pthread_st;
    void * (* func)(void *arg) = pthread_st.task;
            printf("1111111111111\n");

    while(run){
        pause();
    memcpy((void *)&pthread_st, ptharg, sizeof(_pth_stat));
        //(*(pthread_st.task))(pthread_st.ag);
        //pthread_st.is_free = FREE;
        //printf("////////////\n");
        printf("zzzzzzzzzzzzzz\n");
        func = pthread_st.task;
        func(pthread_st.ag);
        pthread_st.is_free = FREE;
    }
    pthread_exit(NULL);
    return NULL;
}

int pthread_pool_create(int thnum)
{
    int loop = 0;

    if(0 >= thnum || TIDMAX < thnum){
        printf("INPUT A ERROR THNUM");
        return -1;
    }

    if(SIG_ERR == signal(SIGUSR1, _sig_reg)){
        printf("signal_reg error\n");
    }
    ptctl = (_pth_ctl *)malloc(sizeof(_pth_ctl));
    task_arr = (_pth_stat *)malloc(sizeof(_pth_stat) * thnum);
    if(NULL == ptctl){
        printf("malloc error\n");
        return -2;
    }
    if(NULL == task_arr){
        printf("malloc error\n");
        return -3;
    }

    ptctl->pthnums = thnum;
    for(loop = 0; loop < thnum; ++loop){
        task_arr[loop].is_free = FREE;
        if(pthread_create((&task_arr[loop].tid), NULL,
           pthgroups, (void *)&task_arr[loop])){
            printf("create error\n");
            break;
          }
    }
    return 0;
}

int pthread_pool_mission(void * (*fn)(void *arg), void *arg)
{
    int loop = 0;

    for(loop = 0; loop < ptctl->pthnums; ++loop){
        if(FREE == task_arr[loop].is_free){
            task_arr[loop].is_free = BUSY;
            task_arr[loop].task = fn;
            task_arr[loop].ag = arg;
            pthread_kill(task_arr[loop].tid, SIGUSR1);
            printf("222222222\n");
        }
    }
    if(ptctl->pthnums == (loop + 1)){
        printf("no free pthread\n");
    }
}

int pthread_pool_end(void)
{
    int loop = 0;

    for(loop = 0; loop < ptctl->pthnums; ++loop){
        pthread_join(task_arr[loop].tid, NULL);
    }
    free(ptctl);
    free(task_arr);
}
