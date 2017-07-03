#include "hash.h"
#include "iter.h"
#include "tools.h"
Boolean is_hash_match(Hash *hash,Iter iter,void *value,int index);
Boolean is_hash_match(Hash *hash,Iter iter,void *value,int index)
{
    foreach(iter,hash->table[index]){
        if(hash->hash_match){
            if(hash->hash_match(value,iter.ptr)){
                break;
            }
            else
                return FALSE;
        }
        else{
            if(*(int *)value == *(int *)iter.ptr){
                break;
            }
            if(iter.ptr == NULL){
                return FALSE;
            }
        }
    }
    if(iter.ptr == NULL){
        return FALSE;
    }
    else{
        return TRUE;
    }
}
void *iter_head(Iter *iter,Dlist dlist)
{
    if(iter == NULL || dlist == NULL ){
        return NULL;
    }
    iter->ptr = dlist->head->data;
    iter->current_node = dlist->head;
    iter->node = dlist->head->next;
    return iter->ptr;
}
void *iter_next(Iter *iter,Dlist dlist)
{
    if(iter == NULL || dlist == NULL || dlist->count == ZERO || iter->node == NULL){
        return NULL;
    }
    iter->ptr = iter->node->data;
    iter->current_node = iter->node;
    iter->node = iter->node->next;
    return iter->ptr;
}
Hash    *init_hash(int b_size, Hash_func h_func)      //hash表的初始化
{
    int i = 0;

    Hash *hash = (Hash *)Malloc(sizeof(Hash));
    hash->bucket_size = b_size;
    hash->element_count = 0;
    hash->hash_free = NULL;
    hash->hash_match = NULL;
    hash->hash_func = h_func;
    //申请桶的个数由b_size决定
    hash->table = (Dlist **)Malloc(sizeof(Dlist *) * b_size);
    for(i = 0;i < b_size; ++i){
        hash->table[i] = init_dlist();
    }
    //bzero(hash->table, sizeof(Dlist *) * b_size);
    //关于双端链表的初始化在被使用的时候进行，这样做是为了节省效率

    return hash;
}
#if 0
Hash    *init_hash(int b_size, Hash_func h_func)      //hash表的初始化
{
    int i;

    Hash *hash = (Hash *)Malloc(sizeof(Hash));
    hash->bucket_size = b_size;
    hash->element_count = 0;
    hash->hash_free = NULL;
    hash->hash_match = NULL;
    hash->hash_func = h_func;
    hash->table = (Dlist **)Malloc(sizeof(Dlist *) * b_size);
    for(i = 0;i < b_size; ++i){
        hash->table[i] = init_dlist();
    }
    //bzero(hash->table,sizeof(Dlist *)*b_size);
    return hash;
}
#endif
void    destroy_hash(Hash **hash)                     //hash表的销毁
{
    int i = 0;
    int size = (*hash)->bucket_size;
    if(hash == NULL || *hash == NULL){
        return ;
    }
    for(i = 0; i < size; ++i){
        destroy_dlist(&((*hash)->table[i]));
    }
    free((*hash)->table);
    free((*hash));
    *hash = NULL;
}
Boolean hash_insert(Hash *hash, const void *value)    //hash表的插入
{
    int i;
    if(hash == NULL || value == NULL ){
        return FALSE;
    }
    //找到节点所在的数组,然后查到链表后面.
    i = hash->hash_func(value) % (hash->bucket_size);
    if(hash_search(hash,value)){
        hash->table[i]->repeat++;
    //    return TRUE;
    }
    if(hash->table[i]->repeat == 0){
        hash->table[i]->repeat++;
    }
    //if(hash->table[i] == NULL){
        //hash->table[i] = init_dlist();
    //    hash->table[i]->repeat++;
    //}
    push_back(hash->table[i],(void *)value);
    hash->element_count++;
    return TRUE;
}
Boolean hash_search(Hash *hash, const void *value)    //hash表的查找
{
    int index;
    int i;
    Iter iter;
    if(hash == NULL || value == NULL){
        return FALSE;
    }
    //先查找到所在的数组位置,在定位到链表的位置.
    index = hash->hash_func(value) % (hash->bucket_size);
    if(hash->table[index] == NULL || hash->table[index]->head == NULL){
        return FALSE;
    }
    return is_hash_match(hash,iter,(void *)value,index);
}
Boolean hash_remove(Hash *hash, const void *value)    //hash表的删除
{
    Iter iter;
    int i;
    int index;
    if(hash == NULL || value == NULL){
        return FALSE;
    }
    index = hash->hash_func(value) % hash->bucket_size;
    if(is_hash_match(hash,iter,(void *)value,index)){
        remove_dlist_node(hash->table[index],iter.current_node);
        hash->element_count--;
        return TRUE;
    }
    else
        return FALSE;
}
Boolean     get_element_count(const Hash *hash,int *index)           //得到hash表的元素数量
{
    if(hash == NULL || index == NULL){
        return FALSE;
    }
    *index = hash->element_count;
    return TRUE;
}
void    show_hash_table(const Hash *hash,Print_func print)             //显示hash表的元素信息
{
    Iter iter;
    int i;
    if(hash == NULL || hash->element_count == ZERO){
        return ;
    }
    for(i = 0;i < hash->bucket_size; ++i){
        show_dlist(hash->table[i],print);
        printf("\n");
    }
}
