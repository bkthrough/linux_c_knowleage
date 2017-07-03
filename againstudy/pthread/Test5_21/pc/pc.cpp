#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

#define MAX_SIZE 20
#define BUFFER_SIZE 8

struct 
{
    pthread_mutex_t mutex;
    pthread_cond_t  nofull;
    pthread_cond_t  noempty;
    int buff[BUFFER_SIZE];
    int nput;
    int nval;
    int count;
}shared = {PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER,PTHREAD_COND_INITIALIZER};

void* produce(void *arg)
{
    for(;;)
    {
        //sleep(1);
        pthread_mutex_lock(&shared.mutex);
        //printf("produce lock.\n");
        //if(shared.nval >= 20)
        //{
        //    pthread_mutex_unlock(&shared.mutex);
        //    printf("produce finish.\n");
        //    break;
        //}
        if(shared.count < BUFFER_SIZE)
        {
            //shared.buff[shared.nput] = shared.nval;
            //shared.nput++;
            //if(shared.nput >= BUFFER_SIZE)
                //shared.nput = 0;
            //shared.nval++;
            shared.count++;
            pthread_cond_signal(&shared.noempty);
            printf("%d.\n",shared.count);
        }
        else
            pthread_cond_wait(&shared.nofull, &shared.mutex);
        pthread_mutex_unlock(&shared.mutex);
    }
}
void* consume(void *arg)
{
    for(;;)
    {
        pthread_mutex_lock(&shared.mutex);
        //int j = 0;
        //printf("%d.\n", shared.count);
        if(shared.count > 0)
        {
            //sleep(1);
            //j++;
            //if(j >= BUFFER_SIZE)
                //j = 0;
            shared.count--;
            pthread_cond_signal(&shared.nofull);
        }
        else{
            pthread_cond_wait(&shared.noempty, &shared.mutex);
            //printf("cond unlock.\n");
        }
        printf("%d.\n",shared.count);
        pthread_mutex_unlock(&shared.mutex);
        //printf("mutex unlock.\n");
    }
}

int main()
{
    pthread_t ptid;
    pthread_t ctid;

    //set_concurrency(2);
    printf("%d.\n",shared.count);
    pthread_create(&ctid, NULL, consume, NULL);
    pthread_create(&ptid, NULL, produce, NULL);

    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);

    return 0;
}
