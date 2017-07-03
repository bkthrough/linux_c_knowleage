#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "pthread_rwlock.h"

my_pthread_rwlock_t rwlock;
pthread_t tid[3];

int my_pthread_rwlock_destroy(my_pthread_rwlock_t *rwlock)
{
    if(0 != pthread_mutex_destroy(&(rwlock->mutex)))
        return -1;
    if(0 != pthread_cond_destroy(&(rwlock->wcond)))
        return -1;
    if(0 != pthread_cond_destroy(&(rwlock->rcond)))
        return -1;
    rwlock->ref_count = 0;

    return 0;
}
int my_pthread_rwlock_init(my_pthread_rwlock_t *rwlock)
{
    if(0 != pthread_mutex_init(&(rwlock->mutex), NULL))
        return -1;
    if(0 != pthread_cond_init(&(rwlock->wcond), NULL))
        return -1;
    if(0 != pthread_cond_init(&(rwlock->rcond), NULL))
        return -1;
    rwlock->ref_count = 0;

    return 0;
}
int my_pthread_rwlock_rdlock(my_pthread_rwlock_t *rwlock)
{
    if(0 != pthread_mutex_lock(&(rwlock->mutex)))
        printf("error.\n");
    //while(rwlock->ref_count < 0){
    //    pthread_cond_wait(&(rwlock->rcond), &(rwlock->mutex));
    //}
    rwlock->ref_count += 1;
    pthread_mutex_unlock(&rwlock->mutex);

    return 0;
}
int my_pthread_rwlock_wrlock(my_pthread_rwlock_t *rwlock)
{
    //printf("wrlock\n");
    if(rwlock->ref_count < 0)
        pthread_cond_wait(&(rwlock->wcond), &(rwlock->mutex));
    else
        if(0 != pthread_mutex_lock(&(rwlock->mutex)))
            printf("error.\n");
    rwlock->ref_count--;

    return 0;
}
int my_pthread_rwlock_trywrlock(my_pthread_rwlock_t *rwlock)
{
    if(rwlock->ref_count > 0){
        return -1;
    }
    if(rwlock->ref_count < 0){
        pthread_cond_wait(&(rwlock->wcond), &(rwlock->mutex));
    }
    if(rwlock->ref_count == 0)
        pthread_mutex_lock(&(rwlock->mutex));

    return 0;
}
int my_pthread_rwlock_tryrdlock(my_pthread_rwlock_t *rwlock)
{
    if(rwlock->ref_count < 0){
        return -1;
    }
    rwlock->ref_count += 1;

    return 0;
}
int my_pthread_rwlock_unlock(my_pthread_rwlock_t *rwlock)
{
    pthread_mutex_t mut;
    pthread_mutex_init(&mut, NULL);
    if(rwlock->ref_count < 0){
        pthread_mutex_unlock(&(rwlock->mutex));
        pthread_mutex_lock(&mut);
        rwlock->ref_count++;
        pthread_mutex_unlock(&mut);
        if(rwlock->ref_count < 0)
            pthread_cond_signal(&(rwlock->wcond));
        else
            pthread_cond_broadcast(&(rwlock->rcond));
    }else if(rwlock->ref_count == 0){
        return -1;
    }else if(rwlock->ref_count == 1){
        pthread_mutex_lock(&mut);
        rwlock->ref_count--;
        pthread_mutex_unlock(&mut);
    }else{
        pthread_mutex_lock(&mut);
        rwlock->ref_count--;
        pthread_mutex_unlock(&mut);
    }

    return 0;
}
void clean_up(void *arg)
{
    printf("clean.\n");
    my_pthread_rwlock_unlock(&rwlock);
}
void *thread_fun1(void *arg)
{
    my_pthread_rwlock_rdlock(&rwlock);
    printf("this is fun1.\n");
    pthread_cleanup_push(clean_up, NULL);
    //sleep(1);
    sleep(4);
    pthread_cleanup_pop(0);
    my_pthread_rwlock_unlock(&rwlock);
}
void *thread_fun2(void *arg)
{
    my_pthread_rwlock_rdlock(&rwlock);
    pthread_cancel(tid[0]);
    printf("this is fun2.\n");
    my_pthread_rwlock_unlock(&rwlock);
}
void *thread_fun3(void *arg)
{
    //int res = 0;
    //res = my_pthread_rwlock_trywrlock(&rwlock);
    //printf("thread3 start.\n");
    my_pthread_rwlock_wrlock(&rwlock);
    printf("this is fun3.heheh\n");
    my_pthread_rwlock_unlock(&rwlock);
}
int main()
{
    my_pthread_rwlock_init(&rwlock);
    pthread_create(&tid[0], NULL, thread_fun1, NULL);
    sleep(1);
    pthread_create(&tid[1], NULL, thread_fun2, NULL);
    pthread_create(&tid[2], NULL, thread_fun3, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    my_pthread_rwlock_destroy(&rwlock);

    return 0;
}
