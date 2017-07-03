#ifndef __UTILI_H
#define __UTILI_H

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
using namespace std;

typedef enum{CPP_TO_C, C_TO_CPP}CONVERT_MODE;

#define UL unsigned long
#define DIR_LENGTH 256
#define INFO_LENGTH 1024

typedef enum
{
    NO_COMMENT_STATE,
    C_COMMENT_STATE,
    CPP_COMMENT_STATE,
    STR_STATE,
    END_STATE
}STATE_ENUM;

typedef struct 
{
    FILE *inputfile;
    FILE *outputfile;
    UL    ulstate;
}STATE_MACHINE;

extern  STATE_MACHINE  g_state;
extern  STATE_ENUM     g_str_pre_state;
extern  "C" void Do_Convert_CppToC();
extern  "C" void Do_Convert_CToCpp();

void InitStateMachine(FILE *inputfile, FILE *outputfile);
char ReadChar();
void WriteChar(char ch);
void WriteDoubleChar(char ch);
void WriteDoubleChar(char ch1, char ch2);



#endif
