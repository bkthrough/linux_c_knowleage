#include <stdio.h>

#define TRUE   (1)
#define FALSE  (0)

typedef unsigned char Boolean;

Boolean del_substr(char *string, const char *substr);
static char *my_strstr(char *string, const char *substr);
static int my_strlen(const char *string);
static char *my_strcpy(char *des_str, const char *src_str);

static char *my_strcpy(char *des_str, const char *src_str)
{
    char *des = des_str;
    const char *src = src_str;

    if(des_str == NULL || src_str == NULL
    || des_str == src_str){
        return des_str;
    }

    while((*des++ = *src++) != '\0'){
        /*do nothing*/
    }
    return des_str;
}

static int my_strlen(const char *string)
{
    int len = 0;
    const char *str = string;

    if(string == NULL){
        return len;
    }

    while(*str != '\0'){
        str++;
        len++;
    }

    return len;
}


static char *my_strstr(char *string, const char *substr)
{
    char *str = string; 
    const char *sub = substr;

    while(*str != '\0' && *sub != '\0'){
        if(*str == *sub){
           //如果两个指针指向的空间内容相等，则都向后移动
           str++;
           sub++;
        }else{
           str -= (sub - substr - 1);
           //  hello,everyoneworld
           //
           //        everyone\0
           sub = substr;
        }
    }
   
    if(*sub == '\0'){    //被匹配的串完全找到
        return str -= (sub - substr);
    }
    return NULL;
}


Boolean del_substr(char *string, const char *substr)
{
    char *find_index = NULL;
    char *copy_start = NULL;
    char *str = string;
    const char *sub = substr;

    //1.进行参数检测
    if(string == NULL || substr == NULL){
        return FALSE;
    }
    //2.查找substr是否存在于string
    //    3.如果找到substr，则在string中进行删除操作；
    //    否则直接返回FALSE;
    find_index = my_strstr(str, sub);
    if(find_index == NULL){
        return FALSE;
    }else{    //找到后删除
        //hello,everyoneworld
        //
        //      everyone
        copy_start = find_index + my_strlen(sub);
        my_strcpy(find_index, copy_start);
        return TRUE;
    }
}

int main(int argc, char **argv)
{
    char str1[] = "hello, everyoneworld!";
    char str2[] = "everyone";
    Boolean find = FALSE;    

    //"hello, world!"  ==> result

    find =  del_substr(str1, str2);
    if(find == TRUE){
        printf("str2 found! the result string is :%s\n", str1);
    }else{
        printf("str2 is not located in str1!\n");
    }

    return 0;
}
