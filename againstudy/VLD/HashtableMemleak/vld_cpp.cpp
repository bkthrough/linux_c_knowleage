//要注意头文件放置的位置，hashtable放在vld_c.h下面会造成malloc被替换
#include "hashtable.h"
#include "vld_c.h"
#include "vld_cpp.h"

void check_leak()__attribute__((destructor));
void *__malloc(size_t sz, int len, const char *filename)
{
    void *result = NULL;
    int size = sz + sizeof(MemNode);
    MemNode *n = create_node(size);

    fill_node(sz, len, n, filename);
    link_node(n);
    result = n+1;

    return result;
}
void __free(void *p)
{
    MemNode *n = NULL;
    void *result = NULL;
    int index;

    n = (MemNode *)p;
    result = n - 1;
    index = Hash(result);
    n = hashtable[index];
    //找到前一个节点
    while(result != n->link && n->link != NULL){
        n = n->link;
    }
    if(result == n)
        hashtable[index] = NULL;
    else if(n->link == NULL)
        return ;
    else
        n->link = n->link->link;

    free_node(result);
    result = NULL;
    n = NULL;
}

void *operator new(size_t sz, int line, const char *file)
{
    void *result = NULL;
    MemNode *n   = NULL;
    int size     = 0;

    size = sz + sizeof(MemNode);
    n = create_node(size);
    fill_node(sz, line, n, file);
    link_node(n);
    result = n+1;

    return result;
}

void *operator new[](size_t sz, int line, const char *file)
{
    void *result = NULL;
    MemNode *n = NULL;
    int size = 0;

    size = sz + sizeof(MemNode);
    n = create_node(size);
    fill_node(sz, line, n, file);
    link_node(n);
    result = n+1;

    return result;
}

void operator delete(void *ptr)
{
    MemNode *n = (MemNode *)ptr;
    MemNode *result;
    int     index;

    if(n == NULL){
        return ;
    }
    result = n-1;
    index = Hash(result);
    n = hashtable[index];
    while(n->link != ptr && n->link != NULL){
        n = n->link;
    }
    if(n == result){
        hashtable[index] = NULL;
    }else if(n->link == NULL){
        return ;
    }else{
        n->link = n->link->link;
    }
    free_node(result);
}
void operator delete[](void *ptr)
{
    MemNode *n = (MemNode *)ptr;
    MemNode *result;
    int     index;

    if(n == NULL){
        return ;
    }
    result = n-1;
    index = Hash(result);
    n = hashtable[index];
    while(n->link != ptr && n->link != NULL){
        n = n->link;
    }
    if(n == result){
        hashtable[index] = NULL;
    }else if(n->link == NULL){
        return ;
    }else{
        n->link = n->link->link;
    }
    free_node(result);
}
