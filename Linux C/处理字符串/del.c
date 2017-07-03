#include <stdio.h>
#include <stdlib.h>
int kmp(const char *str1,const char *str2);
char *del(char *str1,const char *str2,int index);
//kmp，用来找到相等的部分，如果相等，则返回开始比较的位置index，不相等返回NULL
int kmp(const char *str1,const char *str2)
{
    int i = 0;
    int j = 0;
    while(str1[i]){
        if(str1[i] == str2[j]){
            i++;
            j++;
            if(str2[j] == '\0'){
                return i-j;
            }
        }
        else if(str1[i] != str2[j]){
            j = 0;
            i++;
        }
    }
    return 0;
}
//删除相同的部分
char *del(char *str1,const char *str2,int index)
{
    int m;
    int n;
    int i;
    for(m = 1;str1[m];++m);
    for(n = 1;str2[n];++n);
    for(i = index;i < m-n;++i){
        str1[i] = str1[i+n];
    }
    for(i = m-n;i < m;++i){
        str1[i] = ' ';
    }
    return str1;
}
int main(int argc,char *argv[])
{
    int i;
    int j;
    i = kmp(argv[1],argv[2]);
    printf("%s\n",del(argv[1],argv[2],i));
    return 0;
}


















    #if 0
    int i;
    int k;
    int m;
    int n;
    int index;
    if(argc != 3){
        fprintf(stderr,"input error");
    }
    for(i = 1;argv[1][i];++i);
    while(argv[1][k] != '\0'){
        if(argv[1][k] != argv[2][m]){
            m = 0;
            k++;
        }
        else if(argv[1][k] == argv[2][m]){
            m++;
            k++;
            if(argv[2][m] == '\0'){
                index = k-m;
                break;
            }
        }
    }
    for(n = index;n < i-index+m;n++){
        argv[1][n] = argv[1][n+m];
    }
    printf("%s",argv[1]);
    return 0;
}
    #endif

