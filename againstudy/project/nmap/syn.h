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
using namespace std;


int maxp = 0;
void *p_fun(void *arg)
{
    struct sockaddr_in *in1;
    char *srcaddr;
    int loopend;
    int size;
    u_char readbuf[1600];
    struct sockaddr_in from;
    socklen_t from_len;
    struct tcphdr *tcp;
    struct servent *sptr;
    tcp = (struct tcphdr *)(readbuf+20);
    int fd = *((int *)arg);

    for(;;){
        memset(readbuf, 0, 1600);
        //为什么发送的也能接收到
        size = recvfrom(fd, (char *)readbuf, 1600, 0, (struct sockaddr *)&from, &from_len);
        //如果小于40说明接收有误
        if(size < 40)
            continue;
        //接收刚刚发送的数据
        if((ntohl(tcp->ack_seq) == 12345))
            continue;
        //接收到rst说明对端关闭
        if(tcp->rst && tcp->ack){
            printf("port:%d | status:closed\n", htons(tcp->source));
        }
        //接受到ack和syn说明对端开启
        if(tcp->ack && tcp->syn){
            in1 = (struct sockaddr_in *)&from;
            srcaddr = inet_ntoa(in1->sin_addr);
            if((sptr = getservbyport(tcp->source, "tcp")) != NULL){
                printf("port:%d | server:%s | status:open！\n", htons(tcp->source), sptr->s_name);
            }else
                printf("port:%d | status open!\n", htons(tcp->source));
        }
        if(htons(tcp->source) == maxp){
            break;
        }
    }
    pthread_exit(NULL);
}
//addr指向16个字的空间
//用反码相加发累加所有16位字
//最后，对计算结果取反，作为tcp校验和
unsigned short checksum(unsigned short *addr, int len)
{
    int nleft = len;
    int sum = 0;
    unsigned short *w = addr;
    unsigned short answer = 0;

    while(nleft > 1){
        sum += *w++;
        nleft -= 2;
    }

    //如果总长度是奇数，那么最后加一个0的字节
    if(nleft == 1){
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }

    //高16位和低16位反复相加，直到高16位为0.
    //只需要加两次就可以，举个例子，两者都是0xffff相加也只不过是0x1fffe 也就是说
    //0xfffe + 0x1 -》0xffff 高位就不可能有值了
    //累加sum的高16位和低16位
    sum = (sum >> 16) + (sum & 0xffff);
    //将进位到高位的16bit再相加
    sum += (sum >> 16);
    //取反
    answer = ~sum;
    return (answer);
}

int sendsyn(int sockfd, u_long sourceIP, struct sockaddr_in *addr)
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
    tcp->dest = addr->sin_port;
    tcp->seq = htonl(12345);
    tcp->ack_seq = 0;
    tcp->doff = 5;
    tcp->syn = 1;
    tcp->window = htons(10052);
    tcp->check = 0;
    tcp->urg_ptr = 0;
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
void synscan(char *ip, int minport, int maxport)
{
    pthread_t tid;
    struct ifreq if_data;
    int sockfd;
    u_int addr_p;
    char *addr;
    struct sockaddr_in cliaddr;
    struct sockaddr_in myaddr;
    socklen_t len = sizeof(myaddr);

    maxp = maxport;
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(sockfd == -1){
        perror("socket");
        exit(1);
    }
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
    pthread_create(&tid, NULL, p_fun, (void *)&sockfd);
    for(int i = minport; i <= maxport; ++i){
        cliaddr.sin_port = htons(i);
        if(0 > sendsyn(sockfd, addr_p, &cliaddr)){
            perror("send error");
        }
    }
    pthread_join(tid, NULL);
}
