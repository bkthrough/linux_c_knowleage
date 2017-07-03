#include "../unp.h"
#include "../bigdata/utili.h"

#define RUN     1
#define FREE    0
#define MAX_NUM 20
#define NOW_NUM 10
#define BREAK   1

int        flag[MAX_NUM] = {0};
int        pool[MAX_NUM] = {0};
pthread_t  tid[MAX_NUM]  = {0};
static int now_num       = NOW_NUM;
int        sockfd;
struct     Oper o;

//void create_pool(); __attribute__((constructor))
void sig_usr1(int sig)
{}
void *p_fun(void *arg)
{
    char *res = NULL;
    int i = *(int *)arg;
    int connfd;

    while(1){
        //等待信号唤醒
        pause();
        connfd = sockfd;
        while(1)
        {
            //判断是否该结束
            if(flag[i] == BREAK){
                pool[i] = FREE;
                flag[connfd] = 0;
                break;
            }
            memset(&o, 0x00, sizeof(o));
            read(connfd, &o, sizeof(o));
            switch(o.oper){
                case ADD:
                    res = add(o.op1, o.op2);
                    break;
                case MUL:
                    res = mul(o.op1, o.op2);
                    break;
                case DIV:
                    res = div(o.op1, o.op2);
                    break;
                case SUB:
                    res = sub(o.op1, o.op2);
                    break;
                case QUIT:
                    goto end;
                default:
                    cout << "invalid para.\n";
                    break;
            }
            if(flag[i] == BREAK){
                pool[i] = FREE;
                flag[i] = 0;
                goto end;
            }
            send(connfd, res, strlen(res), 0);
            memset(res, 0, strlen(res));
        }
        //设置为空闲，循环回去等待
        end:
            pool[i] = FREE;
    }
}

int find_idel()
{
    return 0;
}
void create_pool()
{
    for(int i = 0; i < MAX_NUM; ++i){
        int val = i;
        pthread_create(&tid[i], NULL, p_fun, &val);
    }
}

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
    //设置为地址可重用
    int yes = 1;
    if(0 > setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes))){
        perror("setsockopt");
        close(sockfd);
        exit(1);
    }
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
    socklen_t len = sizeof(cliaddr);
    int res;
    int i = 0;
    pid_t pid;

    while(1){
        sockfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
        signal(SIGUSR1, sig_usr1);
        //找到空闲线程并唤醒它
again:
        for(i = 0; i < now_num; ++i){
            if(pool[i] == FREE){
                pool[i] = RUN;
                pthread_kill(tid[i], SIGUSR1);
                break;
            }
        }
        //如果到达了线程的最大值
        //找出合适的应该替换的线程
        //让那个线程置为空闲
        //回上面去加载线程
        if(i == MAX_NUM){
            int index = find_idel();
            flag[index] = BREAK;
            sleep(4);
            goto again;
        }
        //到了当前最大值，就去创建线程
        else if(i == now_num){
            pthread_create(&tid[now_num], NULL, p_fun, NULL);
            ++now_num;
            goto again;
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
    create_pool();
    sockfd = init((short)atoi(argv[1]), argv[2]);
    start(sockfd);

    return 0;
}
