#include "udp_group_chat_common.h"

int socks = -1;
int groupnumber;
int runflg = 1;
sockaddr_in serveraddr;
pthread_t thrcv;

enum {CMD=0,IPADDR,GROUPNUM};

void sig_int(int sig)
{
    runflg = 0;
}

void init(int ac,char **av)
{
    int sockid = -1;
    if(GROUPNUM >= ac){
        printf("Usage : %s <server-ip> <groupnumber>\n",av[CMD]);
        return ;
    }
    sockid = socket(AF_INET,SOCK_DGRAM,0);
    if(0 > sockid){
        return;
    }
    bzero(&serveraddr,sizeof(sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port   = htons(CHATPORT);
    if(!inet_aton(av[IPADDR],&serveraddr.sin_addr)){
        //error
    }
    socks = sockid;
    groupnumber = atoi(av[GROUPNUM]);
    if(SIG_ERR == signal(SIGINT,sig_int)){
    //error
    }
    if(siginterrupt(SIGINT,1)){
    //error
    }
}

//recv msg thread
void *recv_thread(void *in)
{
    _uchat_head msg;
    int rst = 0 , rcvsize = sizeof(_uchat_head);
    int socklen = sizeof(sockaddr_in);
    sockaddr_in server;

    while(runflg){
       rst = recvfrom(socks,&msg,rcvsize,MSG_DONTWAIT,(sockaddr *)&server,&socklen);
       if(0 >= rst){
           usleep(100);
           continue;
       }
       if(CHATOFF == msg.ctl){
           kill(getpid(),SIGINT);
           break;
       }
       if(CHATMSG == msg.ctl){
           printf("{%s} says: %s\n",inet_ntoa(msg.src_addr.sin_addr),msg.msg);
       }
    }
}

void do_chat()
{
    _uchat_head msg;
    sockaddr_in server;
    int rcvsize = sizeof(_uchat_head);
    int socklen = sizeof(sockaddr_in);
    int msglen = 0;

    if(0 > socks){
        printf("socket error : %d\n",socks);
        return;
    }
    printf("\n++++++++++++++ Type \"exit\" for quit ++++++++++++++\n\n");
    msg.ctl = CHATJOIN;
    msg.groupnumber = groupnumber;
    msg.msglen = 0;
    sendto(socks,&msg,UHEADSIZE,0,(sockaddr *)&serveraddr,socklen);
    msg.ctl = CHATOFF;
    recvfrom(socks,&msg,UHEADSIZE,0,(sockaddr *)&server,&socklen);
    if(CHATCONN != msg.ctl){
    //refused
        return;
    }
    if(pthread_create(&thrcv,NULL,recv_thread,NULL)){
    //error
    }

    //send msg loop
    while(runflg){
        memset(&msg,0x00,sizeof(_uchat_head));
        //recvfrom(socks,&msg,rcvsize,0,(sockaddr *)&server,&socklen);
        printf("[Me]>> ");
        sync();
        fgets(msg.msg,CHATLEN,stdin);

        msg.ctl = CHATMSG;
        msg.msglen = strlen(msg.msg);
        if(1 >= msg.msglen){
            continue;
        }
        if(!strncmp(EXIT,msg.msg,strlen(EXIT))){
            runflg = 0;
            break;
        }
        msg.groupnumber = groupnumber;
        sendto(socks,&msg,UHEADSIZE + msg.msglen,0,(sockaddr *)&serveraddr,socklen);
    }
    msg.groupnumber = groupnumber;
    msg.ctl = CHATOFF;
    msg.msglen = 0;
    sendto(socks,&msg,UHEADSIZE,0,(sockaddr *)&serveraddr,socklen);
    pthread_join(thrcv,NULL);
    close(socks);
}

int main(int ac,char **av)
{
    init(ac,av);
    do_chat();
}
