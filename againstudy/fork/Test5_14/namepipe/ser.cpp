#include"utili.h"

int main(int argc, char *argv[])
{
    int write_fd;
    int read_fd;

    if(access(write_fifo_name,F_OK) == -1)
    {
        int res = mkfifo(write_fifo_name,FILE_MODE);
        if(res == -1)
        {
            printf("make write fifo error.\n");
            exit(1);
        }
    }

    write_fd = open(write_fifo_name, O_WRONLY);
    if(write_fd == -1)
    {
        printf("open write fifo error.\n");
        unlink(write_fifo_name);
        exit(1);
    }

    printf("Server Wait Client Connect.......\n");
    while(1)
    {
        read_fd = open(read_fifo_name, O_RDONLY);
        if(read_fd != -1)
            break;
        sleep(1);
    }
    printf("Client Connect Server OK.\n");
    
    char sendbuf[256];
    char recvbuf[256];
    while(1)
    {
        printf("Ser:>");
        scanf("%s",sendbuf);
        if(strcmp(sendbuf,"quit") == 0)
        {
            unlink(write_fifo_name);
            break;
        }
        write(write_fd, sendbuf, strlen(sendbuf)+1);

        read(read_fd, recvbuf, 256); // 
        printf("Cli:>%s\n",recvbuf);
    }

    return 0;
}
















