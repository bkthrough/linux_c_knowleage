#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <net/if.h>
#include "syn.h"
using namespace std;

int sendfin(int sockfd, u_long sourceIP, struct sockaddr_in *addr)
{
    unsigned char netPacket[sizeof(struct tcphdr)];
    struct tcphdr *tcp;
    //指向pseudoHead的头，和strcpy中的临时变量作用类似
    u_char *pPseudoHead;
    u_char pseudoHead[12+sizeof(struct tcphdr)];
    u_short tcpHeadLen;

    memset(netPacket, 0, sizeof(struct tcphdr));

    tcpHeadLen = htons(sizeof(struct tcphdr));
    tcp = (struct tcphdr *)netPacket;
    tcp->source = htonl(8888);
    tcp->dest = addr->sin_port;
    tcp->seq = htonl(12345);
    tcp->doff = 5;
    tcp->fin = 1;
    tcp->window = htons(10052);
    pPseudoHead = pseudoHead;

    memset(pPseudoHead, 0, 12+sizeof(struct tcphdr));
    //源ip地址
    memcpy(pPseudoHead, &sourceIP, 4);
    pPseudoHead += 4;

    //目的ip地址
    memcpy(pPseudoHead, &(addr->sin_addr), 4);
    //保留字节（0）
    pPseudoHead += 5;

    //传输层协议号，tcp为6
    memset(pPseudoHead, 6, 1);
    ++pPseudoHead;

    //tcp报文长度（包头+数据）
    memcpy(pPseudoHead, &tcpHeadLen, 2);
    pPseudoHead += 2;

    memcpy(pPseudoHead, tcp, sizeof(struct tcphdr));
    //校验
    tcp->check = checksum((u_short *)pseudoHead, sizeof(struct tcphdr)+12);

    int temp = sendto(sockfd, netPacket, sizeof(struct tcphdr), 0,
                      (struct sockaddr *)addr, sizeof(struct sockaddr));

    return temp;
}
void deal_with_fin(char *ip, int minport, int maxport)
{
    pthread_t tid;
    struct ifreq if_data;
    int sockfd;
    u_int addr_p;
    char *addr;
    struct sockaddr_in cliaddr;
    struct sockaddr_in myaddr;
    struct sockaddr_in from;
    socklen_t len = sizeof(myaddr);
    u_char readbuf[1600];
    socklen_t from_len;
    struct tcphdr *tcp;
    struct servent *sptr;
    tcp = (struct tcphdr *)(readbuf+20);
    int loopend;
    int size;
    clock_t start, end;
    struct timeval tv;

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(sockfd == -1){
        perror("socket");
        exit(1);
    }
    //设置超时时间
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int res = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    getsockname(sockfd, (struct sockaddr *)&myaddr, &len);

    strcpy(if_data.ifr_name, "lo");
    if(ioctl(sockfd, SIOCGIFADDR, &if_data) < 0){
        perror("ioctl");
        exit(1);
    }
    memcpy((void *)&addr_p, ((char *)(&if_data.ifr_addr.sa_data)+2), 4);
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr(ip);
    for(int i = minport; i <= maxport; ++i){
        cliaddr.sin_port = htons(i);
        if(0 > sendfin(sockfd, addr_p, &cliaddr)){
            perror("send error");
        }
        for(;;){
            memset(readbuf, 0, 1600);
            size = recvfrom(sockfd, (char *)readbuf, 1600, 0, (struct sockaddr *)&from, &from_len);
            //又收到了刚刚发送的包
            if(tcp->fin == 1){
                continue;
            }
            if(tcp->rst){
                printf("port:%d | status:closed\n", htons(tcp->source));
                break;
            }
            //超时，则判定为开启状态
            if(size < 0){
                printf("port:%d | status:opening\n", i);
                break;
            }
            //其他情况则判定重新接受
            else{
                continue;
            }
        }
    }
}
