#include <apue.h>

#define THMAX  6

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
    int mytid = gettid();
    while(run){
        printf("[%d]<<<<<<<<<<<<<%d\n",mytid,who.val);
        sleep(1);
    }
    pthread_exit(NULL);
    return NULL;
}


int main(void)
{
    int loop;
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
        pthread_detach(tidmax[loop]);
        //sleep(1);
    }
#endif

    printf(">>>>>>>>>>>>>father:%d\n",fid);
    while(run){
        ++global;
        printf("-----------------------------\n");
        sleep(1);
    }
    //pthread_join(tid,NULL);
    return 0;
}
