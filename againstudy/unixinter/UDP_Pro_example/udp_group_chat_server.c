#include "udp_group_chat_common.h"


_group groups[GROUPMAX];
_thinfo threads[GROUPMAX];//one group , one thread for service
int socks  = -1;
int runflg =  1;

void sig_int(int sig)
{
    runflg = 0;
}

boolean init()
{
    int sockid;
    sockaddr_in  addr;

    memset(groups,0x00,sizeof(_group)*GROUPMAX);
    memset(threads,0x00,sizeof(_thinfo)*GROUPMAX);
    sockid = socket(AF_INET,SOCK_DGRAM,0);
    if(0 > sockid){
        //socket error
        return FALSE;
    }
    socks = sockid;
    bzero(&addr,sizeof(sockaddr_in));
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(CHATPORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockid,(sockaddr *)&addr,sizeof(sockaddr))){
        close(sockid);
        return FALSE;
    }
    if(SIG_ERR == signal(SIGINT,sig_int)){
        close(socks);
        return FALSE;
    }
    return TRUE;
}

void do_send_group(_group *group,_uchat_head *msg)
{
    int loop = 0 , usize = 0 ;
    if(NULL == group || NULL == msg){
        return;
    }
    usize = UHEADSIZE + msg->msglen;
    for(loop=0;loop<PEOPLEMAX;++loop){
        if(!memcmp(&msg->src_addr,&group->members[loop].addr,sizeof(sockaddr))){
            continue;
        }
        if(group->members[loop].inuse){
            sendto(socks,msg,usize,0,
                   (sockaddr *)&group->members[loop].addr,sizeof(sockaddr));
        }
    }
}

/*one group,one thread*/
void * msg_deal_thread(void *index)
{
    int myindex ,loop = 0;
    _thinfo *myinfo  = NULL;
    _group  *mygroup = NULL;

    memcpy(&myindex,&index,sizeof(int));
    myinfo = &threads[myindex];
    for(loop=0;loop<GROUPMAX;++loop){
        if(groups[loop].groupnumber == myinfo->groupnumber){
            mygroup = &groups[loop];
            break;
        }
    }
    if(NULL == mygroup){
        printf("thread: groupnumber error {%d}\n",myinfo->groupnumber);
        pthread_exit(NULL);
    }
    while(runflg){
        if(0 >= groups[myinfo->groupindex].members){
        //the members are all quit , threads exit.
            break;
        }
        if(0 < myinfo->have_msg){
            do_send_group(mygroup,&myinfo->chatmsg);
            myinfo->have_msg -= 1;
        }else{
            usleep(1000);
        }
    }
    pthread_exit(NULL);
    return NULL;
}

void do_send_msg(_uchat_head *msg,sockaddr_in *client)
{
    int groupnumber = -1 , loop = 0 , index = -1;
    int threadindex = -1;
    pthread_t  thid;
    _uchat_head ack;
    void *thin;

    if(NULL == msg || NULL == client){
        return;
    }
    groupnumber = msg->groupnumber;
    if(0 >= groupnumber){
        //illegal group number
        return;
    }
    //find the group number
    for(loop=0;loop<GROUPMAX;++loop){
        if(groupnumber == groups[loop].groupnumber){
            //found
            index = loop;
            break;
        }
    }
    if(-1 == index){
        //not found , create a new one
        for(loop=0;loop<GROUPMAX;++loop){
            if(0 >= groups[loop].groupnumber){
                index = loop;
                break;
            }
        }
        if(GROUPMAX == loop){
            //didn't find an idle position
            return;
        }
        groups[index].groupnumber = groupnumber;
        //groups[index].membernum   = 1;
    }

    //find the thread which should deal with the message
    for(loop=0;loop<GROUPMAX;++loop){
        if(threads[loop].inuse && groupnumber == threads[loop].groupnumber){
            //found
            threadindex = loop;
            break;
        }
    }
    if(-1 == threadindex){
    //didn't found , create a new thread
        for(loop=0;loop<GROUPMAX;++loop){
            if(!threads[loop].inuse){
                break;
            }
        }
        if(GROUPMAX == loop){
            //no idle position
            return;
        }
        threads[loop].inuse = 1;
        threads[loop].groupindex = index;
        threads[loop].groupnumber = groupnumber;
        threads[loop].have_msg = 0;
        thin = (char *)0x00 + loop ;
        if(pthread_create(&thid,NULL,msg_deal_thread,thin)){
        //errorr
            return;
        }
        pthread_detach(thid);
    }

    switch(msg->ctl){
    case CHATJOIN :
        groups[index].membernum += 1;
        for(loop=0;loop<PEOPLEMAX;++loop){
            if(!groups[index].members[loop].inuse){
                groups[index].members[loop].inuse = 1;
                memcpy(&groups[index].members[loop].addr,client,sizeof(sockaddr));
                break;
            }
        }
        ack.ctl = CHATDROP;
        if(PEOPLEMAX != loop){
            ack.ctl = CHATCONN;
        }
        sendto(socks,&ack,UHEADSIZE,0,(sockaddr *)client,sizeof(sockaddr));
        break;
    case CHATMSG  :
        memcpy(&msg->src_addr,client,sizeof(sockaddr_in));
        memcpy(&threads[threadindex].chatmsg,msg,sizeof(_uchat_head));
        threads[threadindex].have_msg += 1;
        break;
    case CHATOFF  :
        for(loop=0;loop<PEOPLEMAX;++loop){
            if(groups[index].members[loop].addr.sin_addr.s_addr == client->sin_addr.s_addr){
                groups[index].membernum -= 1;
                groups[index].members[loop].inuse = 0;
                break;
            }
        }
        break;
    default:
        printf("Unknown msg type : %d\n",msg->ctl);
        break;
    }//end switch

}

void service_start()
{
    int rcvsize = sizeof(_uchat_head);
    int rst = 0;
    int socklen = sizeof(sockaddr);
    sockaddr_in client;
    _uchat_head rcvmsg;

    while(runflg){
        rst = recvfrom(socks,&rcvmsg,rcvsize,MSG_DONTWAIT,(sockaddr *)&client,&socklen);
        if(0 >= rst){
            usleep(100);
            continue;
        }
        do_send_msg(&rcvmsg,&client);
    }
}

void service_end()
{
    close(socks);
}

int main(void)
{
    init();
    service_start();
    service_end();
    return 0;
}
