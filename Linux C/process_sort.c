#include <apue.h>

//非常粗糙的多进程排序，对文件进行分为两部分，然后分别排序，问题很大
//不过根据这个程序也收获了一些知识，比如：进程对文件的偏移量不共享，
//进程是对上一个进程偏移量的继续。
void sort(int *a,int left,int right)
{
    int i = 0;
    int j = 0;
    int tmp = 0;

    for(i = 0; i <= right-1; ++i){
        for(j = i+1; j <= right; ++j){
            if(a[i] > a[j]){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}
int main()
{
    FILE *fp = NULL;
    FILE *fp1 = NULL;
    char c;
    int block;
    struct stat fs;
    int fd = 0;
    int fd1 = 0;
    int *array = NULL;
    int i = 0;
    int length = 0;

    fp = fopen("sort","r");
    fp1 = fopen("deal","w");
    fd = fileno(fp);
    fd1 = fileno(fp1);
    stat("sort",&fs);
    array = (int *)malloc(sizeof(int) * (fs.st_size/2));
    block = fork();
    length = fs.st_size/2;
    if(block == 0){
        while(length--){
            c = fgetc(fp);
            if(c != ','){
                array[i] = atoi(&c);
                i++;
            }
        }
        sort(array,0,i-1);
        i = 1;
        while(array[i+1]){
            array[i] += 48;
            fputc(array[i],fp1);
            fputc(',',fp1);
            i++;
        }
        array[i] += 48;
        fputc(array[i],fp1);
    }
    else{
        printf("this is father:");
        while(length--){
            c = fgetc(fp);
            if(c != ','){
                array[i] = atoi(&c);
                i++;
            }
        }
        sort(array,0,i-1);
        lseek(fd,(fs.st_size/2),SEEK_SET);
        i = 0;
        while(array[i]){
            array[i] += 48;
            fputc(array[i],fp1);
            fputc(',',fp1);
            i++;
        }
    }
    close(fd);

    return 0;
}
