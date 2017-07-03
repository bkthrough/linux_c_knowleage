#include <apue.h>
#include <iostream>
using namespace std;

#define SERPORT  (8888)

int init()
{
    int sockfd = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        cerr << "socket error.\n";
        exit(1);
    }

    return sockfd;
}
void str_cli(FILE *fp, int sockfd)
{
    char buf[1024] = {0};
    int  maxfdp1;
    fd_set rset;
    int stdineof = 0;

    FD_ZERO(&rset);
    while(1){
        //把对应的描述符转换为rset中的对应位并置1
        if(stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = (sockfd > fileno(fp) ? sockfd : fileno(fp))+1;
        //等待有描述符发生，那么就把其他的位置0
        select(maxfdp1, &rset, NULL, NULL, NULL);

        bzero(buf, strlen(buf)+1);
        if(FD_ISSET(sockfd, &rset)){
            if(0 == read(sockfd, buf, 1024)){
                if(stdineof == 1){
                    cout << "normal terminal.\n";
                    return ;
                }
                //else
                    //cerr << "error.\n";
            }
            write(fileno(stdout), buf, strlen(buf)+1);
        }

        if(FD_ISSET(fileno(fp), &rset)){
            if(0 == read(fileno(fp), buf, 1024)){
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            cout << "read from stdin.\n";
            write(sockfd, buf, strlen(buf)+1);
        }
    }

}
void start(int sockfd, char *addr)
{
    struct sockaddr_in seraddr;

    bzero(&seraddr, sizeof(seraddr));
    seraddr.sin_port = htons(SERPORT);
    inet_pton(AF_INET, addr, &seraddr.sin_addr);
    seraddr.sin_family = AF_INET;

    if(0 > connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr))){
        cerr << "error connect.\n";
    }
    str_cli(stdin, sockfd);
}
void sig_pipe(int sig)
{
    cout << "sigpipe.\n";
}
int main(int argc, char *argv[])
{
    int sockfd = 0;

    if(argc != 2){
        cout << "please input like this:  ./cli 127.0.0.1.\n";
        exit(1);
    }
    signal(SIGPIPE, sig_pipe);
    sockfd = init();
    start(sockfd, argv[1]);

    return 0;
}
