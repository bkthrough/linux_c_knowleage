#include <apue.h>

#define LINEMAX     4096 //4096 + 1
#define FIFONAME    "/tmp/my.fifo"
#define ENDMSG      "I_Have_A_Dream_That_When_I_Grow_Up_I_Will_Marry_FanBingBing"

int main(int ac,char **av)
{
    int    fd , len = 0;
    FILE * fs;
    char   buf[LINEMAX];
    pid_t  chid;

    if(1 >= ac){
        printf("Usage : %s <file-name>\n",av[0]);
        return 1;
    }
    fs = fopen(av[1],"r");
    if(NULL == fs){
        printf("%s\n",strerror(errno));
        return 2;
    }
    if(-1 != (fd = open(FIFONAME,O_RDWR))){
    ;
    }else if(0 != mkfifo(FIFONAME,0666)){
        printf("mkfifo %s\n",strerror(errno));
        fclose(fs);
        return 3;
    }else if(0 > (fd = open(FIFONAME,O_RDWR))){
        printf("open %s\n",strerror(errno));
        return 4;
    }

    chid = fork();
    if(0 > chid){
    //error
    }else if(0 == chid){
        int rdsz = 0;
        memset(buf,0x00,LINEMAX);
        //fcntl(fd,F_SETFL,O_NONBLOCK);
        while(rdsz = read(fd,buf,LINEMAX-1)){
            if(0 == strncmp(buf,ENDMSG,strlen(ENDMSG))){
                break;
            }
            printf("%s",buf);
            memset(buf,0x00,LINEMAX); // Important
        }
        exit(0);
    }else{
        memset(buf,0x00,LINEMAX);
        while(fread(buf,1,LINEMAX-1,fs)){
            len = strlen(buf);
            write(fd,buf,len);
            memset(buf,0x00,LINEMAX);
            //usleep(100);
        }
        write(fd,ENDMSG,strlen(ENDMSG));
        close(fd);
    }
    wait(NULL);
    printf("-------------- Proc End ------------------\n");
    fclose(fs);
    return 0;
}
