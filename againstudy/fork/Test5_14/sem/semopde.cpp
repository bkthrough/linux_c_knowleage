#include"../utili.h"

int main(int argc, char *argv[])
{
    key_t key_id = ftok(argv[1],0xFF);
    key_t sem_id = semget(key_id,0,0);
    
    struct sembuf p;
    p.sem_num = 0;
    p.sem_op = -1;
    p.sem_flg = 0;
    
    int res = semop(sem_id, &p, 1); 
    if(res == -1) 
    {   
        printf("operator sem decrement fail.\n");
    }   
    printf("operator sem decrement  ok.\n");                                                      
    return 0;
}    

