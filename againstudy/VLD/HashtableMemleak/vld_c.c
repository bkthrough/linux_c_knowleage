#include "hashtable.h"
#include "vld_c.h"

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
    if(result == n){
        hashtable[index] = NULL;
    }else if(n->link == NULL){
        return ;
    }else{
        n->link = n->link->link;
    }

    free_node(result);
    result = NULL;
    n = NULL;
}
