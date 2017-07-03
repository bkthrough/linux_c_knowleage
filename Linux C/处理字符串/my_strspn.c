#include <stdio.h>
//比较两个字符串,string只要有一个能和accept匹配的字符就继续比较accept的第二个字节
//直到有没有匹配的,那么就返回能匹配的个数
size_t my_strspn(const char *string, const char *accept)
{

    int num = 0;
    const char *str = string;
    const char *acc = NULL;
//string = hello,world
//accept = lhaerd
// 
    while(*str != '\0'){
	acc = accept;
	while(*acc != '\0'){
	    if(*str == *acc){
		break;
	    }
	    acc++;
	}
	str++;
	
    }
    return str
}

int main(int argc, char **argv)
{
    char *string = "hello,world";
    char *accept = "lhaerd";
    int count = 0;
    count = my_strspn(string, accept);
    printf("%d\n", count);
    return 0;
}
