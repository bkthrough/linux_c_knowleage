#include <apue.h>
int init()
{
    int sockfd = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
        perror("socket");
}
void start(int sockfd, short port, char *addr)
{
    struct sockaddr_in cliaddr;
    struct sockaddr_in seraddr;
    char readbuf[256] = {0};
    char sendbuf[256] = {0};
    socklen_t len = sizeof(cliaddr);

    seraddr.sin_port = htons(port);
    seraddr.sin_addr.s_addr = inet_addr(addr);
    seraddr.sin_family = AF_INET;
    while(1){
        scanf("%s", sendbuf);
        sendto(sockfd, sendbuf, strlen(sendbuf)+1, 0, (struct sockaddr *)&seraddr, len);

        recvfrom(sockfd, readbuf, 256, 0, (struct sockaddr *)&seraddr, &len);
        printf("ser:> %s\n", readbuf);
    }
}
int main(int argc, char *argv[])
{
    int sockfd = 0;

    if(argc != 3){
        printf("arg wrong.\n");
        return 1;
    }
    sockfd = init();
    start(sockfd, (short)atoi(argv[1]), argv[2]);

    return 0;
}
