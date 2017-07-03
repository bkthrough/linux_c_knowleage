#include"utili.h"

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


