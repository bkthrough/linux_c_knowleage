#include <apue.h>

typedef unsigned char boolean;
#define TRUE  (1==1)
#define FALSE (1==0)
#define THMAX  3

/*
 * /usr/include/pthread.h
 *
 */
pthread_spinlock_t      spinlock_lock;

pthread_t thid[THMAX];

int run = TRUE ;

void sig_handle(int sig)
{
    run = FALSE;
}

boolean pthread_spin_set(pthread_spinlock_t *spinlock)
{
    boolean rst = TRUE;
    if(NULL == spinlock){
        rst = FALSE;
    }
    if(rst && pthread_spin_init(spinlock,PTHREAD_PROCESS_PRIVATE)){
        rst = FALSE;
    }

    return rst;
}

void *thfunc(void *input)
{
    int myid;
    memcpy(&myid,&input,sizeof(int));
    while(run){
        pthread_spin_lock(&spinlock_lock);
        printf("%d running\n",myid);
        //usleep(10);
        //sleep(1 + 5*myid);
        sleep(1);
        pthread_spin_unlock(&spinlock_lock);
        usleep(10);
    }
    pthread_exit(NULL);
    return NULL;
}

/*
 * resource collection
 */
void rsc_coll(boolean istest)
{
    if(istest){
        pthread_spin_lock(&spinlock_lock);
        pthread_spin_unlock(&spinlock_lock);
    }
    pthread_spin_destroy(&spinlock_lock);
    printf("Proc END .\n");
    return;
}

int main(void)
{
    int  loop = 0;
    void *input;

    if(SIG_ERR == signal(SIGINT,sig_handle)){
        rsc_coll(FALSE);
        return 1;
    }

    loop = pthread_spin_set(&spinlock_lock);
    if(TRUE != loop){
        rsc_coll(FALSE);
        return 1;
    }
    for(loop=0;loop<THMAX;++loop){
        memcpy(&input,&loop,sizeof(int));
        if(pthread_create(&thid[loop],NULL,thfunc,input)){
            break;
        }
    }
    for(loop=0;loop<THMAX;++loop){
        pthread_join(thid[loop],NULL);
    }
    rsc_coll(TRUE);
    return 0;
}
