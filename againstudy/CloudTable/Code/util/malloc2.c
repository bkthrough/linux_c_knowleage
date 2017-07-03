#include "malloc2.h"
#include "log.h"

/** The handler for out of memory situation **/
void oom(size_t size)
{
    logg(EMERG, "The Memory Allocation has failed by allocating %d byte!!!!", size);
    sleep(1);
    abort();
}

void* mallocs(size_t size)
{
    size = size + 1;
    void* ptr = malloc2(size);
    memset(ptr, 0, size);
    return ptr;
}

/** malloc2 is safe implementaion of malloc, will sum the total usage of memory for information **/
void* malloc2(size_t size)
{
    void* ptr = malloc(size);
    if(ptr == NULL) 
    {
        oom(size);
    }
    return ptr;
}

void* realloc2(void* ptr, size_t size)
{
    void *newptr = realloc(ptr, size);
    if (newptr == NULL)
    {
        oom(size);
    }
    return newptr;
}

void free2(void* ptr)
{
    if(ptr != NULL)
    {
        free(ptr);
    }
}

/** Free a bunch of pointers **/
void frees(int size, ...)
{
    va_list ap;
    int i=0;
    va_start(ap, size);
    for(i=0; i<size; i++)
    {
        void* ptr = va_arg(ap, void*);
        free2(ptr);
    }
}


