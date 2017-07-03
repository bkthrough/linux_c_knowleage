#include <apue.h>

int main()
{
    char *buf = "hello,world";
    int fd = -1;

    fd = open("file.c",O_RDWR);
    write(fd,buf,strlen(buf));

    return 0;
}
