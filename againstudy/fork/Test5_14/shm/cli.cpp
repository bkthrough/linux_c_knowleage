#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id = ftok(argv[1],ID);
    if(key_id == -1)
    {
        printf("ftk error.\n");
        exit(1);
    }

    key_t shm_id = shmget(key_id,0,0);
    if(shm_id == -1)
    {
        printf("shmget error.\n");
        exit(1);
    }

    char *addr = (char *)shmat(shm_id,NULL,0);
    if(addr == (void *)-1)
    {
        printf("shmat error.\n");
        exit(1);
    }

    while(1)
    {
        printf("Ser:>%s\n",addr);

        printf("Cli:>");
        scanf("%s",addr);
        if(strcmp(addr,"quit") == 0)
        {
            break;
        }
    }
    return 0;
}


