#include"../unp.h"
#include"utili.h"
#include<stdlib.h>

int sock_bind(const char *ip, short port)
{
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(port);
    addrSer.sin_addr.s_addr = inet_addr(ip);
    socklen_t addrlen = sizeof(struct sockaddr);
    bind(fd, (struct sockaddr*)&addrSer, addrlen);
    return fd;
}

void handle_accept(int epollfd, int listenfd)
{
    struct sockaddr_in addrCli;
    int sockConn;
    socklen_t addrlen = sizeof(struct sockaddr);
    sockConn = accept(listenfd, (struct sockaddr*)&addrCli, &addrlen);
    if(sockConn == -1)
        perror("accept");
    else
    {
        printf("accept a new client:%s:%d\n",inet_ntoa(addrCli.sin_addr),addrCli.sin_port);
        add_event(epollfd, sockConn, EPOLLIN);
    }
}

void do_read(int epollfd, int fd, char *buf)
{
    int nread = read(fd, buf, 256);
    if(nread <= 0)
    {
        printf("Server is Closed.\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLIN);
    }
    printf("recv msg:>%s\n",buf);
    modify_event(epollfd, fd, EPOLLOUT);
}

void do_write(int epollfd, int fd, char *buf)
{
    int nwrite = write(fd, buf, strlen(buf)+1);
    if(nwrite <= 0)
    {
        printf("client is closed.\n");
        close(fd);
        delete_event(epollfd, fd, EPOLLOUT);
    }
    else
        modify_event(epollfd, fd, EPOLLIN);
}


void handle_events(int epollfd, epoll_event *events, int num, int listenfd, char *buf)
{
    int fd;
    for(int i=0; i<num; ++i)
    {
        fd = events[i].data.fd;
        if((fd==listenfd) && (events[i].events & EPOLLIN))
            handle_accept(epollfd, listenfd);
        else if(events[i].events & EPOLLIN)
            do_read(epollfd, fd, buf);
        else if(events[i].events & EPOLLOUT)
            do_write(epollfd, fd, buf);
    }
}

void do_epoll(int listenfd)
{
    int epollfd;
    epoll_event events[1024];
    epollfd = epoll_create(FDSIZE);
    add_event(epollfd,listenfd, EPOLLIN);
    int res;
    char buf[256];
    for(;;)
    {
        res = epoll_wait(epollfd, events, 1024,-1);
        if(res == -1)
        {
            perror("epoll_wait");
            exit(1);
        }
        handle_events(epollfd, events, res, listenfd, buf);
    }
    close(epollfd);
}

int main()
{
    int listenfd;
    listenfd = sock_bind(IPADDR, PORT);
    listen(listenfd, LISTENQ);
    do_epoll(listenfd);
    return 0;
}
