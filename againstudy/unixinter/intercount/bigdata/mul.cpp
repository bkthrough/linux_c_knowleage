#include "utili.h"

char *mul(char *str1, char *str2)
{
    int len1 = 0;
    int len2 = 0;
    int i    = 0;
    int j    = 0;
    int k    = 0;
    int index = 0;
    //int类型数组，这个很重要
    int *str= NULL;
    char *result;
    char c1;
    char c2;
    char jinwei = '0';

    if(str1 == NULL || str2 == NULL){
        return NULL;
    }
    len1 = strlen(str1);
    len2 = strlen(str2);
    str = new int[len1 + len2];
    for(i = 0; i < len1+len2; ++i)
        str[i] = '\0';
    for(i = len1-1; i >= 0; --i){
        for(j = len2-1; j >= 0; --j){
            index = len1-1-i + len2-1-j;
            //对应下标存放乘积
            str[index] += (str1[i]-'0') * (str2[j]-'0');
        }
    }
    for(i = 0; i < len1+len2; ++i){
        if(str[i] >= 10){
            //进位
            str[i+1] += str[i] / 10;
            str[i]   = str[i]%10;
        }
    }
    for(i = len1+len2-1; i >= 0; --i){
        if(str[i] != 0)
            break;
    }
    k = 0;
    result = new char[i+1];
    for(; i >= 0; --i){
        //转给char数组
        result[k++] = str[i] + '0';
    }

    return result;
}
