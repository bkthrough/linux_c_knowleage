#include <apue.h>

#define THMAX  6
#define LIFE   5

union tpar {
    int val;
    void *ptr;
};

pthread_t tid,tidmax[6];
int run = 1;
int global = 1;

pid_t gettid(void)
{
    return syscall(SYS_gettid);
}

void *thfunc(void *firepan)
{
    pid_t  myfa = *(int *)firepan;
    //pid_t myid = getpid();
    pid_t myid = gettid();
    printf("[father:%d]mypid,mytid:%d,%lu\n",myfa,myid,tid);
    while(run){
       printf("global:%d\n",global); 
       sleep(1); 
    }//end while
    pthread_exit(NULL);
    return NULL;
}

void * thgroups(void *myid)
{
    union tpar who;
    who.ptr = myid;
    int mytid = gettid(),mylife = 0;
    if(1 == who.val){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    }
    if(2 == who.val){
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    }
    if(3 == who.val){
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    }
    while(run && mylife < LIFE){
        mylife += 1;
        printf("[%d]<<<<<<<<<<<<<%d\n",mytid,who.val);
        sleep(1);
    }
    printf("<><><> %d\n",who.val);
    pthread_exit(NULL);
    return NULL;
}


int main(void)
{
    int loop,err;
    union tpar tp;
    pid_t fid = getpid();

#if 0
    if(pthread_create(&tid,NULL,thfunc,(void *)&fid)){
        //error
    }
#else
    for(loop=0;loop<THMAX;++loop){
        tp.ptr = NULL;
        tp.val = loop;
        if(pthread_create(&tidmax[loop],NULL,thgroups,tp.ptr)){
            //error
            break;
        }
        //pthread_detach(tidmax[loop]);
    }
#endif

    printf(">>>>>>>>>>>>>father:%d\n",fid);
#if 0
    while(run){
        ++global;
        printf("-----------------------------\n");
        sleep(1);
    }
#endif
    //set detach
    pthread_detach(tidmax[0]);

    //cancel
    pthread_cancel(tidmax[1]);
    pthread_cancel(tidmax[2]);
    pthread_cancel(tidmax[3]);
    //join
    for(loop=0;loop<THMAX;++loop){
        err = pthread_join(tidmax[loop],NULL);
        printf("%ld\n",tidmax[loop]);
        if(0 != err){
            printf("pthread_join error [%d,%d]\n",loop,err);
        }
    }
    return 0;
}
