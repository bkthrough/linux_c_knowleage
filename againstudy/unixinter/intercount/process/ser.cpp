#include "../unp.h"

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
    int yes = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    seraddr.sin_addr.s_addr = inet_addr(addr);
    seraddr.sin_port = htons(port);
    seraddr.sin_family = AF_INET;
    if(0 > bind(sockfd, (struct sockaddr *)&seraddr, len)){
        perror("bind");
        close(sockfd);
        exit(1);
    }
    //5是等待队列中的最大值
    listen(sockfd, 5);

    return sockfd;
}
void start(int listenfd)
{
    Oper o;
    struct sockaddr_in cliaddr;
    struct sockaddr_in seraddr;
    socklen_t len = sizeof(cliaddr);
    int sockfd;
    int res;
    pid_t pid;

    while(1){
        sockfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
        getsockname(sockfd, (struct sockaddr *)&seraddr, &len);
        int port = ntohs(seraddr.sin_port);
        cout << port << endl;
        if(sockfd < 0){
            perror("accept");
            exit(1);
        }
        if(0 > (pid = fork())){
            perror("fork");
            exit(1);
        }else if(pid == 0){
            while(1){
                read(sockfd, &o, sizeof(o));
                switch(o.oper){
                    case ADD:
                        res = o.op1 + o.op2;
                        break;
                    case MUL:
                        res = o.op1 * o.op2;
                        break;
                    case DIV:
                        res = o.op1 / o.op2;
                        break;
                    case SUB:
                        res = o.op1 - o.op2;
                        break;
                    case QUIT:
                        break;
                    default:
                        break;
                }
                send(sockfd, &res, sizeof(int), 0);
            }
            exit(0);
        }else{
            //continue
        }
    }
}
int main(int argc, char *argv[])
{
    int sockfd;
    if(argc != 3){
        printf("wrong arg.\n");
        return 1;
    }
    sockfd = init((short)atoi(argv[1]), argv[2]);
    start(sockfd);

    return 0;
}
