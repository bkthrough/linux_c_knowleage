#include"../unp.h"
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

void handle_connection(struct pollfd *connfds, int num)
{
    int n;
    char buf[256];
    for(int i=1; i<= num; ++i)
    {
        if(connfds[i].fd  == -1)
            continue;
        if(connfds[i].revents & POLLIN)
        {
            n = recv(connfds[i].fd, buf, 256, 0);
            if(n <= 0)
            {
                close(connfds[i].fd);
                connfds[i].fd = -1;
                continue;
            }
            printf("recv msg:>%s\n",buf);
            send(connfds[i].fd, buf, n, 0);
        }
    }
}

void do_poll(int sockSer)
{
    pollfd clientfds[OPEN_SIZE];
    clientfds[0].fd = sockSer;
    clientfds[0].events = POLLIN;

    for(int i=1; i<OPEN_SIZE; ++i)
        clientfds[i].fd = -1;

    int maxi = 0;
    int nready;
    struct sockaddr_in addrCli;
    socklen_t addrlen = sizeof(struct sockaddr);
    int i;
    for(;;)
    {
        nready = poll(clientfds, maxi+1,-1);
        if(nready == -1)
        {
            perror("poll");
            exit(1);
        }
        if(clientfds[0].revents & POLLIN)
        {
            int sockConn = accept(sockSer, (struct sockaddr*)&addrCli, &addrlen);
            if(sockConn == -1)
            {
                perror("accept");
                continue;
            }
            printf("accept a new client:%s:%d\n",inet_ntoa(addrCli.sin_addr),addrCli.sin_port);

            for(i=1; i<OPEN_SIZE; ++i)
            {
                if(clientfds[i].fd < 0)
                {
                    clientfds[i].fd = sockConn;
                    break;
                }
            }
            if(i == OPEN_SIZE)
            {
                printf("Server Over Load.\n");
                continue;
            }
            clientfds[i].events = POLLIN;
            maxi = (i > maxi ? i : maxi);
            if(--nready <= 0)
                continue;
        }
        handle_connection(clientfds, maxi);
    }
}

int main()
{
    int sockSer;
    sockSer = sock_bind(IPADDR, PORT);
    listen(sockSer, LISTENQ);
    do_poll(sockSer);
    return 0;
}






