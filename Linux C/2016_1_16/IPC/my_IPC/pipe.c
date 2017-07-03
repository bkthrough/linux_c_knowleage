#include <apue.h>

#define LEN  4096
void m_read(int pfd[2],FILE *fp)
{
    char buf[LEN] = {0};
    int size = 0;

    close(pfd[1]);

    while(0 != (size = read(pfd[0],buf,LEN-1))){
        printf("%s",buf);
        memset(buf,0x00,LEN);
    }
    close(pfd[0]);

    _exit(0);
}

void m_write(int pfd[2],FILE *fp)
{
    char buf[LEN] = {0};
    int size = 0;

    close(pfd[0]);

    while(0 != (size = fread(buf,1,LEN-1,fp))){
        write(pfd[1],buf,LEN);
        memset(buf,0x00,LEN);
    }
}
int main(int argc,char *argv[])
{
    int pfd[2];
    int chid;
    FILE *fp;

    if(1 >= argc){
        printf("para error\n");
        return 1;
    }
    fp = fopen(argv[1],"r");
    if(0 != pipe(pfd)){
        //error
        fclose(fp);
    }
    chid = fork();
    if(0 > chid){
        //error
        fclose(fp);
        return 2;
    }else if(0 == chid){
        m_read(pfd,fp);
    }else{
        m_write(pfd,fp);
    }
    close(pfd[1]);
    wait(NULL);

    fclose(fp);

    return 0;
}
