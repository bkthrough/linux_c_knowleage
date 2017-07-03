#include <apue.h>

int sockid = -1;

int sock_init(char *address,int port,int *sockid)
{
    int sock = -1;
    sockaddr_in addr;

    sock = socket(AF_INET,SOCK_STREAM,0);
    bzero(&addr,sizeof(sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port   = htons(port);
    if(NULL == address){
        addr.sin_addr.s_addr = INADDR_ANY;
    }
    //inet_aton(address,&addr.sin_addr);
    bind(sock,(sockaddr *)&addr,sizeof(sockaddr_in));
    *sockid = sock;
}
void do_connect(int connid)
{
    char buf[100] = {0};
    while(1){
        recv(connid,buf,100,0);
        printf("%s\n",buf);
        memset(buf,0x00,strlen(buf));
        sleep(1);
    }
}
int main(int argc,char *argv[])
{
    int connid = -1;
    sockaddr_in client;
    int len = sizeof(client);
    int chid = -1;

    sock_init(argv[1],80,&sockid);
    listen(sockid,5);
    while(1){
        connid = accept(sockid,(sockaddr *)&client,&len);
        chid = fork();
        if(0 == chid){
            do_connect(connid);
        }else{
            //continue
        }
    }

    return 1;
}
