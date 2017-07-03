#include <apue.h>
#include <sys/epoll.h>
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
void do_work(int sockfd)
{
    epoll_event events[2];
    int i = 0;
    int epollfd = 0;
    int fd = 0;
    char buf[256] = {0};
    int flag = 0;

    epollfd = epoll_create(2);
    add_event(epollfd, STDIN_FILENO, EPOLLIN);
    add_event(epollfd, sockfd, EPOLLOUT);
    for(;;){
        int res = epoll_wait(epollfd, events, 2, -1);
        if(res == -1){
            perror("wait");
            exit(1);
        }
        for(i = 0; i < res; ++i){
            fd = events[i].data.fd;
            if(fd == STDIN_FILENO && (events[i].events & EPOLLIN)){
                read(STDIN_FILENO, buf, 256);
                flag = 1;
            }else if(flag == 1 && fd == sockfd && (events[i].events & EPOLLOUT)){
                write(sockfd, buf, strlen(buf)+1);
                flag = 0;
                modify_event(epollfd, sockfd, EPOLLIN);
            }else if(fd == sockfd && (events[i].events & EPOLLIN)){
                memset(buf, 0, strlen(buf));
                read(sockfd, buf, 256);
                printf("echo is :> %s", buf);
                modify_event(epollfd, sockfd, EPOLLOUT);
            }
        }
    }
}
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(struct sockaddr);

    if(sockfd < 0){
        perror("socket");
        return 1;
    }
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr(IP);
    seraddr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr *)&seraddr, len);
    do_work(sockfd);

    return 0;
}
