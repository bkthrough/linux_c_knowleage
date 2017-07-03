#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id = ftok(argv[1],0xFF);
    key_t sem_id = semget(key_id,0,0);
    struct sembuf v;
    v.sem_num = 0;
    v.sem_op = 0;
    v.sem_flg = 0;

    int res = semop(sem_id, &v, 1);
    if(res == -1)
    {
        printf("operator sem increment fail.\n");
    }
    printf("operator sem increment ok.\n");
    return 0;
}    
