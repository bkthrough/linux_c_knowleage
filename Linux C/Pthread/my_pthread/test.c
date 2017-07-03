#include <apue.h>

void *printabc(void *str)
{
    sleep(1);
    printf("hello\n");

    pthread_exit(NULL);
    return NULL;
}
int main()
{
    pthread_t tid;

    pthread_create(&tid,NULL,printabc,NULL);
    //pthread_detach(tid);
    return 0;
}
