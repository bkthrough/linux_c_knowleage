#include <apue.h>

#define TRUE  (1)
#define FALSE (0)

int sockid;
int run = 1;
sockaddr_in serveraddr;
int sock_init(char *address,int port)
{
    if(NULL == address){
        return FALSE;
    }
    sockid = socket(AF_INET,SOCK_STREAM,0);
    if(0 > sockid){
        return FALSE;
    }
    bzero(&serveraddr,sizeof(sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    if(!inet_aton(address,&serveraddr.sin_addr)){
       return FALSE;
    }

    return TRUE;
}
int do_connect()
{
    if(connect(sockid,(sockaddr *)&serveraddr,sizeof(sockaddr_in))){
        return FALSE;
    }
    return TRUE;
}
void do_send()
{
    FILE *fp;
    char buf[12] = "hello,world";

    while(1){
        send(sockid,&buf,strlen(buf),0);
        sleep(1);
    }
}
int main(int argc,char *argv[])
{
    if(argc < 2){
        printf("arg is wrong\n");
        return 1;
    }
    sock_init(argv[1],80);
    do_connect();
    do_send();

    return 0;
}
