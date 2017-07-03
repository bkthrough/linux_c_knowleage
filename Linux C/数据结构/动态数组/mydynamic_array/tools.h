#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//工具类接口
void *Malloc(size_t size);
void *Realloc(void *ptr,size_t size);
void swap(void *a, void *b, int length);

#endif
