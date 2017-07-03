#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX_THING  (20)
pthread_mutex_t mutex;
pthread_cond_t  Full;
pthread_cond_t  Empty;
int count = 0;

void init()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&Full, NULL);
    pthread_cond_init(&Empty, NULL);
}
void *produce(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
        //生产过于多，那么就停止等待消费者消费
        if(count == MAX_THING){
            //自动解锁，等到信号发过来上锁
            pthread_cond_wait(&Full, &mutex);
            //有可能消费者跑得很快，而信号的发送很慢
            //导致消费者都消费完了，因为空而阻塞
            //if(count == 0)
            //    pthread_cond_signal(&Empty);
            //count += 1;
        }else if(count == 0){
            //防止消费者等待，没有货了就生产并且发信号
            count += 1;
            pthread_cond_signal(&Empty);
        }else{
            count += 1;
        }
        cout << "生产者：" << count << endl;
        pthread_mutex_unlock(&mutex);
    }
}
void *consume(void *arg)
{
    while(1){
        pthread_mutex_lock(&mutex);
        if(count == MAX_THING){
            //生产者阻塞在最大值处，那么消费者因为wait解锁
            //进入当前代码区，给数量-1，然后发信号
            count -= 1;
            pthread_cond_signal(&Full);
        }else if(count == 0){
            //等生产者
            pthread_cond_wait(&Empty, &mutex);
            //防止一种情况，等的过程因为跑得很快，导致生产者成产的
            //货物满了，生产者阻塞
            //if(count == MAX_THING)
            //    pthread_cond_signal(&Full);
            //count -= 1;
        }else{
            count -= 1;
        }
        cout << "消费者：" << count << endl;
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_t tid[2];

    pthread_create(&tid[1], NULL, consume, NULL);
    pthread_create(&tid[0], NULL, produce, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
