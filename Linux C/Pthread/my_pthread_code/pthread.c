#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>


#define NUM  10

pthread_t tid[NUM];
pid_t gettid(void)
{
    return syscall(SYS_gettid);
}
void *t_start(void *addr)
{
    int i = 0;
    pid_t tid;
    int run = 1;

    memcpy((void *)&i,(void *)&addr,sizeof(int));
    tid = gettid();
    //while(run){
        printf("----------------------------------------\n");
        printf("tid:%d   i'm No.%d pthread\n",tid,i);
        sleep(1);
    //}
}
void t_create()
{
    int i = 0;
    void *addr = NULL;

    for(i = 0; i < NUM; ++i){
        memcpy((void *)&addr,(void *)&i,sizeof(int));
        pthread_create(&tid[i],NULL,t_start,addr);
        //pthread_detach(tid[i]);
        printf("tid[%d] == %ld\n",i,tid[i]);
    }
}
int main(int argc,char *argv[])
{
    int count = 0;

    t_create();
    while(1){
        printf("thread run\n");
        sleep(1);
    }
    return 0;
}
