#pragma once
#include <apue.h>
#include <iostream>
using namespace std;

void deal_with_all(char *ip, int minport, int maxport)
{
    int sockfd;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(struct sockaddr);
    struct servent *sptr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr(ip);
    for(int i = minport; i <= maxport; ++i){
        seraddr.sin_port = htons(i);
        if(0 >connect(sockfd, (struct sockaddr *)&seraddr, len)){
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
}
