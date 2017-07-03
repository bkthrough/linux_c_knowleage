#include <stdio.h>
//给定一个字符,找到字符在字符串出现的位置,返回这个地址
char *strrchr(char *string, int lable);
char *strrchr(char *string, int lable)
{

    char *str = string;
    char *new_str = NULL; 
    if(string == NULL){
	return string;
    }
    while(*str != '\0'){
	if((char)lable == *str){
	   new_str = str;
    	}
	str++;
    }	
    return new_str;



}
int main(int argc, char **argv)
{
    char str1[] = "hello,everyone!";
    char str2 = 'e' ;
    //char str3[] = {0};

    printf("%s\n",strrchr(str1, (int)str2));
    return 0;
}
