#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "fifo.h"
using namespace std;

int main()
{
    int res;
    int read_fd;
    int write_fd;
    char buf[256] = {0};

    //res = mkfifo(read_fifo, O_CREAT |  0644);
    //if(res != 0){
    //    cout << "mkfifo error!" << endl;
    //    exit(1);
    //}
    //res = mkfifo(write_fifo, O_CREAT | 0644);
    //if(res != 0){
    //    cout << "mkfifo error!" << endl;
    //    exit(1);
    //}
    read_fd = open(write_fifo, O_RDONLY);
    write_fd = open(read_fifo, O_WRONLY);
    while(1){
        read(read_fd, buf, 256);
        cout << buf;
        read(0, buf, 256);
        write(write_fd, buf, strlen(buf)+1);
    }

    return 0;
}
