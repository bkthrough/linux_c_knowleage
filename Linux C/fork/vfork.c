#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[],char *envp[])
{
    int chid = -1;
    int rst = -1;
    char *const arg[] = {"ls",NULL};

    arg = 0x01;
    chid = fork();
    if(0 > chid){
        //error
    }else if(0 == chid){
        rst = execv("/bin/ls",arg);

        if(-1 == rst){
            //error
        }
        exit(0);
    }else{
        sleep(6);
    }

    return 0;
}
