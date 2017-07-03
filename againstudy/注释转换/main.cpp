#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "utili.h"
using namespace std;

void find_file(const char *src_dir, const char *dst_dir, base *b)
{
    char src[256]      = {0};
    char dst[256]      = {0};
    DIR *dirptr = NULL;
    struct dirent *entry;
    struct stat info;

    dirptr = opendir(src_dir);
    if(dirptr == NULL){
        //如果是文件就去处理
        b->deal_with_file(src_dir, dst_dir);
        return ;
    }
    mkdir(dst_dir, 0644);
    while(entry = readdir(dirptr)){
        //给出文件的相对路径
        sprintf(src, "%s/%s", src_dir, entry->d_name);
        sprintf(dst, "%s/%s", dst_dir, entry->d_name);
        stat(src, &info);
        cout << dst << endl;
        if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0){
            continue;
        }else if(S_ISDIR(info.st_mode)){
            //如果是文件夹，那么就创建，然后递归去找里面的文件
            mkdir(dst, 0644);
            find_file(src, dst, b);
        }else{
            //是文件，那么就去进行处理
            b->deal_with_file(src, dst);
        }
    }
}
int main(int argc, char *argv[])
{
    c C;
    cpp Cpp;
    char src_dir[256] = {0};
    char dst_dir[256] = {0};
    char src[256]     = {0};
    char get_src[256] = {0};
    char dst[256]     = {0};
    char mode[5]      = {0};
    char str[256]     = {0};
    char attr[20]     = {0};

#if default
    cout << "***************************************************\n";
    cout << "*  mode \"c\" 把c的注释类型转换为cpp的注释类型    *\n";
    cout << "\n";
    cout << "\n";
    cout << "*  mode \"cpp\" 把cpp的注释类型转换为c的注释类型  *\n";
    cout << "***************************************************\n";
    printf( "please input src_dir:");
    cin >> src_dir;
    printf( "please input dst_dir:");
    cin >> dst_dir;
    cout << "please choose mode:";
    cin >> mode;

#elif order
    int res = 0;
    //提取参数，分别提取-s -d -m 之后的参数
    while(0 < (res = getopt(argc, argv, "s:d:m:"))){
        switch(res){
            case 's':
                strcpy(src_dir, optarg);
                break;
            case 'd':
                strcpy(dst_dir, optarg);
                break;
            case 'm':
                strcpy(mode, optarg);
                break;
        }
    }

#endif
    if(0 == strncmp(mode, "cpp", strlen("cpp")))
        find_file(src_dir, dst_dir, &C);
    else if(0 == strncmp(mode, "c", strlen("c")))
        find_file(src_dir, dst_dir, &Cpp);

    return 0;
}
