#include"utili.h"

//extern "C" int ConvertComment(FILE *inputfile, FILE *outputfile);

#if 0
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
#endif
/////////////////////////////////////////////////////////////////
STATE_MACHINE  g_state;
STATE_ENUM     g_str_pre_state;

//void InitStateMachine(FILE *inputfile, FILE *outputfile);
//char ReadChar();
//void WriteChar(char ch);
//void WriteDoubleChar(char ch);
//void WriteDoubleChar(char ch1, char ch2);

void Do_Convert_CppToC();
void EventProc(char ch);
void EventProcAtNo(char ch);
void EventProcAtC(char ch);
void EventProcAtCpp(char ch);
void EventProcAtStr(char ch);
/////////////////////////////////////////////////////////////////
#if 0

int ConvertComment(FILE *inputfile, FILE *outputfile)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("In function ConvertComment:argument invalid.\n");
        return -1;
    }

    ///////////////////////////////////////////////////////////////
    //
    InitStateMachine(inputfile, outputfile);

    Do_Convert_CppToC();

    return 0;
}
void InitStateMachine(FILE *inputfile, FILE *outputfile)
{
    g_state.inputfile = inputfile;
    g_state.outputfile = outputfile;
    g_state.ulstate = NO_COMMENT_STATE;
}
char ReadChar()
{
    char ch = fgetc(g_state.inputfile);
}
void WriteChar(char ch)
{
    fputc(ch, g_state.outputfile);
}
void WriteDoubleChar(char ch)
{
    fputc(ch, g_state.outputfile);
    fputc(ch, g_state.outputfile);
}
void WriteDoubleChar(char ch1, char ch2)
{
    fputc(ch1, g_state.outputfile);
    fputc(ch2, g_state.outputfile);
}
#endif 
void Do_Convert_CppToC()
{
    char ch;
    while(g_state.ulstate != END_STATE)
    {
        ch = ReadChar();
        EventProc(ch);
    }
}

void EventProc(char ch)
{
    switch(g_state.ulstate)
    {
    case NO_COMMENT_STATE:
        EventProcAtNo(ch);
        break;
    case C_COMMENT_STATE:
        EventProcAtC(ch);
        break;
    case CPP_COMMENT_STATE:
        EventProcAtCpp(ch);
        break;
    case STR_STATE:
        EventProcAtStr(ch);
        break;
    default:
        break;
    }
}

////////////////////////////////////////////////////////
void EventProcAtNo(char ch)
{
    char nextch;
    switch(ch)
    {
    case '/':
        nextch = ReadChar();
        if(nextch == '/')    //C++ Comment
        {
            WriteChar(ch);
            WriteChar('*');   //   // --> /*
            g_state.ulstate = CPP_COMMENT_STATE;
        }
        else if(nextch == '*') //C Comment
        {
            WriteDoubleChar('/','*');
            g_state.ulstate = C_COMMENT_STATE;
        }
        else
        {}
        break;
    case '"':
        WriteChar(ch);
        g_str_pre_state = NO_COMMENT_STATE;
        g_state.ulstate = STR_STATE;
        break;
    case EOF:
        g_state.ulstate = END_STATE;
        break;
    default:
        WriteChar(ch);
        break;
    }
}
void EventProcAtC(char ch)
{
    char nextch;
    switch(ch)
    {
    case '*':
        nextch = ReadChar();
        if(nextch == '/')
        {
            WriteDoubleChar('*','/');
            g_state.ulstate = NO_COMMENT_STATE;
        }
        else
        {
            WriteChar(ch);
        }
        break;
    case '/':
        nextch = ReadChar();
        if(nextch == '/')    //   /*  //  */
        {
            WriteDoubleChar(' ');
        }
        break;
    default:
        WriteChar(ch);
        break;
    }
}
void EventProcAtCpp(char ch)
{
    char nextch;
    switch(ch)
    {
    case EOF:
        WriteChar('*');
        WriteChar('/');
        g_state.ulstate = END_STATE;
        break;
    case '\n':
        WriteChar('*');
        WriteChar('/');
        WriteChar(ch);
        g_state.ulstate = NO_COMMENT_STATE;
        break;
    case '/':
        nextch = ReadChar();
        if(nextch=='/' || nextch=='*') //  // // or // /*
        {
            WriteDoubleChar(' ');
        }
        else
        {
            WriteChar(ch);
            WriteChar(nextch);
        }
        break;
    case '*':
        nextch = ReadChar();
        if(nextch == '/')    //  //  */
        {
            WriteDoubleChar(' ');
        }
        else
        {
            WriteChar(ch);
            WriteChar(nextch);
        }

        break;
    case '"':
        WriteChar(ch);
        g_str_pre_state = CPP_COMMENT_STATE;
        g_state.ulstate = STR_STATE;
        break;
    default:
        WriteChar(ch);
        break;
    }
}
void EventProcAtStr(char ch)
{
    switch(ch)
    {
    case '"':
        WriteChar(ch);
        //g_state.ulstate = NO_COMMENT_STATE;
        g_state.ulstate = g_str_pre_state;
        break;
    default:
        WriteChar(ch);
        break;
    }
}


