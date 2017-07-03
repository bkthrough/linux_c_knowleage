//#include<unistd.h>
//#include<stdio.h>
//#include<pthread.h>

#include"pthread_rwlock.h"

pthread_rwlock_t rwlock;
//
void* thread_fun1(void *arg)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("This is fun1.\n");
    pthread_rwlock_unlock(&rwlock);
}
void* thread_fun2(void *arg)
{
    //printf("thread2 is run......\n");
    pthread_rwlock_rdlock(&rwlock);
    printf("This is fun2.\n");
    pthread_rwlock_unlock(&rwlock);
}
void* thread_fun3(void *arg)
{
    //printf("thread3 is run......\n");
    pthread_rwlock_wrlock(&rwlock);
    printf("This is fun3.\n");
    pthread_rwlock_unlock(&rwlock);
}
void* thread_fun4(void *arg)
{
    printf("thread4 is run......\n");
    pthread_rwlock_wrlock(&rwlock);
    printf("This is fun4.\n");
    pthread_rwlock_unlock(&rwlock);
}

int main()
{
    pthread_rwlock_init(&rwlock, NULL);
    pthread_t tid[4];
    pthread_create(&tid[0], NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid[1], NULL, thread_fun2, NULL);
    pthread_create(&tid[2], NULL, thread_fun3, NULL);
    //pthread_create(&tid[3], NULL, thread_fun4, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    //pthread_join(tid[3], NULL);
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
