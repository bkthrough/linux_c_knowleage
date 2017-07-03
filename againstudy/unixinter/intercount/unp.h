#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
using namespace std;

#define MAX_LEN 256

typedef enum{ADD, SUB, MUL, DIV, QUIT}OPER_STATE;

struct Oper
{
    OPER_STATE oper;
    char       op1[256];
    char       op2[256];
};
