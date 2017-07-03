#include <apue.h>

int main(int argc,char *argv[])
{
    int pfd[2];
    FILE *fs;
    int chid = -1;
    char buf[4097] = {0};

    if(1 >= argc){
        fprintf(stderr,"error");
        return 1;
    }
    fs = fopen(argv[1],"r");
    if(NULL == fs){
        fprintf(stderr,"error");
        return 1;
    }
    if(0 != pipe(pfd)){
        //error
        fclose(fs);
        return 1;
    }
    chid = fork();
    if(0 > chid){
        //error
    }else if(0 == chid){
        int rdsz = 0;
        close(pfd[1]);
        while(0 != (rdsz = read(pfd[0],buf,4096))){
            printf("%s\n",buf);
            memset(buf,'\0',4097);
        }
        close(pfd[0]);
        _exit(0);
    }else{
        close(pfd[0]);
        while(0 != fread(buf,1,4096,fs)){
            write(pfd[1],buf,4096);
            memset(buf,'\0',4097);
        }
    }
    close(pfd[1]);
    wait(NULL);
    fclose(fs);

    return 0;
}
