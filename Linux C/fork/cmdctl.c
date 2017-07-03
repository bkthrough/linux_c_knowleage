#include <apue.h>

#define CLEN       512
#define SEPA       '@'

#define START      1
#define STOP       2
#define STATUS     4
#define RESTART    8
#define FORCE_STOP 16

#define OPTSTART   "start"
#define OPTSTOP    "stop"
#define OPTSTATUS  "status"
#define OPTRESTART "restart"

enum {CMD=0,OPT,PRO};

int background = 0;

void usage(char *cmd)
{
    printf("Usage : %s <%s|%s|%s|%s> <program>\n",cmd,
           OPTSTART,OPTSTOP,OPTSTATUS,OPTRESTART);
}

int get_sepa(char *sa)
{
    int len = 0;
    if(NULL == sa)
        return 0;
    len = strlen(sa);
    if(SEPA == sa[len-1]){
        return 1;
    }
    return 0;
}

int whattodo(char *what)
{
    int ctl = 0;
    if(NULL == what){
        ctl = 0;
    }else if(!strcmp(what,OPTSTART)){
        ctl = START ;
    }else if(!strcmp(what,OPTSTOP)){
        ctl = STOP  ;
    }else if(!strcmp(what,OPTSTATUS)){
        ctl = STATUS;
    }else if(!strcmp(what,OPTRESTART)){
        ctl = RESTART;
    }
    return ctl;
}

int isrun(int ac,char **av,char *pro)
{
    int   id = 0,len,num;
    char  cmd[CLEN];
    FILE *cmdh;
    if(PRO >= ac){
        return id;
    }
    num = ac-1;
    bzero(pro,CLEN);
    while(num > OPT){
        len = strlen(av[num]);
        if(SEPA != av[num][0]){
            if(SEPA == av[num][len-1]){
                len -= 1;
            }
            memcpy(pro,av[num],len);
            break;
        }
        num--;
    }
    bzero(cmd,CLEN);
    sprintf(cmd,"pidof -s %s",pro);
    //sprintf(cmd,"ps -eo pid,command |grep %s | grep -v grep|grep -v %s |awk \'{print $2}\'",pro,av[0]);
    //sprintf(cmd,"ps aux |grep %s|grep -v grep|head -n 1 ",pro);
    cmdh = popen(cmd,"r");
    if(NULL == cmdh){
        return id; 
    }
    bzero(cmd,CLEN);
    id = fread(cmd,1,CLEN,cmdh);
    if(0 < id){
        id = atoi(cmd);
    }
    pclose(cmdh);

    //printf("%s:%d\n",pro,id);
    return id;
}

void do_start(char *pro,char **arg,char **env)
{
    char  cmd[CLEN];
    pid_t chid;
    if(NULL == pro)
        return;

    chid = vfork();

    if(0 > chid){

    }else if(0 == chid){
        int rst = -1;
        freopen("/dev/null","w",stdout);
        freopen("/dev/null","w",stderr);
        rst = execlp(pro,pro,NULL);
        if(-1 == rst){
            printf("%s not exist.\n",pro);
        }
        _exit(0);
    }else{
        //parent space
    }
    //if(!background){
    //    wait(NULL);
    //}
}

void do_stop(int pid)
{
    char cmd[CLEN];
    FILE *docmd;
    if(0 >= pid){
        return;
    }
    bzero(cmd,CLEN);
    sprintf(cmd,"kill -9 %d",pid);
    docmd = popen(cmd,"r");
    if(NULL == docmd){
        printf("popen error [%d].\n",errno);
    }else{
        pclose(docmd);
    }
}

void do_work(int ac,char **av,char **env)
{
    int  ctl = 0;
    int  pid = 0;
    char pro[CLEN];
    if(PRO >= ac){
        usage(av[0]);
        return;
    }
    background = get_sepa(av[ac-1]);

    ctl = whattodo(av[OPT]);
    pid = isrun(ac,av,pro);

    switch(ctl){
        case START :
            if(0 < pid){
                printf("%s is already started [%d].\n",pro,pid);
            }else{
                do_start(pro,av,env);
                pid = isrun(ac,av,pro);
                if(pid){
                    printf("%s started [%d].\n",pro,pid);
                }
            }
            break;

        case STOP  :
            if(0 < pid){
                do_stop(pid);
                printf("%s stoped.\n",pro);
            }else{
                printf("%s not started.\n",pro);
            }
            break;

        case STATUS:
            if(0 < pid){
                printf("%s is running [%d] .\n",pro,pid);
            }else{
                printf("%s not started .\n",pro);
            }
            break;

        case RESTART :
            if(0 < pid){
                do_stop(pid);
            }
            do_start(pro,av,env);
            pid = isrun(ac,av,pro);
            if(pid){
                printf("%s restarted [%d].\n",pro,pid);
            }
            break;

        default:
            usage(av[0]);
            break;
    }//end switch
    if(!background){
        wait(NULL);
    }
}

int main(int ac,char **av,char **env)
{
    do_work(ac,av,env);
    return 0;
}
