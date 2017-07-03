#include <apue.h>

#define MYPATH  "/usr/bin/gedit"
#define MYPRO   "gedit"

int  main(int ac,char **av,char *envp[])
{
    pid_t chid = -1;

    chid = vfork();
    if(0 > chid){
    //error
    }else if(0 == chid){
        int rst = -1;
        //char *envp[2] = {"HOME=/home",NULL};
        rst = execle(MYPATH,MYPRO,NULL,envp);
        if(-1 == rst){
        //error
        }
        exit(0);
    }else{
        printf("execle excued\n"); 
    }
    return 0;
}


