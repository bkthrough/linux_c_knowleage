#include <stdio.h>
//拷贝num个字符
char *my_strncpy(char *des_str, const char *src_str, size_t num);
char *my_strncpy(char *des_str, const char *src_str, size_t num)
{
    char *des = des_str;
    const char *src = src_str;
    int i = 0;

    if(des == NULL || src == NULL || des == src || num < 0){
	return des_str;
    }else{

//      while(num-- && (*des++ = *src++) != "\0"){};
	for(i = 0; i < num; i++){
	    des[i] = src[i];
	   // src++;
	   // des++;
	}
    }
   
    return des_str;
}

int main(int argc, char **argv)
{
    char *str1 = "hello,world";
    char str2[] = {0};
    my_strncpy(str2, str1, 5);
    printf("the str2 is %s\n",str2);

    return 0;
}
