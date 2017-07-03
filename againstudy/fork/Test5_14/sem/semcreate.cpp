#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id;
    key_id = ftok(argv[1], 0xFF);
    if(key_id == -1)
    {
        printf("ftok error.\n");
        exit(1);
    }

    key_t sem_id;
    sem_id = semget(key_id, 1, IPC_CREAT|IPC_EXCL|0666);
    if(sem_id == -1)
    {
        printf("semget error.\n");
        exit(1);
    }
    printf("create sem ok, sem_id = %d\n",sem_id);
    return 0;
}
