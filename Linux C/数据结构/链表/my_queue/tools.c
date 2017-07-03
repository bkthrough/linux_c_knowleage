#include "tools.h"

void *Malloc(size_t length)
{
    void *result;
    result = malloc(length);
    if(result == NULL){
        fprintf(stderr,"no space to malloc");
        exit(1);
    }
    return result;
}

void swap(void *ptr1,void *ptr2,size_t length)
{
    void *temp = Malloc(length);
    memcpy(temp,ptr1,length);
    memcpy(ptr1,ptr2,length);
    memcpy(ptr2,temp,length);
}
