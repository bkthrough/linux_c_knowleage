#include <iostream>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define SERPORT 8888
int init(void)
{
    int sockfd = 0;
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        perror("socket");
    }
    //224和服务器发过去的端口和自己bind
    cliaddr.sin_port = htons(SERPORT);
    cliaddr.sin_addr.s_addr = inet_addr("224.0.0.1");
    cliaddr.sin_family = AF_INET;
    int yes = 1;
    if(0 > setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)))
        perror("sersockopt");
    if(0 > bind(sockfd, (struct sockaddr *)&cliaddr, len))
        perror("bind");
    struct ip_mreq mul;
    mul.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    mul.imr_interface.s_addr = htonl(INADDR_ANY);
    //if(0 > setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mul, sizeof(mul)))
    //    perror("set zubo");

    return sockfd;
}
void start(int sockfd)
{
    char buf[256];
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(seraddr);

    while(1)
    {
        recvfrom(sockfd, buf, 256, 0, (struct sockaddr *)&seraddr, &len);
        if(strncmp(buf, "quit", 4) == 0){
            break;
        }else
            cout << buf;
    }
    close(sockfd);
}
int main()
{
    int sockfd = 0;

    sockfd = init();
    start(sockfd);

    return 0;
}
