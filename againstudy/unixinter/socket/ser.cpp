#include <apue.h>
#include <sys/epoll.h>
#include <iostream>
using namespace std;

#define SERPORT   (8888)
#define LISNUM    (5)

//epoll的好处：
//只把描述符添加一次到内核中
//不用所有都去轮巡
//描述符个数无限
static void handle_accept(int, int);
static void add_event(int, int, int);
int init_udp()
{
    int sockfd = 0;
    socklen_t len;
    struct sockaddr_in seraddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr   = htonl(INADDR_ANY);
    seraddr.sin_port   = htons(SERPORT);

    if(0 > bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr))){
        close(sockfd);
        cerr << "bind error.\n";
    }

    return sockfd;
}
int init_tcp()
{
    int listenfd = 0;
    socklen_t len;
    struct sockaddr_in seraddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr   = htonl(INADDR_ANY);
    seraddr.sin_port   = htons(SERPORT);

    if(0 > bind(listenfd, (const struct sockaddr *)&seraddr, sizeof(seraddr))){
        close(listenfd);
        cerr << "bind error.\n";
    }
    if(0 > listen(listenfd, LISNUM)){
        close(listenfd);
        cerr << "listen error.\n";
    }

    return listenfd;
}

void start(int listenfd, int udpfd)
{
    int    res = 0;
    int    epollfd;
    int    fd = 0;
    int    n = 0;
    char   buf[1024] = {0};
    struct epoll_event events[100];
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    //创建
    epollfd = epoll_create(100);
    //把listen的加入到epoll中
    add_event(epollfd, listenfd, EPOLLIN);
    add_event(epollfd, udpfd, EPOLLIN);
    for(;;){
        //res的值是就绪链表里就绪的个数
        res = epoll_wait(epollfd, events, 100, -1);
        for(int i = 0; i < res; ++i){
            //就绪的fd
            fd = events[i].data.fd;
            //listenfd得到的响应，那么就要去创建接收描述符
            if((fd == listenfd) && (events[i].events & EPOLLIN)){
                handle_accept(listenfd, epollfd);
            }
            //其他的如果是读，那么就去读好了
            else if((fd == udpfd) && events[i].events & EPOLLIN){
                n = recvfrom(fd, buf, 1024, 0, (struct sockaddr *)&cliaddr,
                             &len);
                sendto(fd, buf, n, 0, (struct sockaddr *)&cliaddr, len);
            }
        }
    }
    close(listenfd);
}

static void add_event(int epollfd, int fd, int state)
{
    struct epoll_event ev;

    ev.events = state;
    ev.data.fd = fd;
    //添加fd到epoll中
    if(0 > epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev))
        cout << "add error.\n";
}

static void handle_accept(int listenfd, int epollfd)
{
    int sockfd = 0;
    struct sockaddr cliaddr;
    socklen_t len = sizeof(cliaddr);

    sockfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
    add_event(epollfd, sockfd, EPOLLIN);
}

int main()
{
    int listenfd = 0;
    int udpfd = 0;

    listenfd = init_tcp();
    udpfd    = init_udp();
    start(listenfd, udpfd);

    return 0;
}
