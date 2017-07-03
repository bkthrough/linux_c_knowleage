#include <apue.h>

int main()
{
    int run = 1;

    fork() && fork() || fork();
    //fork() , fork();

    while(run){
        //printf("Who am I %d\n",getpid());
        sleep(1);
    }

    return 0;
}
