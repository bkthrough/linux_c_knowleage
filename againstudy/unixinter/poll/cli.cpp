#include <apue.h>

#define IP "127.0.0.1"
#define PORT 8888
int main(int argc, char *argv[])
{
    int sockfd = 0;
    char buf[256] = {0};
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(seraddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr(IP);
    seraddr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr *)&seraddr, len);
    for(;;){
        send(sockfd, "hello", strlen("hello")+1, 0);
        read(sockfd, buf, 256);
        printf("%s\n",buf);
        sleep(3);
    }

    return 0;
}
