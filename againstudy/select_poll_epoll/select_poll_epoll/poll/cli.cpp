#include"../unp.h"

void handle_connection(int sockfd)
{
    pollfd fds[2];
    fds[0].fd = sockfd;
    fds[0].events = POLLIN;
    fds[1].fd = STDIN_FILENO;
    fds[1].events = POLLIN;

    int n;
    char buf[256];
    for(;;)
    {
        poll(fds, 2, -1);
        if(fds[0].revents & POLLIN)
        {
            n = recv(sockfd, buf, 256, 0);
            if(n <= 0)
            {
                printf("Server is Closed.\n");
                close(sockfd);
            }
            write(STDOUT_FILENO, buf, n);
        }
        if(fds[1].revents & POLLIN)
        {
            n = read(STDIN_FILENO, buf, 256);
            if(n == 0)
            {
                continue;
            }
            write(sockfd, buf, n);
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

    connect(sockCli, (struct sockaddr*)&addrSer, sizeof(struct sockaddr));

    handle_connection(sockCli);

    return 0;
}

