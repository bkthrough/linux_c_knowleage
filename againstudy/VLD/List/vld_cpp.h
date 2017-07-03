#ifndef __VLD_H
#define __VLD_H

#include"utility.h"

typedef struct MemNode
{
    char *pfile;
    size_t line;
    size_t size;
    struct MemNode *link;
}MemNode;

static MemNode *_AfxPMem; //head
static MemNode *_AfxPTail;  //tail

void* operator new(size_t sz, char *file, size_t line)
{
    void *result;
    size_t total_size = sz + sizeof(MemNode);
    MemNode *p = (MemNode*)malloc(total_size);
    assert(p != NULL);

    p->pfile = file;
    p->line = line;
    p->size = sz;
    p->link = NULL;

    if(_AfxPMem == NULL)
    {
        _AfxPMem = _AfxPTail = p;
    }
    else
    {
        _AfxPTail->link = p;
        _AfxPTail = p;
    }

    result = p+1;
    return result;
}

void operator delete(void *ptr)
{
    if(_AfxPMem == NULL)
    {
        abort();
    }

    MemNode *p = _AfxPMem;
    MemNode *q;
    while(p != NULL)
    {
        if(p+1 == ptr)
            break;
        q = p;
        p = p->link;
    }

    if(p == NULL)
    {
        cout<<"deleter pointer is invalid."<<endl;
        return;
    }
    if(p == _AfxPMem)
    {
        _AfxPMem = _AfxPMem->link;
    }
    else
    {
        q->link = p->link;
    }
    free(p);
    p = NULL;
}


void check_leak()
{
    MemNode *p = _AfxPMem;
    if(p == NULL)
    {
        cout<<"[OK] No Memory Leak."<<endl;
        return;
    }

    size_t count = 0;
    while(p != NULL)
    {
        count++;
        p = p->link;
    }
    printf("----------------------%d Location Memory Leak--------------------\n",count);

    count = 0;
    p = _AfxPMem;
    while(p != NULL)
    {

        count++;
        printf("[Error %d] at %p memory leak. file:%s, line=%d, size=%d\n",
               count, p+1, p->pfile, p->line, p->size);
        p = p->link;
    }
}

#endif
