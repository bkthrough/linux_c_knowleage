#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN   1024

char *ENDMSG = "this is endmsg";

void m_read(int fd)
{
    int rdsz = 0;
    char buf[LEN] = {0};

    while(rdsz = read(fd,buf,LEN-1)){
        if(0 == strcmp(buf,ENDMSG)){
            break;
        }
        printf("%s",buf);
        memset(buf,0x00,LEN);
    }
}
void m_write(int fd,FILE *fs)
{
    int wtsz;
    char buf[LEN] = {0};

    while(fread(buf,1,LEN-1,fs)){
        wtsz = strlen(buf);
        write(fd,buf,wtsz);
        memset(buf,0x00,LEN);
        //时间必须长一点，这样保证结束字符串在写之前，之前写的东西会被读
        //不然读的就会连起来导致错误。
        usleep(100);
    }
    write(fd,ENDMSG,strlen(ENDMSG));
}
int main(int ac,char *av[])
{
    int fd = 0;
    int chid = -1;
    FILE *fs;

    fs = fopen(av[1],"r");

    if(-1 != (fd = open("my.fifo",O_RDWR,0666))){
    }else if(0 != mkfifo("my.fifo",0666)){
        //error
        fclose(fs);
        return 1;
    }else if(0 > (fd = open("my.fifo",O_RDWR,0666))){
        //error
        fclose(fs);
        return 2;
    }

    chid = fork();
    if(0 > chid){
        //error
    }else if(0 == chid){
        m_read(fd);
        exit(0);
    }else{
        m_write(fd,fs);
    }
    wait(NULL);
    close(fd);
    fclose(fs);

    return 0;
}
