#include <apue.h>

int run = 1;

int main(void)
{
    pid_t chid;
    chid = fork();
    if(0 > chid){
       logerr("fork error\n");
       return 1;
    }else if(0 == chid){
    //child space
        int count = 0;
        while(run){
            printf("I'm child,%d,%d\n",chid,getpid());
            if(++count > 2){
                run = 0;
            }
            sleep(1);
        }
        fork();
        printf("count:%d\n",count);
        exit(0); // son process should be quit
    }else{
    //father space
        int count = 0;
        while(run){
            printf("father running {child:%d,self:%d}\n",chid,getpid());
            if(count++ > 5){
                run = 0;
            }
            sleep(1);
        }
    }

    printf("Process end %d\n",getpid());
    return 0;
}
