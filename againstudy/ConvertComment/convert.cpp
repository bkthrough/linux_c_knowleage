#include"utili.h"
extern "C" int ConvertComment(FILE *inputfile, FILE *outputfile);

void help();
int ConvertComment(FILE *inputfile, FILE *outputfile, CONVERT_MODE mode);

int main(int argc, char *argv[])
{
    char src_file[DIR_LENGTH];
    char dest_file[DIR_LENGTH];

    CONVERT_MODE mode = CPP_TO_C;

    int option;
    //./convert -s input.c -d output.c
    while((option = getopt(argc, argv, "s:d:mh")) != -1)
    {
        switch(option)
        {
        case 's':
            strcpy(src_file, optarg);
            break;
        case 'd':
            strcpy(dest_file, optarg);
            break;
        case 'm':
            mode = C_TO_CPP;
            break;
        case 'h':
            help();
            return 0;
        case '?':
            printf("Usage: convert [-m] -s src_file -d dest_file.\n");
            break;
        }
    }

    FILE *fpIn = NULL;
    FILE *fpOut = NULL;
    fpIn = fopen(src_file, "r");
    if(NULL == fpIn)
    {
        //cout<<"Open input.c file fail."<<endl;
        cout<<"Open "<<src_file<<"fail."<<endl;
        return -1;
    }
    fpOut =fopen(dest_file, "w");
    if(NULL == fpOut)
    {
        //cout<<"Open output.c file fail."<<endl;
        cout<<"Open "<<dest_file<<"fail."<<endl;
        return -1;
    }

    ConvertComment(fpIn, fpOut, mode);

    fclose(fpIn);
    fclose(fpOut);

    cout<<"Comment Convert Complete."<<endl;
    return 0;
}

void help()
{
    FILE *fp = fopen("help.txt","r");
    if(NULL == fp)
    {
        printf("Open help.txt file fail.\n");
        return;
    }

    char buffer[INFO_LENGTH];
    while(!feof(fp))
    {
        fgets(buffer, INFO_LENGTH, fp);
        printf("%s",buffer);
    }
    fclose(fp);
}

int ConvertComment(FILE *inputfile, FILE *outputfile, CONVERT_MODE mode)
{
    if(inputfile==NULL || outputfile==NULL)
    {
        printf("In function ConvertComment:argument invalid.\n");
        return -1;
    }

    InitStateMachine(inputfile, outputfile);

    if(mode == CPP_TO_C)
        Do_Convert_CppToC();
    else
        Do_Convert_CToCpp();
}






