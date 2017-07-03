#include <apue.h>

#define SIG_WAKE  SIGUSR1
#define SIG_END   SIGUSR2
#define SHMKEY_MAIN_NET (0x01010101)
#define BUSY  (0)
#define IDLE  (1)

typedef struct procinfo{
    pid_t pid;
    int   flag;
}_procinfo;

typedef struct pool_ctl{
    int shmid;
    int procnum;
    _procinfo *info;
}_pool_ctl;

_pool_ctl *pctl;
int run = 1;

/////////////////////////////////////////////////////////////
void _sig_wake(int sig)
{
    //continue
}

void _sig_end(int sig)
{
    run = 0;
}

void *shm_init(key_t key,void **maddr,size_t size)
{
    int shmid = -1;
    void *addr = NULL;

    if(NULL == maddr){
        return NULL;
    }
    if(0 < size){
        shmid = shmget(key,size,IPC_CREAT|0644);
    }else{
        shmid = shmget(key,0,0);
    }
    if(0 > shmid){
        return NULL;
    }

    addr = shmat(shmid,NULL,0);

    //can't understand
    *maddr = addr;
    if(maddr){
        bzero(maddr,size);
    }
    return addr;
}

int do_pool(_pool_ctl *ctl)
{
    pid_t pid;
    int loop = 0;
    int chid = -1;
    int rst = OK;
    if(NULL == pctl){
        return NG;
    }
    for(loop = 0; loop < pctl->procnum; ++loop){
        chid = fork();
        if(0 > chid){
            rst = NG;
            break;
        }else if(0 == chid){
            _procinfo *myinfo = NULL;
            //get pctl's addr
            pctl = (_pool_ctl *)shm_init(SHMKEY_MAIN_NET,(void **)&pctl,0);
            printf("%s\n",pctl);
            if(NULL == pctl){
                exit(0);
            }
            myinfo =(_procinfo *)(pctl + 1) + loop;
            printf("child born id is %d\n",getpid());
            while(run){
                pause();
                myinfo->flag = BUSY;
                printf("%d is busy\n",myinfo->pid);
                myinfo->flag = IDLE;
            }
            _exit(0);
        }else{
            pctl->info[loop].pid = chid;
        }
    }

    return rst;
}

void do_server(_pool_ctl *ctl)
{
    int index = 0;

    while(run){
        index = (index + 1) % pctl->procnum;
        printf("%d\n",index);
        kill(pctl->info[index].pid,SIG_WAKE);
        sleep(1);
    }
    if(0 >= pctl->procnum){
        printf("no child\n");
        return ;
    }
    for(index = 0; index < pctl->procnum; ++index){
        kill(pctl->info[index].pid,SIG_END);
    }
    index = 0;
    while(index < pctl->procnum){
        wait(NULL);
        index++;
    }
}

int main(int argc,char *argv[])
{
    int pnum = 0;
    int rst = NG;
    if(1 >= argc){
        return 1;
    }
    pnum = atoi(argv[1]);

    signal(SIG_WAKE,_sig_wake);
    signal(SIG_END,_sig_end);

    pctl = shm_init(SHMKEY_MAIN_NET,(void **)&pctl,
                    sizeof(_pool_ctl) + pnum * sizeof(_pool_ctl));
    pctl->info = (_procinfo *)((char *)pctl + sizeof(_pool_ctl));
    pctl->procnum = pnum;

    rst = do_pool(pctl);
    printf("%d\n",rst);
    if(OK == rst){
        printf("kill sig\n");
        do_server(pctl);
    }

    return 0;
}
