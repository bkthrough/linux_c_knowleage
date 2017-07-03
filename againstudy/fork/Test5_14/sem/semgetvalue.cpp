#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id;
    key_id = ftok(argv[1],0xFF);
    key_t sem_id;
    sem_id = semget(key_id, 0, 0);
    int sem = semctl(sem_id, 0, GETVAL);
    printf("sem value = %d\n",sem);
    return 0;
}
