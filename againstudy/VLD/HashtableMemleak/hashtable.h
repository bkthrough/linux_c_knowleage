#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <malloc.h>
#include <stdio.h>
#include <assert.h>

#define HASHSIZE   301
typedef struct MemNode
{
    const char *pfile;
    size_t     line;
    size_t     sz;
    struct MemNode *link;
}MemNode;

MemNode *hashtable[HASHSIZE] = {0};

static size_t Hash(void *p)
{
    return ((size_t)p) % HASHSIZE;
}

MemNode *create_node(size_t size)
{
    MemNode *p = (MemNode *)malloc(size);
    assert(p != NULL);
    return p;
}

void free_node(void *p)
{
    free(p);
    p = NULL;
}

void fill_node(int size, int line, MemNode *n, const char *file)
{
    n->sz = size;
    n->line = line;
    n->pfile = file;
    n->link = NULL;
}

void link_node(MemNode *n)
{
    size_t index = Hash(n);

    if(hashtable[index] == NULL){
        hashtable[index] = n;
    }else{
        n->link = hashtable[index];
        hashtable[index] = n;
    }
}

void check_leak()
{
    int i = 0;
    int flag = 0;
    MemNode *n;

    for(i = 0; i < HASHSIZE; ++i){
        n = hashtable[i];
        while(n != NULL){
            flag = 1;
            printf("warning: No. %d in %s has leak.\n", n->line,
                   n->pfile);
            n = n->link;
        }
    }
    if(flag == 0){
        printf("this is no leak.\n");
    }
}

#endif






