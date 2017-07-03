#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>

#define MAX_SIZE 10
int value = 1;
pthread_mutex_t mutex;
pthread_cond_t  d, s;
//1 3 5 7 9 
void* fun1(void *arg)
{
    pthread_mutex_lock(&mutex);
    while(value <= MAX_SIZE)
    {
        if(value % 2 == 1)
        {
            printf("fun1 value = %d\n", value);
            value++;
            sleep(1);
            pthread_cond_signal(&s);
            printf("fun1 sleep 5 second.\n");
            sleep(5);
            printf("fun1 wakeup.\n");
        }
        else
        {
            printf("fun1 wait..\n");
            pthread_cond_wait(&d, &mutex);
            printf("xxxxxxxxxxxxx\n");
        }
    }
    pthread_mutex_unlock(&mutex);
}
//2 4 6 8 10
void* fun2(void *arg)
{ 
    printf("aaaaaaaaaaa\n");
    pthread_mutex_lock(&mutex);
    while(value <= MAX_SIZE)
    {
        if(value % 2 == 0)
        {
            printf("fun2 value = %d\n",value);
            value++;
            sleep(1);
            pthread_cond_signal(&d);
        }
        else
        {
            printf("fun2 wait..\n");
            pthread_cond_wait(&s, &mutex);
            printf("bbbbbbbbbbbbbbbb\n");
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t tid[2];
    pthread_create(&tid[1],NULL, fun2, &tid[0]);
    sleep(1);
    pthread_create(&tid[0],NULL, fun1, NULL);

    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

/*
int COUNT = 5;
int value;
pthread_mutex_t mutex;

void* SetValue(void *arg)
{
    printf("This is Child thread.\n");
    while(COUNT > 0)
    {
        pthread_mutex_lock(&mutex);
        printf("child COUNT =%d\n",COUNT);
        value = COUNT;
        COUNT--;
        srand(time(0));
        sleep(rand() % 3);
        pthread_mutex_unlock(&mutex);
    }
}
void PrintValue()
{
    printf("This is Main thread.\n");
    while(COUNT > 0)
    {
        pthread_mutex_lock(&mutex);
        printf("value = %d\n",value);
        srand(time(0));
        sleep(rand() % 3);
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, SetValue, NULL);
    sleep(1);
    PrintValue();
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

/*
pthread_mutex_t mutex;

int value = 10;

void* thread_fun1(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("This is thread_fun1.\n");
    sleep(5);
    pthread_mutex_unlock(&mutex);
}
void* thread_fun2(void *arg)
{
    printf("thread2 wait......\n");
    pthread_mutex_lock(&mutex);
    printf("This is thread_fun2.\n");
    pthread_mutex_unlock(&mutex);
}
void* thread_fun3(void *arg)
{
    printf("thread3 wait......\n");
    pthread_mutex_lock(&mutex);
    printf("This is thread_fun3.\n");
    pthread_mutex_unlock(&mutex);
}
void* thread_fun4(void *arg)
{
    printf("thread4 wait......\n");
    pthread_mutex_lock(&mutex);
    printf("This is thread_fun4.\n");
    pthread_mutex_unlock(&mutex);
}
void* thread_fun5(void *arg)
{
    printf("thread5 wait......\n");
    pthread_mutex_lock(&mutex);
    printf("This is thread_fun5.\n");
    pthread_mutex_unlock(&mutex);
}


int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t tid[5];
    pthread_create(&tid[0], NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid[1], NULL, thread_fun2, NULL);
    pthread_create(&tid[2], NULL, thread_fun3, NULL);
    pthread_create(&tid[3], NULL, thread_fun4, NULL);
    pthread_create(&tid[4], NULL, thread_fun5, NULL);

    for(int i=0; i<5; ++i)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
*/
