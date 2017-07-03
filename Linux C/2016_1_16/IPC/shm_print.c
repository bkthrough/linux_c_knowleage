#include <apue.h>

#define ADDR (0xabcd0001)
int get_shmid(char *str)
{
    key_t key;

    key = strtol(str,NULL,0);

    return shmget(key,0,0);
}
void *get_start_addr(char *str)
{
    int shmid = 0;
    int result = 0;
    int a = 10;

    //result = strtol(str,NULL,16);
    shmid = get_shmid(str);
    if(shmid == 0){
        return NULL;
    }
    return shmat(shmid,NULL,0);
}

void print(void *shmaddr,int shmid)
{
    int i = 0;
    int j = 0;
    int k = 0;
    size_t size = 0;
    unsigned char *start_addr = (unsigned char *)shmaddr;
    struct shmid_ds sd;

    shmctl(shmid,IPC_STAT,&sd);
    size = sd.shm_segsz;
    while(size){
        if(i == 0){
            printf("0x%03d0\t",j);
        }
        while(i < 16){
            if(*start_addr){
                printf("%01x",*start_addr);
                start_addr++;
                i++;
            }
            else{
                printf("00");
                start_addr++;
                i++;
            }
            k++;
            if(k == 4){
                printf(" ");
                k = 0;
            }
            size--;
            if(size == 0){
                break;
            }
        }
        printf("\n");
        i = 0;
        j++;
    }
}
int main(int argc,char *argv[])
{
    char *shmaddr = NULL;
    int shmid = 0;

    if(1 > argc){
        printf("error\n");
        return 1;
    }
    shmid = get_shmid(argv[1]);
    shmaddr = get_start_addr(argv[1]);
    print(shmaddr,shmid);

    return 0;
}
