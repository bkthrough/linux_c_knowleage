#ifndef MALLOC_H_
#define MALLOC_H_
#include "global.h"

//malloc2的基础上，初始化空间
void* mallocs(size_t size);
//申请空间，作出错处理
void* malloc2(size_t size);
void* realloc2(void* ptr, size_t size);
void free2(void* ptr);
void frees(int size, ...);

#endif /* MALLOC_H_ */
