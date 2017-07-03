#include <apue.h>

#define SHMKEY_MAIN_NET   0xabcd0001
#define SEMKEY_MAIN_NET   0xabcdf001

#define POOLMAX           128
#define IDLE              0
#define BUSY              1

#define SIG_WAKEUP        SIGUSR1
#define SIG_END           SIGUSR2

#define _sem_lock(semid,sems)   sem_opr(semid,sems,-1,1)
#define _sem_unlock(semid,sems) sem_opr(semid,sems,1,1)

typedef struct procinfo{
    pid_t  pid;
    int    isbusy;
}_procinfo ;

typedef struct pool_ctl {
    int       shmid  ;
    int       semid  ;
    int       procnum;
    _procinfo *info  ;
}_pool_ctl;

_pool_ctl * pctl;
int poolrun = 1;

void _sig_wake(int sig)
{
    //just wake up
}

void _sig_end(int sig)
{
    poolrun = 0;
    printf("got sig %d\n",getpid());
}

void *shm_init(key_t key,void ** maddr,size_t size,int *shm_id)
{
    int   shmid = -1;
    void *addr = NULL;

    if(NULL == maddr){
        return NULL;
    }
    if(0 < size){
        shmid = shmget(key,size,IPC_CREAT|0666);
    }else{
        shmid = shmget(key,0,0);
    }
    if(0 > shmid){
        return NULL;
    }

    addr = shmat(shmid,NULL,0);
    *maddr = addr;
    if(maddr){
        memset(maddr,0x00,size);
    }
    if(shm_id){
        *shm_id = shmid;
    }
    return addr;
}

int sem_init(key_t key,int nsems,int isinit)
{
    int semid = -1;
    int loop  =  0;

    if(isinit){
        if(0 >= nsems){
           semid = -1;
           goto _END;
        }
        semid = semget(key,nsems,IPC_CREAT|0666); 
        if(0 > semid){
            goto _END;
        }
        for(loop=0;loop<nsems;++loop){
            if(semctl(semid,loop,SETVAL,1)){
                //error
                semctl(semid,0,IPC_RMID);
                semid = -1;
                break;
            }
        }
    }else{
        semid = semget(key,0,0);
    }

_END:
    return semid;
}

int sem_opr(int semid,int semnum,int op,int nsops)
{
    _sembuf *sbuf = NULL;
    int      loop = 0;
    if(1 > nsops){
        return NG;
    }
    sbuf = (_sembuf *)malloc(sizeof(_sembuf)* nsops);
    if(NULL == sbuf){
        return NG;
    }
    for(loop=0;loop<nsops;++loop){
        sbuf[loop].sem_num = semnum + loop;
        sbuf[loop].sem_op  = op;//P : -1 , V : +1
        sbuf[loop].sem_flg = SEM_UNDO;
    }
_LOOP:
    if(-1 == semop(semid,sbuf,nsops)){
        //error
        if(EINTR == errno){
            goto _LOOP;
        }else{
            return NG;
        }
    }

    free(sbuf);
    return OK;
}


int make_pool(_pool_ctl * ctl)
{
    pid_t chid = -1;
    int loop = 0 , rst = OK;
    if(NULL == pctl){
        return NG;
    }
    for(loop=0;loop<pctl->procnum;++loop){
        chid = fork();
        if(0 > chid){
        //error
            rst = NG;
            break;
        }else if(0 == chid){
            _procinfo * myinfo = NULL;

            pctl = (_pool_ctl *)shm_init(SHMKEY_MAIN_NET,(void **)&pctl,0,NULL);
            if(NULL == pctl){
                exit(0);
            }
            myinfo = (_procinfo *)((char *)pctl + sizeof(_pool_ctl)) + loop;
            printf("child born [%d]\n",getpid());
            while(poolrun){
                pause();
                _sem_lock(pctl->semid,loop);   //P
                myinfo->isbusy = BUSY;
                _sem_unlock(pctl->semid,loop); //V

                printf("%d I'm working\n",myinfo->pid);

                _sem_lock(pctl->semid,loop);   //P
                myinfo->isbusy = IDLE;
                _sem_unlock(pctl->semid,loop); //V
            }
            exit(0);
        }else{
            pctl->info[loop].pid = chid;
        }
    }
    return rst;
}

void do_serv(_pool_ctl * ctl)
{
   int index = 0;

   if(0 >= pctl->procnum){
       printf("No sons\n");
       return;
   }
   while(poolrun){
       index = (index + 1 )% pctl->procnum;
       _sem_lock(pctl->semid,index);      //P
       if(BUSY == pctl->info[index].isbusy){
           continue;
       }
       kill(pctl->info[index].pid,SIG_WAKEUP);
       _sem_unlock(pctl->semid,index);   //V
       sleep(1);
   }
   for(index=0;index<pctl->procnum;++index){
       kill(pctl->info[index].pid,SIG_END);
   }
   index = 0 ;
   while(index < pctl->procnum){
       wait(NULL);
       index++ ;
   }
}

void _proc_start()
{
    if(SIG_ERR == signal(SIG_WAKEUP,_sig_wake)){
    //error
    }
    if(SIG_ERR == signal(SIG_END,_sig_end)){
    //error
    }
    if(SIG_ERR == signal(SIGINT,_sig_end)){
    //error
    }
}

void _proc_end()
{
    semctl(pctl->semid,0,IPC_RMID);
    shmctl(pctl->shmid,IPC_RMID,NULL);
}

int main(int ac,char **av)
{
    int pnum = 0 , shmid = -1 , semid = -1;
    int rst = NG;
    if(1 >= ac){
        printf("procnum miss\n");
        return 1;
    }
    pnum = atoi(av[1]);
    if(0 >= pnum || POOLMAX < pnum){
        //out of range
        return 2;
    }

    pctl = shm_init(SHMKEY_MAIN_NET,(void **)&pctl,
             sizeof(_pool_ctl) + pnum * sizeof(_procinfo),&shmid);
    if(NULL == pctl){
        printf("shm_init error\n");
        return 3;
    }
    pctl->info = (_procinfo *)((char *)pctl + sizeof(_pool_ctl));
    pctl->procnum = pnum;
    pctl->shmid = shmid;
    semid = sem_init(SEMKEY_MAIN_NET,pnum,1);
    if(-1 == semid){
        return 4;
    }
    pctl->semid = semid;

    _proc_start();
    rst = make_pool(pctl);
    if(OK == rst){
        do_serv(pctl);
    }

    _proc_end();
    return 0;
}
