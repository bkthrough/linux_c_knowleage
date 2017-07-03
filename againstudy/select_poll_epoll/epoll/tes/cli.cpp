#include"../unp.h"
#include"utili.h"
#include<string.h>
#include<stdlib.h>
#include<iostream>

//int sock_bind(const char *ip, short port)
//{
//    int fd;
//    fd = socket(AF_INET, SOCK_STREAM, 0);
//    struct sockaddr_in addrSer;
//    addrSer.sin_family = AF_INET;
//    addrSer.sin_port = htons(port);
//    addrSer.sin_addr.s_addr = inet_addr(ip);
//    socklen_t addrlen = sizeof(struct sockaddr);
//    bind(fd, (struct sockaddr*)&addrSer, addrlen);
//    return fd;
//}
//
//void handle_accept(int epollfd, int listenfd)
//{
//    struct sockaddr_in addrCli;
//    int sockConn;
//    socklen_t addrlen = sizeof(struct sockaddr);
//    sockConn = accept(listenfd, (struct sockaddr*)&addrCli, &addrlen);
//    if(sockConn == -1)
//        perror("accept");
//    else
//    {
//        printf("accept a new client:%s:%d\n",inet_ntoa(addrCli.sin_addr),addrCli.sin_port);
//        add_event(epollfd, sockConn, EPOLLIN);
//    }
//}

/*
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
*/
int g_send_num = 0;
int g_recv_num = 0;
pthread_mutex_t recv_mutex;
pthread_mutex_t send_mutex;

void *thread_func(void *arg)
{
    int last_recv_num = 0;
    int last_send_num = 0;
    while(1){
        sleep(1);
        pthread_mutex_lock(&recv_mutex);
        printf("************************************************************\n");
        printf("接受到%d个包\n", g_recv_num);
        printf("上一秒收到%d个包\n", g_recv_num - last_recv_num);
        last_recv_num = g_recv_num;
        pthread_mutex_unlock(&recv_mutex);
        pthread_mutex_lock(&send_mutex);
        printf("发送到%d个包\n", g_send_num);
        printf("上一秒发送%d个包\n", g_send_num - last_send_num);
        last_send_num = g_send_num;
        pthread_mutex_unlock(&send_mutex);
        printf("************************************************************\n");
    }
}

inline int extract(const char *buf, int len)
{
    int pack_num = 1;

    while(buf[0] == 0x12 && buf[9] == 0x21 && len > 10){
        memcpy((char *)buf, buf+10, 8182);
        ++pack_num;
        len -= 10;
    }

    return pack_num;
}

int main()
{
    int sockfd;
    struct sockaddr_in sersock;
    int num = 0;
    int epoll_fd = 0;
    epoll_event events[1024];

    //listenfd = sock_bind(IPADDR, PORT);
    //listen(listenfd, LISTENQ);
    sersock.sin_family = AF_INET;
    sersock.sin_port = htons(61000);
    sersock.sin_addr.s_addr = inet_addr("123.103.74.220");
    epoll_fd = epoll_create(1024);
    pthread_t tid;

    pthread_mutex_init(&recv_mutex, NULL);
    pthread_mutex_init(&send_mutex, NULL);
    std::cin >> num;
    pthread_create(&tid, NULL, thread_func, NULL);
    for(int i = 0; i < num; ++i){
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        int ret = connect(sockfd, (struct sockaddr *)&sersock, sizeof(sersock));
        add_event(epoll_fd, sockfd, EPOLLIN | EPOLLOUT);
        //add_event(epoll_fd, sockfd, EPOLLOUT);
    }
    int fd = 0;
    char send_buf[8192] = {0};
    char recv_buf[8192] = {0};
    int len = 8192;
    int recv_len = 0;
    int package_num = 0;
    send_buf[0] = 0x12; send_buf[5] = 0x01; send_buf[9] = 0x21;
    for(;;){
        num = epoll_wait(epoll_fd, events, 1024, -1);
        for(int i = 0; i < num; ++i){
            fd = events[i].data.fd;
            if(events[i].events & EPOLLIN){
                if(0 > (recv_len = read(fd, recv_buf, len))){
                    std::cout << "read error\n";
                    continue;
                }
                package_num = extract((const char *)recv_buf, recv_len);
                pthread_mutex_lock(&recv_mutex);
                g_recv_num += package_num;
                pthread_mutex_unlock(&recv_mutex);
            }
            if(events[i].events & EPOLLOUT){
                if(0 > write(fd, send_buf, 10)){
                    std::cout << "write error\n";
                    continue;
                }
                pthread_mutex_lock(&send_mutex);
                ++g_send_num;
                pthread_mutex_unlock(&send_mutex);
            }
        }
        usleep(10000);
    }
    return 0;
}
