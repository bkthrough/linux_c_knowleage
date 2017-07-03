#include"../unp.h"

void handle_connection(int sockfd)
{
    fd_set readfds;
    int maxfd = sockfd;
    struct timeval tv;
    while(1)
    {
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);
        maxfd = sockfd;
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        int res = select(maxfd+1, &readfds, NULL, NULL, &tv);
        if(res == -1)
        {
            perror("select");
            return;
        }
        if(res == 0)
        {
            printf("Client time out.\n");
            continue;
        }
        int n;
        char recvbuf[256];
        if(FD_ISSET(sockfd, &readfds))
        {
            n = recv(sockfd,recvbuf, 256, 0);
            if(n <= 0)
            {
                printf("Server is closed.\n");
                close(sockfd);
                FD_CLR(sockfd, &readfds);
                return;
            }
            printf("client recv slef msg:> %s\n",recvbuf);
            sleep(3);
            send(sockfd, recvbuf, strlen(recvbuf)+1, 0);
        }
    }
}

int main()
{
    int sockCli;
    sockCli = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrSer;
    addrSer.sin_family = AF_INET;
    addrSer.sin_port = htons(PORT);
    addrSer.sin_addr.s_addr = inet_addr(IPADDR);

    socklen_t addrlen = sizeof(struct sockaddr);
    int res = connect(sockCli, (struct sockaddr*)&addrSer, addrlen);
    if(res < 0)
        perror("connect");
    printf("Client connect Server Ok.\n");
    send(sockCli,"hello Server.",strlen("hello Server.")+1, 0);
    handle_connection(sockCli);
    return 0;
}
