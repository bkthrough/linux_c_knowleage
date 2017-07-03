/*
 * UDP group chat project
 */
#include "apue.h"

#define TRUE       1
#define FALSE      0
#define EXIT       "exit"
typedef int        boolean ;

#define CHATPORT   9999

#define PEOPLEMAX  128
#define GROUPMAX   128

#define CHATLEN    1024 //message's length
#define NAMELEN    32   //name length
#define UHEADSIZE  (sizeof(_uchat_head) - CHATLEN)

#define CHATCONN   1   //connection requests
#define CHATOFF    2   //quit a group
#define CHATDROP   4   //connection refused
#define CHATMSG    8   //messages
#define CHATJOIN   16  //join a group


//group information
typedef struct member {
    int  inuse;
    sockaddr_in addr;
}_member;

typedef struct group {
    int groupnumber;
    int membernum;
    _member members[PEOPLEMAX];
}_group;

//message translation header
typedef struct uchat_head {
    int         groupnumber;
    int         ctl;
    sockaddr_in src_addr;
    short       msglen;
    char        nickname[NAMELEN];
    char        msg[CHATLEN];
}_uchat_head;

//thread control information
typedef struct thinfo {
    int inuse;
    int groupindex;
    int groupnumber;
    int have_msg;
    _uchat_head chatmsg;
}_thinfo;

