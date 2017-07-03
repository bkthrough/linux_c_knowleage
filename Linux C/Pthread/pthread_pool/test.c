#include "pthread_pool.h"

int runflg = 1;
union tpar{
    int val;
    void *ptr;
};

void _sig_hander(int sig);
void *mytest(void *thn);

void *mytest(void *thn)
{
    union tpar tp;
    tp.ptr = thn;
    printf("----------%d\n", tp.val);
    return NULL;
}

void _sig_hander(int sig)
{
    runflg = 0;
}

int main(int argc, char **argv)
{
    int thnum = 0;
    int argnum = 0;
    int rst = 0;
    union tpar *arg;

    if(1 >= argc){
        printf("Usage : %s <thread-number>\n", argv[0]);
        return 1;
    }

    if(SIG_ERR == signal(SIGINT, _sig_hander)){
        printf("signal reg error\n");
        return 2;
    }
    thnum = atoi(argv[1]);
    arg = (union tpar *)malloc(sizeof(union tpar) * thnum);
    if(NULL == arg){
        printf("malloc error\n");
        return 3;
    }
    if(0 != (rst = pthread_pool_create(thnum))){
        printf("pthread_poll_create error    %d\n", rst);
        return 4;
    }
    printf("3333333333333\n");

    while(runflg){
        arg[argnum].ptr = NULL;
        arg[argnum].val = argnum;
        pthread_pool_mission(mytest, arg);
        argnum = (argnum + 1) % thnum;
        sleep(1);
    }
    pthread_pool_end();
    free(arg);
    return 0;
}
