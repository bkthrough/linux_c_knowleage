#include <apue.h>

int main(int ac,char **av,char *env[])
{
    pid_t chid = -1;
    int  psint = 0 ;

    chid = vfork();
    if(0 > chid){
    //error
    }else if(0 == chid){
        sleep(5);
        psint = getpid();
        printf("child exit\n");
        exit(0);
    }else{
        printf("parent %d,%d\n",chid,psint); 
    }
    system("pstree -ap | grep pro_vfork");
    sleep(10);
    psint = wait(NULL);
    printf("------------%d-------------------\n",psint);
    system("pstree -ap | grep pro_vfork");
    sleep(10);
    return 0;
}
