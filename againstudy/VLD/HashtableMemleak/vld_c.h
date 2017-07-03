#pragma once

#include <stdio.h>
#include <malloc.h>

void *__malloc(size_t sz, int len, const char *filename);
void __free(void *p);
//必须在下面宏替换，不然__malloc函数里面调用的malloc函数也被宏替换了,会导致死循环
#define malloc(sz) __malloc(sz, __LINE__, __FILE__)
#define free(ptr)  __free(ptr)

