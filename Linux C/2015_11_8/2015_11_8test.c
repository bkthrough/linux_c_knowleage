#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#if 1

size_t my_strlen(const char *string);   // 字符串长度
//长度不受限
char *my_strcpy(char *des_str, const char *src_str);   //字符串拷贝
char *my_strcat(char *des_str, const char *src_str);   //字符串链接
int   my_strcmp(const char *string1, const char *string2);   //字符串的比较
//长度受限
//从src_str中拷贝num个字符到des_str中
char *my_strncpy(char *des_str, const char *src_str, size_t num);   
//从src_str中追加num个到des_str中
char *my_strncat(char *des_str, const char *src_str, size_t num);
//string1和string2比较num个字符
int my_strncmp(const char *string1, const char *string2);

//字符的查找，返回值为地址
char *my_strchr(const char *string, int ch);
//字符查找，返回值为下标
int find_index(const char *string, int ch);
//字符查找，最后一次出现的位置
char *strrchr(const char *string, int ch);
//字符串匹配
char *my_strstr(const char * string1, const char *string2);
//hello,everyoneworld
//
//everyone
//从头到尾匹配string中的字符，返回首次失配前能够匹配的字符个数
size_t my_strspn(const char *string, const char *accept);
//从头到尾匹配string中的字符，返回首次匹配前未能匹配的字符个数
size_t my_strcspn(const char *string, const char *reject);

//大小写字母转换
int tolower(int ch);   //大写转小写

int toupper(int ch);   //小写转大写

// A    65
//
// a    97

//内存操作
void *memcpy(void *dst_str, void *src_str, size_t length);

//    hello,world
//
//   src    dst


// 接口实现
///////////////////////////////////////////////////////////////////


size_t my_strlen(const char *string)   // 字符串长度
{
    int len = 0;
    const char *str = string;

    if(string == NULL){
        return len;
    }
    while(str[len++] != '\0');
   
    return len;
}

//长度不受限

char *my_strcpy(char *des_str, const char *src_str)   //字符串拷贝
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

char *my_strcat(char *des_str, const char *src_str)   //字符串链接
{
    char *des = des_str;
    const char *src = src_str;
    int des_len = 0;

    if(des_str == NULL || src_str == NULL){
        return NULL;
    }

    //    "hello"  hello\0
    //
    //    des

    des_len = my_strlen(des_str);
    des += des_len;   //让des指向\0

    // my_strcpy(des, src);
    while((*des++ = *src++) != '\0');

    return des_str;
}

int   my_strcmp(const char *string1, const char *string2)   //字符串的比较
{  
     const char *str1 = string1;
     const char *str2 = string2;

    // hello\0       str1
    //
    // hello,world!  str2 
    //
    // hello,world!  str1
    //
    // hello\0       str2

     assert((string1 != NULL) && (string2 != NULL));
     
     while(*str1 && *str2 && *str1 == *str2){
         str1++;
         str2++;
     }     

     return (*str1 - *str2);
}

//长度受限

//从src_str中拷贝num个字符到des_str中
char *my_strncpy(char *des_str, const char *src_str, size_t num)
{
     char *des = des_str;
     const char *src = src_str;

     if(des_str == NULL || src_str == NULL 
     || des_str == src_str || num <= 0){
         return des_str;
     }

     while( num-- && (*des++ = *src++) != '\0'){
         /*do nothing*/
     }

     return des_str;
   
}   
//字符的查找，返回值为地址
char *my_strchr(const char *string, int ch)
{
    const char *str = string;

    if(string == NULL){
        return NULL;
    }

    while(*str != '\0'){
        if(*str == (char)ch){
            return (char *)str;
        }
        str++;
    }
    return NULL;
}
//hello,world

//      w
//字符查找，返回值为下标
int find_index(const char *string, int ch)
{
    char *find = my_strchr(string, ch);
    if(find != NULL){
        return find - string;
    }else{ 
        return -1;
    }
}
//字符查找，最后一次出现的位置
char *strrchr(const char *string, int ch)
{
    const char *str = string;
    char *p_char = NULL;

    if(string == NULL){ 
        return p_char;
    }
    
    while(*str != '\0'){
        if(*str == (char)ch){ 
            p_char = (char *)str;
        }
        str++;
    }
    return p_char;
}
//字符串匹配
//char *my_strstr(const char * string1, const char *string2);
//hello,everyoneworld
//
//everyone
//从头到尾匹配string中的字符，返回首次失配前能够匹配的字符个数
size_t my_strspn(const char *string, const char *accept)
{
    const char *str = string;
    const char *acc = NULL;

    if(string == NULL || accept == NULL){ 
        fprintf(stderr, "argument is invalid!\n");
        exit(1);
    }
    
    //hello,world   string
    //
    //elho          accept
    //
    // 11 * 4
    //
    //
    while(*str != '\0'){
        acc = accept;
        while(*acc != '\0'){
            if(*acc == *str){
                break ;
            }
            acc++;
        }
        if(*acc == '\0'){
            return str - string;
        }
        str++;
    }
}

#if 0
//从头到尾匹配string中的字符，返回首次匹配前未能匹配的字符个数
size_t my_strcspn(const char *string, const char *reject);

//从src_str中追加num个到des_str中
char *my_strncat(char *des_str, const char *src_str, size_t num)
{
    return NULL;
}

//string1和string2比较num个字符
int strncmp(const char *string1, const char *string2)
{
    return NULL;
}
#endif
#endif

#if 1

int main(int argc, char **argv)
{
    char *str1 = "hello,world";
    char *str2 = "ehlo";
    char str3[40] = "welcome";
    
     //strncpy(str3, str1, 100);   //str3:hellome

     printf("accept count:%d\n", my_strspn(str1, str2));
     printf("reject count:%d\n", strcspn(str1, str2));


    return 0;
}

#endif

#if 0
void *Malloc(size_t size);

void *Malloc(size_t size)
{
    void *result = NULL;
 
    result = malloc(size);
    if(result == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    bzero(result, size);
    return result;
}

int main(int argc, char **argv)
{
    char *str1 = "adsasdasd";
    int len = 0;
    char *str2 = NULL;
    char str3[40] = "hello,world";
  
    len = strlen(str1);
    str2 = Malloc(len + 1);
 
    strcpy(str2, str1);
 
    //hello,worldadsasdasd\0
    //
    //adsasdasd\0

    strcat(str3, str1);
    printf("the str3:%s\n", str3);


    return 0;
}

#endif

#if 0

void *Malloc(size_t size);

void *Malloc(size_t size)
{
    void *result = NULL;
 
    result = malloc(size);
    if(result == NULL){
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    bzero(result, size);
    return result;
}

int main(int argc, char **argv)
{
    char *str1 = "hello,world";   //case1
    char str2[100] = "hello,world";    //case2  
    char str3[] = "hello,world";    //case3

    char *str4 = NULL;    //case4
 
    str4 = Malloc(20);
#if 0
    str4 = (char *)malloc(20);
    if(str4 == NULL){ 
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
#endif
    strcpy(str4, "hello,world");

   // int array[100] = {1};

    return 0;
}

#endif
