#include "tools.h"
#include <stdlib.h>
#include <stdio.h>

void *Malloc(int size)
{
    void *result = NULL;
    result = malloc(size);
    if(result == NULL){
        fprintf(stderr,"no space to malloc");
        exit(1);
    }
    return result;
}

void *Realloc(void *ptr,int size)
{
    Realloc(ptr,size);
    if(ptr == NULL){
        fprintf(stderr,"no space to realloc");
        exit(1);
    }
    return ptr;
}
