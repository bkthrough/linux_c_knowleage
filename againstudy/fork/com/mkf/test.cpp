#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fifo.h"

int main()
{
    open(read_fifo, O_RDWR);
}
