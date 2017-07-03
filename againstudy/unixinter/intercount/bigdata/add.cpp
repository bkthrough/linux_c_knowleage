#include "utili.h"

char *add(char *str1, char *str2)
{
    char *sum = NULL;
    char *result = NULL;
    char jinwei = '0';
    int len1 = 0;
    int len2 = 0;
    char c1 = '0';
    char c2 = '0';
    int i = 0;
    int j = 0;
    int k = 0;

    if(str1 == NULL || str2 == NULL){
        return sum;
    }
    len1 = strlen(str1);
    len2 = strlen(str2);
    sum = new char[len1+len2];
    for(i = len1-1, j = len2-1; ; --j, --i){
        if(i < 0 && j < 0){
            c1 = '0';
            c2 = '0';
        }else if(j < 0){
            c2 = '0';
            c1 = str1[i];
        }else if(i < 0){
            c1 = '0';
            c2 = str2[j];
        }else{
            c1 = str1[i];
            c2 = str2[j];
        }
        sum[k++] = (c1 + c2 + jinwei - '0' - '0' - '0') % 10 + '0';
        jinwei   = (c1 + c2 + jinwei - '0' - '0' - '0') / 10 + '0';
        if(jinwei == '0' && c1 == '0' && c2 == '0')
            break;
    }
    k = 0;
    result = new char[256]();
    for(i = strlen(sum)-1; i >= 0; --i){
        if(sum[i] != '0')
            break;
    }
    for(int j = i; j >= 0; --j)
        result[k++] = sum[j];

    return result;
}
