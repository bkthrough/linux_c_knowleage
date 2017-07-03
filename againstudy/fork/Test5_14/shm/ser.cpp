#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id;
    key_id = ftok(argv[1], ID);
    if(key_id == -1)
    {
        printf("ftok error.\n");
        exit(1);
    }
    printf("key_id = 0x%x\n", key_id);

    key_t shm_id;
    shm_id = shmget(key_id, 1024, IPC_CREAT|IPC_EXCL|0666);
    if(shm_id == -1)
    {
        printf("shmget error.\n");
        exit(1);
    }


    char *addr;
    addr = (char *)shmat(shm_id,NULL, 0);
    if(addr == (void*)-1)
    {
        printf("shmat error.\n");
        shmctl(shm_id, IPC_RMID, NULL);
        exit(1);
    }
    while(1)
    {
        //write
        printf("Ser:>");
        scanf("%s",addr);
        if(strcmp(addr,"quit") == 0)
        {
            shmctl(shm_id, IPC_RMID, NULL);
            break;
        }

        //read
        printf("Cli:>%s\n",addr);
    }
    return 0;
}

















