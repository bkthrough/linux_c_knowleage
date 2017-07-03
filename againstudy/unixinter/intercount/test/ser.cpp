#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAX_LEN 256
#define SERPORT 8888
int init()
{
    int sockfd = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        perror("socket");
        exit(1);
    }

    return sockfd;
}

void start(int sockfd)
{
    char sendbuf[MAX_LEN] = {0};
    struct sockaddr_in seraddr;

    seraddr.sin_port = htons(SERPORT);
    seraddr.sin_addr.s_addr = inet_addr("224.0.0.1");
    seraddr.sin_family = AF_INET;
    while(1)
    {
        read(fileno(stdin), sendbuf, MAX_LEN);
        int len = sendto(sockfd, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr *)&seraddr, sizeof(seraddr));
        if(len < 0)
            cout << "send msg error.\n";
        if(strncmp(sendbuf, "quit", 4) == 0)
            break;
    }
    close(sockfd);
}
int main()
{
    int sockfd;

    sockfd = init();
    start(sockfd);

    return 0;
}
