#include"utili.h"

int main()
{
    int write_fd, read_fd;
    if(access(read_fifo_name,F_OK) == -1)
    {
        int res = mkfifo(read_fifo_name, FILE_MODE);
        if(res == -1)
        {
            printf("make read fifo error.\n");
            exit(1);
        }
    }
    read_fd = open(write_fifo_name, O_RDONLY);
    if(read_fd == -1)
    {
        printf("open read fifo error.\n");
        unlink(read_fifo_name);
        exit(1);
    }

    write_fd = open(read_fifo_name, O_WRONLY);
    if(write_fd == -1)
    {
        printf("open write fifo error.\n");
        exit(1);
    }
    printf("Connect Server Ok.\n");

    char sendbuf[256];
    char recvbuf[256];

    while(1)
    {
        read(read_fd, recvbuf, 256);
        printf("Ser:>%s\n",recvbuf);
        printf("Cli:>");
        scanf("%s",sendbuf);
        if(strcmp(sendbuf,"quit") == 0)
        {
            unlink(read_fifo_name);
            break;
        }
        write(write_fd, sendbuf, strlen(sendbuf)+1);
    }
    return 0;
}















