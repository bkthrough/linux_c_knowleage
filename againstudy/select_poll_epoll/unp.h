#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<sys/epoll.h>

#define IPADDR  "127.0.0.1"
#define PORT    8787
#define MAXLINE 1024
#define LISTENQ 5

//select
#define SIZE 10

