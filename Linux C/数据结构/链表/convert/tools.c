#include "tools.h"
#include <stdio.h>

void *Malloc(size_t length)
{
    void *result = malloc(length);
    if(result == NULL){
        fprintf(stderr,"free space can't malloc");
        exit(1);
    }
    return result;
}

