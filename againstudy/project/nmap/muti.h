#pragma once
#include <apue.h>
#include <iostream>
using namespace std;

//一个线程处理几个端口
#define DO_NUM  (10)

int fd;
int maxP;
int minP;
struct sockaddr_in seraddr;
socklen_t len = sizeof(struct sockaddr);
void *p_proc(void *arg)
{
    int start = (*(int *)arg * 10) + minP;
    int end = (start+10) < maxP ? (start+10) : maxP;
    struct servent *sptr;

    for(int i = start; i <= end; ++i){
        seraddr.sin_port = htons(i);
        if(0 > connect(fd, (struct sockaddr *)&seraddr, len)){
            printf("port:%d | status closed\n", ntohs(seraddr.sin_port));
        }
        else{
            sptr = getservbyport(seraddr.sin_port, "tcp");
            if(sptr == NULL)
                printf("port:%d | status opening!!!!!!!!\n", ntohs(seraddr.sin_port));
            else
                printf("port:%d | service is %s | status opening!!!!!!!!\n", ntohs(seraddr.sin_port), sptr->s_name);
        }
    }
    pthread_exit(NULL);
}
void deal_with_muti(char *ip, int minport, int maxport)
{
    int sockfd;
    int num;
    pthread_t *tid;
    int *array;

    num = (maxport - minport) / 10 + 1;
    array = new int[num];
    maxP = maxport;
    minP = minport;
    tid = new pthread_t[num];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    fd = sockfd;
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr(ip);
    for(int i = 0; i < num; ++i){
        array[i] = i;
        pthread_create(&tid[i], NULL, p_proc, &array[i]);
        //只能在一个线程跑完再跑另一个线程，因为他们不能共用一个sockfd
        pthread_join(tid[i], NULL);
    }
}
