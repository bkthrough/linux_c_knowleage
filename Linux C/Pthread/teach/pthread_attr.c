#include <apue.h>

pthread_attr_t thattr;
pthread_t      thid;

int run = 1;

void pthread_attr_set(pthread_attr_t *attr)
{
    if(NULL == attr){
        return ;
    }
    pthread_attr_init(attr);
    //if(pthread_attr_setdetachstate(attr,PTHREAD_CREATE_DETACHED)){
    if(pthread_attr_setdetachstate(attr,PTHREAD_CREATE_JOINABLE)){
        return;
    }
    if(pthread_attr_setstacksize(attr,10485760)){
        return;
    }
    return;
}

void * thfunc(void *in)
{
    while(run){
        printf(">>>>>>>>>>>>>>>>\n");
        sleep(1);
    }
}

int main(void)
{
    pthread_attr_set(&thattr);

    if(pthread_create(&thid,&thattr,thfunc,NULL)){
    //error
        printf("create error[%d]\n",errno);
    }

    pthread_join(thid,NULL);

    pthread_attr_destroy(&thattr);
    return 0;
}
