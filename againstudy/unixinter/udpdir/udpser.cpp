#include <apue.h>
int init(short port, char *addr)
{
    int sockfd = 0;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(seraddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
        perror("socket");
    seraddr.sin_port = htons(port);
    seraddr.sin_addr.s_addr = inet_addr(addr);
    seraddr.sin_family = AF_INET;
    if(-1 == bind(sockfd, (struct sockaddr *)&seraddr, len))
        perror("bind");

    return sockfd;
}
void start(int sockfd)
{
    struct sockaddr_in cliaddr;
    char readbuf[256] = {0};
    char sendbuf[256] = {0};
    socklen_t len = sizeof(cliaddr);

    while(1){
        recvfrom(sockfd, readbuf, 256, 0, (struct sockaddr *)&cliaddr, &len);
        printf("cli:> %s\n", readbuf);

        printf("ser:>");
        scanf("%s", sendbuf);
        sendto(sockfd, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr *)&cliaddr, len);
    }
}
int main(int argc, char *argv[])
{
    int sockfd = 0;

    if(argc != 3){
        printf("arg wrong.\n");
        return 1;
    }
    sockfd = init((short)atoi(argv[1]), argv[2]);
    start(sockfd);

    return 0;
}
