#pragma once

#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
using namespace std;


const char *write_fifo_name = "write_fifo";
const char *read_fifo_name = "read_fifo";
#define FILE_MODE O_CREAT|O_EXCL|S_IWUSR|S_IRUSR
