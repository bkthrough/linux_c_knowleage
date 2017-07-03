#include "utili.h"
bool is_zero(char *res)
{
    int len = strlen(res);

    for(int i = 0; i < len; ++i){
        if(res[i] != '0')
            return false;
    }
    return true;
}
char *div(char *str1, char *str2)
{
    //指向每一步做减法后的数组
    char *res = NULL;
    int len1 = 0;
    int len2 = 0;
    int develop_len = 0;
    int i = 0;
    int index;
    int k = 0;
    //存储做除法的结果
    int *array = NULL;
    //返回的数组
    char *result = NULL;

    array = new int[256 * 4];
    result = new char[256];
    for(int j = 0; j < 256; ++j){
        array[j] = 0;
        result[j] = 0;
    }
    len1 = strlen(str1);
    len2 = strlen(str2);
    if(len1 < len2){
        return result;
    }
    develop_len = len1 - len2;
    while(i < develop_len){
        str2[i + len2] = '0';
        ++i;
    }
    res = str1;
    for(;;){
        while(res[0] != '-'){
            res = sub(res, str2);
            if(res[0] != '-'){
                array[develop_len] += 1;
                index = develop_len;
                //如果大于10，那么就进位
                while(array[index] == 10){
                    array[index] = 0;
                    ++index;
                    array[index] += 1;
                }
                if(true == is_zero(res))
                    break;
            }else if(develop_len > 0){
                //如果是负数，就回退到上一次的res
                memmove(res, res+1, strlen(res)-1);
                memset(res+strlen(res)-1, 0, 1);
                res = sub(str2, res);
                break;
            }
        }
        //加0的长度没有了或者结果为0了，说明该退出
        if(develop_len == 0 || true == is_zero(res))
            break;
        //如果加的0多了，那么就删去后面的0
        if(develop_len > 0){
            --develop_len;
            str2[len2+develop_len] = '\0';
        }
    }
    for(i = 255; i >= 0; --i){
        if(array[i] != 0)
            break;
    }
    k = 0;
    for(int j = i; j >= 0; --j)
        result[k++] = array[j] + '0';

    return result;
}
