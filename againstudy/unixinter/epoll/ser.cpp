#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

#define IP "127.0.0.1"
#define PORT 8888

void add_event(int epollfd, int fd, int event)
{
    epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}
void modify_event(int epollfd, int fd, int event)
{
    epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}
void delete_event(int epollfd, int fd, int event)
{
    epoll_event ev;
    ev.events = event;
    ev.data.fd = fd;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}
int init_sock()
{
    int sockfd;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(seraddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_addr.s_addr = inet_addr(IP);
    seraddr.sin_port = htons(PORT);
    seraddr.sin_family = AF_INET;
    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if(0 > bind(sockfd, (struct sockaddr *)&seraddr, len)){
        perror("bind");
        exit(1);
    }
    listen(sockfd, 5);

    return sockfd;
}
void accept_work(int sockfd, int epollfd)
{
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int connfd = 0;

    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    cout << "accept" << endl;
    add_event(epollfd, connfd, EPOLLIN);
}
void do_work(int sockfd)
{
    int epollfd;
    epoll_event events[1024];
    int res;
    int fd;
    char buf[256] = {0};

    epollfd = epoll_create(1024);
    add_event(epollfd, sockfd, EPOLLIN);
    for(;;){
        res = epoll_wait(epollfd, events, 1024, -1);
        if(res == -1){
            perror("wait");
            exit(1);
        }
        for(int i = 0; i < res; ++i){
            fd = events[i].data.fd;
            if(fd == sockfd && (events[i].events & EPOLLIN))
                accept_work(sockfd, epollfd);
            else if(events[i].events & EPOLLIN){
                read(fd, buf, 256);
                modify_event(epollfd, fd, EPOLLOUT);
            }else{
                write(fd, buf, strlen(buf)+1);
                modify_event(epollfd, fd, EPOLLIN);
            }
        }
    }
}
int main()
{
    int sockfd = 0;

    sockfd = init_sock();
    do_work(sockfd);

    return 0;
}
