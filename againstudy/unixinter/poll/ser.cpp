#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>

#define OPEN_SIZE  10
#define IP   "127.0.0.1"
#define PORT (8888)
int sock_bind(const char *ip, short port)
{
    int sockfd = 0;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(struct sockaddr_in);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("socket");
        exit(1);
    }
    seraddr.sin_addr.s_addr = inet_addr(ip);
    seraddr.sin_port = htons(port);
    seraddr.sin_family = AF_INET;
    if(0 > bind(sockfd, (struct sockaddr *)&seraddr, len)){
        perror("bind");
        close(sockfd);
    }

    return sockfd;
}

void do_work(pollfd *clientfds, int num)
{
    char buf[256] = {0};

    for(int i = 1; i <= num; ++i){
        if(clientfds[i].fd == -1)
            continue;
        if(clientfds[i].revents & POLLIN){
            read(clientfds[i].fd, buf, 256);
            printf("%s\n", buf);
            write(clientfds[i].fd, buf, strlen(buf)+1);
        }
    }
}

void do_poll(int sockfd)
{
    pollfd clientfds[OPEN_SIZE];
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(struct sockaddr);
    int readyn;
    int num = 0;
    int i = 0;

    clientfds[0].fd = sockfd;
    clientfds[0].events = POLLIN;

    for(i = 1; i < OPEN_SIZE; ++i){
        clientfds[i].fd = -1;
    }
    for(;;){
        readyn = poll(clientfds, num+1, -1);
        if(readyn == -1){
            perror("readyn");
            exit(1);
        }
        else if(clientfds[0].revents & POLLIN){
            int connfd = 0;
            connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
            if(connfd < 0){
                perror("accept");
                exit(1);
            }

            for(i = 1; i < OPEN_SIZE; ++i){
                if(clientfds[i].fd < 0){
                    clientfds[i].fd = connfd;
                    break;
                }
            }
            if(i == OPEN_SIZE){
                printf("full.\n");
                continue;
            }
            clientfds[i].events = POLLIN;
            num = i > num ? i : num;
        }
        do_work(clientfds, num);
    }
}
int main(int argc, char *argv[])
{
    int sockfd = sock_bind(IP, PORT);
    listen(sockfd, 5);
    do_poll(sockfd);

    return 0;
}
