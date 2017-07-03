#include <apue.h>

#define SERPORT (5050)

int run = 1;

void sig_segv(int sig)
{
    exit(0);
}
void sig_chld(int sig)
{
    exit(0);
}
int init(char *addr)
{
    int sockfd = 0;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(seraddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("error");
        exit(1);
    }
    seraddr.sin_addr.s_addr = inet_addr(addr);
    seraddr.sin_port = htons(SERPORT);
    seraddr.sin_family = AF_INET;
    if(0 > connect(sockfd, (struct sockaddr *)&seraddr, len)){
        perror("");
        exit(1);
    }

    return sockfd;
}
void start(int sockfd)
{
    char readbuf[256] = {0};
    char sendbuf[256] = {0};
    int chld = 0;

    if(0 > (chld = fork())){
        perror("");
    }else if(chld == 0){
        while(run){
            printf("cli:<< ");
            if(0 < read(fileno(stdin), sendbuf, 256)){
                send(sockfd, sendbuf, strlen(sendbuf)+1, 0);
                if(strncmp(sendbuf, "quit", 4) == 0){
                    kill(getppid(), SIGKILL);
                    break;
                }
            }
        }
        close(sockfd);
        exit(0);
    }else{
        while(run){
            read(sockfd, readbuf, 256);
            if(strncmp(readbuf, "quit", 4) == 0){
                kill(chld, SIGKILL);
                break;
            }
            printf("ser:<< %s", readbuf);
        }
    }
    close(sockfd);
}
int main(int argc, char *argv[])
{
    int sockfd = 0;

    if(argc != 2){
        printf("error.\n");
        return 1;
    }
    sockfd = init(argv[1]);
    start(sockfd);

    return 0;
}
