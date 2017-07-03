#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "msg.h"
using namespace std;

#define SEND   (5)
#define RECV   (6)
#define ID (0x11)
int run = 1;
void sig_segv(int sig)
{
    exit(0);
}
void sig_chld(int sig)
{
    int status;
    wait(&status);
    exit(0);
}
int get_id(char *file)
{
    key_t msg_key;
    key_t msg_id;

    msg_key = ftok(file, ID);
    if(msg_key == -1){
        cerr << "ftok error." << endl;
        exit(1);
    }
    msg_id = msgget(msg_key, IPC_CREAT | IPC_EXCL | 0644);
    if(msg_id == -1){
        cerr << "msgget error." << endl;
        exit(1);
    }

    return msg_id;
}
bool send_msg(int msgid)
{
    Msgbuf m;
    m.msgtype = SEND;
    scanf("%s", m.msgbuf);
    msgsnd(msgid, &m, strlen(m.msgbuf) + 1, IPC_NOWAIT);
    if(strncmp(m.msgbuf, "bye", 3) == 0){
        return false;
    }
    return true;
}
bool read_msg(int msgid)
{
    Msgbuf m;
    msgrcv(msgid, &m, 256, RECV, 0);
    if(strncmp(m.msgbuf, "bye", 3) == 0){
        msgctl(msgid, IPC_RMID, NULL);
        return false;
    }
    cout << "cli say :" << m.msgbuf << endl;
    return true;
}
int main(int argc, char *argv[])
{
    int msgid;
    int chld = 0;

    msgid = get_id(argv[1]);
    if(0 > (chld = fork())){
       cerr << "fork error." << endl;
       msgctl(msgid, IPC_RMID, NULL);
       exit(1);
    }else if(chld == 0){
        while(run){
            if(false == send_msg(msgid))
            {
                kill(getppid(), SIGCHLD);
                exit(0);
            }
            signal(SIGSEGV, sig_segv);
        }
    }else{
        signal(SIGCHLD, sig_chld);
        while(1){
            if(false == read_msg(msgid)){
                kill(chld, SIGSEGV);
                break;
            }
        }
    }

    return 0;
}
