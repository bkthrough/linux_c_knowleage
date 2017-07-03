#include <apue.h>

typedef unsigned char boolean;
#define TRUE  (1==1)
#define FALSE (1==0)
#define THMAX  3

/*
 * /usr/include/pthread.h
 *
 */
pthread_mutex_t      mutex_lock;
//pthread_mutex_t      mutex_lock = PTHREAD_MUTEX_INITIALIZER ;

pthread_mutexattr_t  mutexattr_lock;
pthread_t thid[THMAX];

int run = TRUE ;

void sig_handle(int sig)
{
    run = FALSE;
}

boolean pthread_mutex_set(pthread_mutex_t *mutex,pthread_mutexattr_t *mutexattr)
{
    boolean rst = TRUE;
    if(NULL == mutex || NULL == mutexattr){
        rst = FALSE;
    }
    if(rst && pthread_mutexattr_init(mutexattr)){
        rst = FALSE;
    }
    if(rst && pthread_mutexattr_settype(mutexattr,PTHREAD_MUTEX_NORMAL)){
        rst = FALSE;
    }
    if(rst && pthread_mutex_init(mutex,mutexattr)){
        rst = FALSE;
    }

    return rst;
}

void *thfunc(void *input)
{
    int myid;
    memcpy(&myid,&input,sizeof(int));
    while(run){
#if 1
        pthread_mutex_lock(&mutex_lock);
#else
        while(pthread_mutex_trylock(&mutex_lock)){
            usleep(10);
            continue;
        }
#endif
        printf("%d running\n",myid);
        //usleep(10);
        sleep(1);
        pthread_mutex_unlock(&mutex_lock);
        usleep(1);
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
        pthread_mutex_lock(&mutex_lock);
        pthread_mutex_unlock(&mutex_lock);
    }
    pthread_mutexattr_destroy(&mutexattr_lock);
    pthread_mutex_destroy(&mutex_lock);
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

    loop = pthread_mutex_set(&mutex_lock,&mutexattr_lock);
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
