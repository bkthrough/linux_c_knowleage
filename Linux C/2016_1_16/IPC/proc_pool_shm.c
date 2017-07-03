#include <apue.h>

#define SHMKEY_MAIN_NET   0xabcd0001

#define POOLMAX           128
#define IDLE              0
#define BUSY              1

#define SIG_WAKEUP        SIGUSR1
#define SIG_END           SIGUSR2

//进程信息
typedef struct procinfo{
    pid_t  pid;
    int    isbusy;
}_procinfo ;

//进程池
typedef struct pool_ctl {
    //共享内存id
    int       shmid  ;
    //进程池内进程个数
    int       procnum;
    _procinfo *info  ;
}_pool_ctl;

_pool_ctl * pctl;
int poolrun = 1;

//handler函数，唤醒进程
void _sig_wake(int sig)
{
    //just wake up
}

//给进程循环条件置0,结束进程
void _sig_end(int sig)
{
    poolrun = 0;
}

//初始化共享内存
//返回值是为了查看是否成功
//地址是传给了maddr
void *shm_init(key_t key,void ** maddr,size_t size)
{
    int   shmid = -1;
    void *addr = NULL;

    if(NULL == maddr){
        return NULL;
    }
    if(0 < size){
        //如果size大于0,那么就创建这个共享内存
        shmid = shmget(key,size,IPC_CREAT|0666);
    }else{
        //size等于0。直接得到shmid值
        shmid = shmget(key,0,0);
    }
    if(0 > shmid){
        return NULL;
    }

    //得到内存的地址
    addr = shmat(shmid,NULL,0);
    *maddr = addr;
    if(maddr){
        memset(maddr,0x00,size);
    }
    return addr;
}

//做池子
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

            pctl = (_pool_ctl *)shm_init(SHMKEY_MAIN_NET,(void **)&pctl,0);
            if(NULL == pctl){
                exit(0);
            }
            //很精巧：控制结构体加1得到子结构体
            myinfo = (_procinfo *)(pctl + 1) + loop;
            printf("child born [%d]\n",getpid());
            while(poolrun){
                pause();
                myinfo->isbusy = BUSY;
                printf("%d I'm working\n",myinfo->pid);
                myinfo->isbusy = IDLE;
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
   while(poolrun){
       index = (index + 1 )% pctl->procnum;
       kill(pctl->info[index].pid,SIG_WAKEUP);
       sleep(1);
   }
   if(0 >= pctl->procnum){
       printf("No sons\n");
       return;
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
}

int main(int ac,char **av)
{
    int pnum = 0;
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
             sizeof(_pool_ctl) + pnum * sizeof(_procinfo));
    if(NULL == pctl){
        printf("shm_init error\n");
        return 3;
    }
    pctl->info = (_procinfo *)((char *)pctl + sizeof(_pool_ctl));
    pctl->procnum = pnum;

    _proc_start();
    rst = make_pool(pctl);
    if(OK == rst){
        do_serv(pctl);
    }
    return 0;
}
