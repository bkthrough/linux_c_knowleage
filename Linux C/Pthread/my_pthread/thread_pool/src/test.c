#include <apue.h>
#include "pthread_pool.h"

typedef void *(*Func)(void *);
void *print(void *addr)
{
    char *str;

    str = malloc(10);
    memcpy((void *)str,addr,10);
        printf("---------------------------------\n");
        printf("%s\n",str);

    return NULL;
}
void *print1(void *addr)
{
    char *str;

    str = malloc(10);
    memcpy((void *)str,addr,10);
        printf("---------------------------------\n");
        printf("%s\n",str);
        sleep(2);

    return NULL;
}
void *print2(void *addr)
{
    char *str;

    str = malloc(10);
    memcpy((void *)str,addr,10);
        printf("---------------------------------\n");
        printf("%s\n",str);
        sleep(2);

    return NULL;
}
void *print3(void *addr)
{
    char *str;

    str = malloc(10);
    memcpy((void *)str,addr,10);
        printf("---------------------------------\n");
        printf("%s\n",str);
        sleep(2);

    return NULL;
}
int main(int argc,char *argv[])
{
    int i;
    char *str = "helloworld";
    char *str1 = "i'm cool";
    char *str2 = "wonderful";
    char *str3 = "man";

    if(1 >= argc){
        printf("para error\n");
        return 1;
    }
    i = atoi(argv[1]);
    if(FALSE == pthread_pool_create(i)){
        //error
        printf("create error\n");
        exit(1);
    }else{
        printf("create ok\n");
    }
    if(FALSE == pthread_pool_mission(print,(void *)str)){
        //error
        printf("mission error\n");
        exit(1);
    }else{
        printf("mission ok\n");
    }
    sleep(2);
    printf("%p\n",print1);
    if(FALSE == pthread_pool_mission(print1,(void *)str1)){
        //error
        printf("mission error\n");
        exit(1);
    }else{
        printf("mission ok\n");
    }
    sleep(2);
    if(FALSE == pthread_pool_mission(print2,(void *)str2)){
        //error
        printf("mission error\n");
    }else{
        printf("mission ok\n");
    }
    if(FALSE == pthread_pool_mission(print3,(void *)str3)){
        //error
        printf("mission error\n");
    }else{
        printf("mission ok\n");
    }
    sleep(1);
    if(FALSE == pthread_pool_end()){
        //error
        printf("end error\n");
    }else{
        printf("end ok\n");
    }

    return 0;
}
