#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id,sem_id;
    key_id = ftok(argv[1],0xFF);
    sem_id = semget(key_id, 0, 0);
    semctl(sem_id, 0, IPC_RMID);
    printf("Remove sem ok, sem id=%d\n",sem_id);
    return 0;
}
