#include <apue.h>

#define PMAX  64

pid_t  pids[PMAX];

typedef void (*PFunc)(void * );


int make_process(int num)
{
    int loop = 0;
    pid_t chid;

    if(0 > num || PMAX < num){
        return NG;
    }
    for(loop=0;loop<num;++loop){
        chid = fork();
        if(0 > chid){
        //error
        }else if(0 == chid){
            //pause();
            printf("child born\n");
            exit(0);
        }else{
            pids[loop] = chid;
        }
    }//end for
}

int main()
{
    make_process(3);
    pause();
    return 0;
}
