#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PARA_ERR   (1)

int run = 1;
int life = 0;

pthread_t *tid;
union tpar{
    int val;
    void *ptr;
};
void *pfunc(void *input)
{
    union tpar who;
    int mylife = 0;

    who.ptr = input;
    if(0 == who.val){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    }
    else if(1 == who.val){
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
        pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    }
    else if(2 == who.val){
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    }
    while(run && mylife < life){
        mylife += 1;
        printf("i'm No%d\n",who.val);
        printf("------------------------\n");
        sleep(1);
    }

    pthread_exit(NULL);
    return NULL;
}
int main(int argc,char *argv[])
{
    int loop;
    int num;
    union tpar tp;

    if(1 >= argc){
        printf("error\n");
        return PARA_ERR;
    }
    num = atoi(argv[1]);
    life = num;
    tid = malloc(sizeof(pthread_t) * num);
    for(loop = 0; loop < num; ++loop){
        tp.ptr = NULL;
        tp.val = loop;
        pthread_create(&tid[loop],NULL,pfunc,tp.ptr);
    }
    for(loop = 0; loop < num; ++loop){
        pthread_cancel(tid[loop]);
    }
    for(loop = 0; loop < num; ++loop){
        pthread_join(tid[loop],NULL);
    }
    printf("pro end\n");

    return 0;
}
