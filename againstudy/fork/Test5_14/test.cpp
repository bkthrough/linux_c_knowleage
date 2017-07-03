#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdlib.h>

union semun
{
    int val;            /* value for SETVAL */
    struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
    unsigned short *array;  /* array for GETALL & SETALL */
    struct seminfo *__buf;  /* buffer for IPC_INFO */
    void *__pad;
};  
    

int main()
{
    char pathname[] = "mysem";
    key_t key;
    key = ftok(pathname,0xFF);
    if(key == -1)
    {
        printf("ftok error.\n");
        exit(1);
    }

    printf("key id = 0x%x\n",key);

    key_t sem_id;
    sem_id = semget(key, 1, IPC_CREAT|IPC_EXCL|0666);
    if(sem_id == -1)
    {
        printf("semget error.\n");
        exit(1);
    }

    printf("sem id = %d\n",sem_id);

    union semun seminit;
    seminit.val = 1;
    semctl(sem_id,0,SETVAL,seminit);
    int semvalue = semctl(sem_id,0,GETVAL);
    printf("sem value = %d\n",semvalue);

    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op = -2;
    sop.sem_flg = IPC_NOWAIT;

    semop(sem_id, &sop, 1);
    semvalue = semctl(sem_id, 0, GETVAL);
    printf("sem value = %d\n",semvalue);

    int res = semctl(sem_id, 0, IPC_RMID);
    if(res == -1)
    {
        printf("Remove sem Fail!\n");
    }
    else
        printf("Remove sem OK.\n");
    return 0;
}

/*
int main()
{
    char pathname[] = "mykey";
    key_t key1, key2;
    key1 = ftok(pathname, 0xFF);
    key2 = ftok(pathname, 0xFE);
    printf("key1 = 0x%x\n",key1);
    printf("key2 = 0x%x\n",key2);
    return 0;
}

/*
void signal_handler(int sig)
{
    switch(sig)
    {
    case SIGINT:
        printf("catch[%d]SIGINT .\n",sig);
        break;
    case SIGQUIT:
        printf("catch[%d]SIGQUIT .\n",sig);
        break;
    case SIGALRM:
        printf("catch[%d]SIGALRM .\n",sig);
        break;
    case SIGKILL:
        printf("catch[%d]SIGKILL .\n",sig);
        break;
    case SIGSTOP:
        printf("catch[%d]SIGSTOP .\n",sig);
        break;
    default:
        printf("unkown signal.\n");
        break;
    }
}

int main()
{
    signal(SIGINT,signal_handler);    //ctrl+c
    signal(SIGQUIT,signal_handler);   //ctrl + \    
    signal(SIGALRM,signal_handler);   //alarm()
    signal(SIGKILL,signal_handler);   //kill
    signal(SIGSTOP,signal_handler);   //ctrl+z

    int i=0;
    while(1)
    {
        printf("i = %d\n",++i);
        sleep(1);
    }
    return 0;
}

/*
int main()
{
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
       // int i = 0;
        //while(1)
        //{
         //   printf("i = %d\n",++i);
       // }
        printf("This is Child process.\n");
        sleep(10);
        printf("Hello\n");
    }
    else if(pid > 0)
    {
        sleep(2);
        kill(pid,SIGINT);

        int status;
        wait(&status);
    }
    return 0;
}

/*
int main()
{
    alarm(5);
    int i = 0;
    while(1)
    {
        i++;
        printf("i = %d\n",i);
    }
    return 0;
}
*/
