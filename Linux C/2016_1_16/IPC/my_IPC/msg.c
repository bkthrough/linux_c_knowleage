#include <apue.h>

#define SIZE    100
char *MSG1="hello,world";
char *MSG2="dota is good game";
char *MSG3="end msg";

int run = 1;
struct msg_st{
    long int msg_type;
    char text[SIZE];
};

struct msg_st data;
void msg_rcv(int msgid)
{
    while(run){
        bzero(data.text,SIZE);
        if(-1 == msgrcv(msgid,(void *)&data,SIZE,0,0)){
            printf("msg recieve error\n");
            return ;
        }
        if(strcmp(data.text,"end msg") == 0){
            break;
        }
        printf("%s\n",data.text);
    }
}
void msg_snd(int msgid,char *buf)
{
    bzero(data.text,SIZE);
    strcpy(data.text,buf);
    data.msg_type = 1;
    if(-1 == msgsnd(msgid,(void *)&data,SIZE,0)){
        printf("send error\n");
        return ;
    }
}
int main(int argc,char *argv[])
{
    int msgid = -1;
    int chid = -1;

    msgid = msgget(0x12341234,0644|IPC_CREAT);
    if(msgid == -1){
        printf("create error\n");
        return 1;
    }
    chid = fork();
    if(-1 > chid){
        //error
    }
    else if(0 == chid){
        msg_snd(msgid,MSG1);
        msg_snd(msgid,MSG2);
        msg_snd(msgid,MSG3);
        exit(0);
    }else{
        msg_rcv(msgid);
    }
    wait(NULL);

    return 0;
}
