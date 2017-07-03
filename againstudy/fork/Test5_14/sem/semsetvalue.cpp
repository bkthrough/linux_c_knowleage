#include"../utili.h"

union semun
{   
    int val;            /* value for SETVAL */
    struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
    unsigned short *array;  /* array for GETALL & SETALL */
    struct seminfo *__buf;  /* buffer for IPC_INFO */
    void *__pad;
}; 

int main(int argc, char *argv[])
{
    key_t key_id;
    key_id = ftok(argv[1], 0xFF);
    key_t sem_id;
    sem_id = semget(key_id, 0, 0);
    if(sem_id == -1)
    {
        printf("get sem fail.\n");
        exit(1);
    }

    union semun init;
    init.val = atoi(argv[2]);
    int res = semctl(sem_id, 0, SETVAL, init);
    if(res == -1)
    {
        printf("set sem value fail.\n");
        exit(1);
    }
    printf("set sem value ok.\n");

    return 0;
}
