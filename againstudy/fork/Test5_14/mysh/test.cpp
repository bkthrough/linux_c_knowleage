#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <exception>
using namespace std;

#define ID  0x11
#define ID1 0x22
void sig_chld(int sig)
{
    int status;
    wait(&status);
}
int main(int ac, char *av[])
{
    key_t key_id;
    key_t key_id1;
    key_t shm_key;
    key_t sem_key;
    pid_t chid = 0;

    key_id = ftok(av[1], ID);
    key_id1 = ftok(av[1], ID1);
    if(key_id == -1 || key_id1 == -1){
        cout << "ftok erorr" << endl;
        exit(1);
    }
    shm_key = shmget(key_id, 1024, IPC_CREAT | IPC_EXCL | 0666);
    if(shm_key == -1){
        cout << "shmget error" << endl;
        exit(1);
    }
    sem_key = semget(key_id1, 2, IPC_CREAT | IPC_EXCL | 0666);
    if(sem_key == -1){
        cout << "shmget error" << endl;
        exit(1);
    }
    char *addr;
    addr = (char *)shmat(shm_key, NULL, 0);
    if(addr == (void *)-1){
        cout << "shmat error" << endl;
        exit(1);
    }
    struct sembuf v = {0, 1, 0};
    struct sembuf p = {0, -1, 0};
    struct sembuf v1 = {1, 1, 0};
    struct sembuf p1 = {1, -1, 0};
    //semctl(sem_key, 0, SETVAL, 1);
    if(0 > (chid = fork())){
        cout << "fork error" << endl;
        exit(1);
    }else if(chid == 0){
        while(1){
            //addr = (char *)shmat(shm_key, NULL, 0);
            semop(sem_key, &p1, 1);
            cout << addr << endl;
            semop(sem_key, &v, 1);
            scanf("%s", addr);
            if(strncmp(addr, "quit", 4) == 0){
                cout << "quit" << endl;
                exit(0);
            }
        }
    }else{
        while(1){
            semop(sem_key, &v1, 1);
            scanf("%s", addr);
            if(strncmp(addr, "quit", 4) == 0){
                cout << "quit" << endl;
                exit(0);
            }
            semop(sem_key, &p, 1);
            cout << addr << endl;
            signal(SIGCHLD, sig_chld);
        }
    }

    return 0;
}
