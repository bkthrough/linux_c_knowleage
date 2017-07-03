#include "unp.h"

int init(short port, char *addr)
{
    int sockfd = 0;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(seraddr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("socket");
        exit(1);
    }
    seraddr.sin_addr.s_addr = inet_addr(addr);
    seraddr.sin_port = htons(port);
    seraddr.sin_family = AF_INET;
    if(0 > connect(sockfd, (struct sockaddr *)&seraddr, len)){
        perror("connect");
        close(sockfd);
        exit(1);
    }

    return sockfd;
}
void start(int sockfd)
{
    Oper o;
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    char res[256] = {0};
    pid_t pid;

    while(1){
        memset(res, 0, 256);
        printf("please choose mode:\n");
        scanf("%d", &o.oper);
        if(o.oper == QUIT){
            write(sockfd, &o, sizeof(o));
            break;
        }
        printf("please input num op1:\n");
        scanf("%s", o.op1);
        printf("please input num op2:\n");
        scanf("%s", o.op2);
        write(sockfd, &o, sizeof(o));
        read(sockfd, res, 256);
        printf("res is : %s.\n", res);
    }
}
void help()
{
    cout << "********************************" << endl;
    cout << "**  输入想要的模式            **" << endl;
    cout << "**  0：加法    1：减法        **" << endl;
    cout << "**  2：乘法    3：除法        **" << endl;
    cout << "**  4：推出程序               **" << endl;
}
int main(int argc, char *argv[])
{
    int sockfd;
    if(argc != 3){
        printf("wrong arg.\n");
        return 1;
    }
    sockfd = init((short)atoi(argv[1]), argv[2]);
    help();
    start(sockfd);

    return 0;
}
