#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
using namespace std;

void *func(void *arg)
{
    pthread_t tid;
    const char *retval = "i'm exit";
    cout << "hehe" << endl;

    pthread_exit((void *)retval);
}
int main()
{
    int i = 3;
    pthread_t tid;
    char *retval = NULL;
    pthread_attr_t attr;
    struct sched_param param;
    int s;

    s = pthread_attr_init(&attr);
    if(s != 0){
        perror("");
        //cout << strerror(errno) << endl;
    }
    s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    if(s != 0)
        perror("");
    s = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
    if(s != 0)
        perror("");
    param.sched_priority = 1;
    s = pthread_attr_setschedparam(&attr, &param);
    if(s != 0){
        perror("");
    }
    pthread_create(&tid, &attr, func, &i);
    s = pthread_attr_getschedparam(&attr, &param);
    if(s != 0){
        perror("");
    }
    cout << param.sched_priority << endl;
    pthread_join(tid, (void **)&retval);
    cout << "i'm parent thread" << endl;
    cout << retval << endl;
    return 0;
}
