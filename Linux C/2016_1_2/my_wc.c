#include <apue.h>

//三个参数分表表示1 2 4这样就可以用一个变量来表示参数了，比如7表示wcl
//1表示w
#define WORD_FLAG  1      //w
#define COUNT_FLAG 2      //c
#define LINE_FLAG  4      //l
#define RULE_SIZE  10245760
#define ZERO       0

void do_work(char **,int);
void do_exe(char *,int);

void do_work(char *argv[],int argc)
{
    int i;
    int index = 0;
    int j = 0;

    for(i = 1; i < argc; ++i){
        //如果是'-'那么就判断是什么参数
        if(argv[i][j] == '-'){
            j++;
            while(argv[i][j]){
                //判断w，l，c或者都不是。让一个变量和它们取或
                switch(argv[i][j]){
                    case 'l':
                        index |= LINE_FLAG;
                        break;
                    case 'w':
                        index |= WORD_FLAG;
                        break;
                    case 'c':
                        index |= COUNT_FLAG;
                        break;
                    default:
                        printf("%s [-w|c|l]..[FILE]\n",argv[0]);
                        break;
                }//switch end
                j++;
            }//while end
        }//if end
    }//for end
    //如果index是0那么就置为7
    if(index == ZERO){
        index |= COUNT_FLAG;
        index |= WORD_FLAG;
        index |= LINE_FLAG;
    }
    //对每个参数分别进行计算
    for(i = 1; i < argc; ++i){
        if(argv[i][0] != '-'){
            do_exe(argv[i],index);
            printf("\n");
        }
    }
}
void do_exe(char *filename,int index)
{
    int fd = -1;
    //栈上申请结构体
    struct stat filestat;
    int size;
    int read_count;
    int flag = 0;
    char buf[RULE_SIZE+1];
    int i = 0;
    int isword = 1;
    int byte = 0;
    int word = 0;
    int line = 0;
    int fd1 = -1;
    int get_size;

    //一定要注意赋值的时候要加括号，不然就出错了
    fd = open(filename,O_RDONLY,0644);
    if(fd == -1){
        printf("%d\n",fd);
        printf("%d error problem\n",errno);
        return ;
    }
    //fstat返回0则说明正常
    if(!fstat(fd,&filestat)){
        size = filestat.st_size;
    }
    //返回要读取的次数
    if(size % RULE_SIZE){
        flag = 1;
    }
    //读取次数
    read_count = size/RULE_SIZE + flag;
    //得到字符数量
    get_size = size;
    //取较小的作为读入标准
    size = size > RULE_SIZE ? RULE_SIZE : size;

    while(read_count--){
        //初始化为0
        memset(buf,'\0',size);
        read(fd,buf,size);
        //把最后置为空
        buf[size] = '\0';
        //从头开到size统计单词和字符出现的次数
        while(i < size){
            if(buf[i] == '\n'){
                line++;
            }
            //判断是否是空格并且前面是否有字符，如果是空格并且前面有字符
            //那么就让isword置0，并且word++
            if(buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n'){
                if(isword){
                    isword = 0;
                    word++;
                }
            }
            //如果有字符那么就让isword置1；
            else{
                isword = 1;
            }
            i++;
        }//while end  读取规定字符结束
    }//while end  读取所有字符结束

    if(index & LINE_FLAG){
        printf(" %d ",line);
    }
    if(index & WORD_FLAG){
        printf("%d ",word);
    }
    if(index & COUNT_FLAG){
        printf("%d ",get_size);
    }
    printf("%s",filename);
}
int main(int argc,char *argv[])
{
    do_work(argv,argc);

    return 0;
}
