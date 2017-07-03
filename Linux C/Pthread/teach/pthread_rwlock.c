#include <apue.h>

typedef unsigned char boolean;
#define TRUE  (1==1)
#define FALSE (1==0)
#define THMAX  6

/*
 * /usr/include/pthread.h
 *
 */
pthread_rwlock_t      rwlock_lock;
//pthread_rwlock_t      rwlock_lock = PTHREAD_rwlock_INITIALIZER ;

pthread_rwlockattr_t  rwlockattr_lock;
pthread_t thid[THMAX];

int run = TRUE ;
int global  = 1;

void sig_handle(int sig)
{
    run = FALSE;
}

boolean pthread_rwlock_set(pthread_rwlock_t *rwlock,pthread_rwlockattr_t *rwlockattr)
{
    boolean rst = TRUE;
    if(NULL == rwlock || NULL == rwlockattr){
        rst = FALSE;
    }
    if(rst && pthread_rwlockattr_init(rwlockattr)){
        rst = FALSE;
    }
    if(rst && pthread_rwlockattr_setpshared(rwlockattr,PTHREAD_PROCESS_PRIVATE)){
        rst = FALSE;
    }
    if(rst && pthread_rwlock_init(rwlock,rwlockattr)){
        rst = FALSE;
    }

    return rst;
}

void *thread(void *input)
{
    int myid;
    memcpy(&myid,&input,sizeof(int));
    while(run){
        pthread_rwlock_rdlock(&rwlock_lock);
        printf("%d running [global:%d]\n",myid,global);
        sleep(1);
        pthread_rwlock_unlock(&rwlock_lock);
        usleep(12);
    }
    pthread_exit(NULL);
    return NULL;
}


void *thwrite(void *input)
{
    int myid;
    memcpy(&myid,&input,sizeof(int));
    while(run){
        pthread_rwlock_wrlock(&rwlock_lock);
        global += (myid + 1);
        printf("-------- write %d ----------\n",global);
        sleep(1);
        pthread_rwlock_unlock(&rwlock_lock);
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
        pthread_rwlock_rdlock(&rwlock_lock);
        pthread_rwlock_unlock(&rwlock_lock);
        pthread_rwlock_wrlock(&rwlock_lock);
        pthread_rwlock_unlock(&rwlock_lock);
    }
    pthread_rwlockattr_destroy(&rwlockattr_lock);
    pthread_rwlock_destroy(&rwlock_lock);
    printf("Proc END .\n");
    return;
}

int main(void)
{
    int  loop = 0;
    int  thrd = THMAX - (THMAX/3),thwr = THMAX/3;
    void *input;

    if(SIG_ERR == signal(SIGINT,sig_handle)){
        rsc_coll(FALSE);
        return 1;
    }

    loop = pthread_rwlock_set(&rwlock_lock,&rwlockattr_lock);
    if(TRUE != loop){
        rsc_coll(FALSE);
        return 1;
    }
    for(loop=0;loop<thrd;++loop){
        memcpy(&input,&loop,sizeof(int));
        if(pthread_create(&thid[loop],NULL,thread,input)){
            break;
        }
    }
    for(loop=0;loop<thwr;++loop){
        memcpy(&input,&loop,sizeof(int));
        if(pthread_create(&thid[loop+thrd],NULL,thwrite,input)){
            break;
        }
    }
    for(loop=0;loop<THMAX;++loop){
        pthread_join(thid[loop],NULL);
    }
    rsc_coll(TRUE);
    return 0;
}
