#include <apue.h>

#define TRUE  (0==0)
#define FALSE (0==1)

typedef unsigned char Boolean;

pthread_mutex_t      mutex_lock;
pthread_mutexattr_t  mutexattr_lock;
pthread_t *tid;

int run = TRUE;

void END(int sig)
{
    run = FALSE;
}

Boolean pthread_mutex_set(pthread_mutex_t *mutex,pthread_mutexattr_t *mutexattr)
{
    Boolean rst = TRUE;

    if(NULL == mutex || NULL == mutexattr){
        rst = FALSE;
    }
    if(rst && pthread_mutexattr_init(mutexattr)){
        rst = FALSE;
    }
    //设置为普通锁
    if(rst && pthread_mutexattr_settype(mutexattr,PTHREAD_MUTEX_NORMAL)){
        rst = FALSE;
    }
    if(rst && pthread_mutex_init(mutex,mutexattr)){
        rst = FALSE;
    }

    return rst;
}

void *thfun(void *id)
{
    while(run){
//选择编译
#if 0
        pthread_mutex_lock(&mutex_lock);
#else
        //没加上就一直尝试加锁
        while(pthread_mutex_trylock(&mutex_lock)){
            usleep(10);
            continue;
        }
#endif
        printf("lock\n");
        printf("i'm %d\n",(int *)id);
        printf("other thread can't visit me\n");
        sleep(1);
        pthread_mutex_unlock(&mutex_lock);

        //这行比较重要，如果不让线程休眠，那么该线程会一直占用cpu
        //刚刚解锁就又占用了cpu，导致其他阻塞线程根本执行不到
        usleep(1);
    }

    pthread_exit(NULL);
    return NULL;
}

void test()
{
    //判断是否解锁，如果未解锁，那么会阻塞。直到解锁后就可以销毁锁啦！！
    //很精妙
    pthread_mutex_lock(&mutex_lock);
    pthread_mutex_unlock(&mutex_lock);

    pthread_mutexattr_destroy(&mutexattr_lock);
    pthread_mutex_destroy(&mutex_lock);

    return ;
}
int main()
{
    int loop = 0;
    void *id;
    int value;
    id = malloc(4);
    tid = (pthread_t *)malloc(sizeof(int) * 3);

    if(SIG_ERR == signal(SIGINT,END)){
        return 1;
    }
    value = pthread_mutex_set(&mutex_lock,&mutexattr_lock);
    if(!value){
        return 2;
    }
    for(loop = 0; loop < 3; ++loop){
        //必须要这样做，相当于把id单元放的就是loop的值。
        //因为如果id指向的是loop，那么会有线程加载时间，而这个时候
        //loop已经是别的值了
        printf("running loop\n");
        memcpy(&id,&loop,sizeof(int));
        pthread_create(&tid[loop],NULL,thfun,id);
    }
    for(loop = 0; loop < 3; ++loop){
        pthread_join(tid[loop],NULL);
    }
    test();

    return 0;
}
