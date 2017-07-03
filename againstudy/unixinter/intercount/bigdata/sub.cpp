#include "utili.h"

#define STR1BIGGER  (1)
#define STR2BIGGER  (2)
#define EQUAL       (3)

int k = 0;
inline static int choosebigger(char *str1, char *str2, int len1, int len2)
{
    int i = 0;

    if(len1 < len2){
        return STR2BIGGER;
    }else if(len1 > len2){
        return STR1BIGGER;
    }
    for(i = 0; i < len1; ++i){
        if(str1[i] != str2[i])
            break;
    }
    if(i == len1)
        return EQUAL;
    return str1[i] > str2[i] ? STR1BIGGER : STR2BIGGER;
}
inline static char *do_sub(char *str1, char *str2, int len1, int len2)
{
    char *str   = NULL;
    int i = 0;
    int j = 0;
    int flag    = 0;
    char c1;
    char c2;
    char jinwei = '1';

    str = new char [len1+len2];
    for(i = len1-1, j = len2-1; i >= 0 || j >= 0; --i, --j){
        if(i < 0){
            c1 = '0';
            c2 = str2[j];
        }else if(j < 0){
            c2 = '0';
            c1 = str1[i];
        }else{
            c1 = str1[i];
            c2 = str2[j];
        }
        if(c1 - c2 + flag * (jinwei - '0') < 0){
            str[k++] = c1 + 10 - c2 + flag * (jinwei - '0') + '0';
            flag = -1;
        }else{
            str[k++] = c1 - c2 + flag * (jinwei - '0') + '0';
            flag = 0;
        }
    }
    return str;
}
char *sub(char *str1, char *str2)
{
    int len1    = 0;
    int len2    = 0;
    int i       = 0;
    int j       = 0;
    int big     = 0;
    char *result= NULL;
    char *str   = NULL;

    if(str1 == NULL || str2 == NULL)
        return NULL;
    len1 = strlen(str1);
    len2 = strlen(str2);
    big = choosebigger(str1, str2, len1, len2);
    if(big == STR1BIGGER)
        str = do_sub(str1, str2, len1, len2);
    else if(big == STR2BIGGER)
        str = do_sub(str2, str1, len2, len1);
    else if(big == EQUAL){
        result = new char[1];
        result[0] = '0';
        return result;
    }

    result = new char[k];
    for(i = k-1; i >= 0; --i){
        if(str[i] != '0')
            break;
    }
    if(big == STR2BIGGER){
        ++i;
        str[i] = '-';
    }
    k = 0;
    for(j = i; j >= 0; --j){
        result[k++] = str[j];
    }
    k = 0;

    return result;
}
