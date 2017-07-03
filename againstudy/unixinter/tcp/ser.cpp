#include<iostream>
#include<apue.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
using namespace std;

#define SERVER_PORT  5050
#define SERVER_IP    "127.0.0.1"
#define QUEUE_SIZE   5

int runfd;
socklen_t len = sizeof(struct sockaddr);
struct sockaddr_in cliaddr;
struct Arg
{
    pthread_cond_t read_cond;
    int            sockfd;
};
void sig_chld(int sig)
{
    exit(0);
}
void *p_fun1(void *arg)
{
    int sockfd = (*(struct Arg*)arg).sockfd;
    pthread_cond_t read_cond = (*(struct Arg *)arg).read_cond;

    while(1){
        char buf[256] = {0};
        memset(buf, 0x00, strlen(buf));
        read(sockfd, buf, 256);
        runfd = sockfd;
        if(strncmp(buf, "quit", 4) == 0){
            printf("termination\n");
            break;
        }
        printf("cli:<< :%s",buf);
    }
    pthread_exit(NULL);
}
void *p_fun2(void *arg)
{
    char buf[256] = {0};

    while(1)
    {
        if(0 < read(fileno(stdin), buf, 256)){
            send(runfd, buf, strlen(buf)+1, 0);
            if(strncmp(buf, "quit", 4) == 0){
                printf("get term.\n");
                break;
            }
        }
    }
    pthread_exit(NULL);
}
int main(int argc, char *argv[])
{
    int sockSer;
    int chld = 0;
    sockSer = socket(AF_INET, SOCK_STREAM, 0);
    if(sockSer == -1)
        perror("socket");

    int yes = 1;
    setsockopt(sockSer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    struct sockaddr_in addrSer, addrCli;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(SERVER_PORT);
    addrSer.sin_addr.s_addr = inet_addr(SERVER_IP);

    socklen_t addrlen = sizeof(struct sockaddr);
    int res = bind(sockSer, (struct sockaddr*)&addrSer, addrlen);
    if(res == -1)
        perror("bind");

    listen(sockSer, QUEUE_SIZE);

    printf("Server Wait Client Connect.......\n");
    int sockConn;
    {
        pthread_t tid;
        pthread_create(&tid, NULL, p_fun2, NULL);
    }
    while(1){
        sockConn = accept(sockSer,(struct sockaddr*)&addrCli, &addrlen);
        if(sockConn == -1)
            perror("accept");
        else{
            printf("accept success.\n");
        }

        pthread_t tid;
        char sendbuf[256];
        char recvbuf[256];
        char buf[256] = {0};
        struct Arg arg;
        pthread_cond_t cond;

        arg.sockfd = sockConn;
        pthread_create(&tid, NULL, p_fun1, &arg);
    }

    close(sockConn);
    close(sockSer);
    return 0;
}
