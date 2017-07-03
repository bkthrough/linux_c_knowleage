#include <apue.h>

#define LINE_AVA    1
#define WORD_AVA    2
#define CHAR_AVA    4

#define ONE_MAX     10485760

void do_work(int,char **);
void do_count(char *,int);

void do_work(int ac,char **av)
{
    int rst = -1;
    int how = 0;
    int loop=0,index=0;

    if(1 >= ac || NULL == av){
        return ;
    }
    for(loop=1;loop<ac;++loop){
        if('-' == av[loop][0]){
            index = 1;
            while('\0' != av[loop][index]){
                switch(av[loop][index]){
                   case 'w':
                       how |= WORD_AVA ;
                       break;
                   case 'l':
                       how |= LINE_AVA;
                       break;
                   case 'c':
                       how |= CHAR_AVA;
                       break;
                   default:
                       printf("Usage : %s <-w|c|l> <filename>\n",av[0]);
                       return ;
                       break;
                }//end switch
                ++index;
            }//end while
        }//end if
    }//end for

    if(0 == how){
        how = WORD_AVA | LINE_AVA | CHAR_AVA ;
    }

    for(loop=1;loop<ac;++loop){
        if('-' != av[loop][0]){
            do_count(av[loop],how);
        }
    }
    return;
}

void do_count(char *filename,int how)
{
    int fd = -1;
    int word=0,line=0,character=0,fsize=0,msize=0;
    int loopcnt = 0,index = 0;
    int isword = 1;
    struct stat statbuf;
    char *fbuf = NULL;

    if(NULL == filename){
        return ;
    }
    fd = open(filename,O_RDONLY,0600);
    if(0 > fd){
        return ;
    }
    if(fstat(fd,&statbuf)){
        printf("fstat error [%s]\n",strerror(errno));
        return;
    }
    fsize = character = statbuf.st_size;
    msize = ONE_MAX > fsize ? fsize : ONE_MAX ;

    loopcnt = fsize / msize + (fsize%msize > 0);

    fbuf = (char *)malloc(msize+1);
    if(NULL == fbuf){
        printf("malloc error [%s]\n",strerror(errno));
        return;
    }
    fbuf[msize] = '\0';

    while(loopcnt){
        memset(fbuf,'\0',msize);
        read(fd,fbuf,msize);
        index = 0;
        while(index < msize){
            if(' ' == fbuf[index] || '\t' == fbuf[index] || '\n' == fbuf[index]){
                if(!isword){
                    word += 1;
                    isword = 1;
                }
            }else{
                isword = 0;
            }
            if('\n' == fbuf[index]){
                line += 1;
            }
            index++;
        }
        loopcnt--;
        //if(' ' == fbuf[0] || '\t' == fbuf[0] || '\n' == fbuf[0]){
        //    word -= 1;
        //}
    }//end while
    if(LINE_AVA & how){
        printf(" %d ",line);
    }
    if(WORD_AVA & how){
        printf(" %d ",word);
    }
    if(CHAR_AVA & how){
        printf(" %d ",character);
    }
    printf("%s\n",filename);

    return;
}

int main(int ac,char **av)
{
    int fd = -1;

    do_work(ac,av);
    return 0;
}
