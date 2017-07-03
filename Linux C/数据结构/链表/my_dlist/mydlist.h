#ifndef _MYDLIST_H
#define _MYDLIST_H

#define TRUE  (1)
#define FALSE (0)
#define ZERO  (0)
#define ONE   (1)
typedef unsigned char Boolean;
typedef void (*Print_func)(void *value);

typedef struct Dlist_node{
    struct Dlist_node *prev;
    struct Dlist_node *next;
    void              *data;
}*Dlist_node;

typedef struct Dlist{
    struct Dlist_node *head;
    struct Dlist_node *tail;
    int               count;
    void (*free_node)(void *ptr);
    Boolean (*match)(void *value1,void *value2);
    void *(*copy_node)(void *value);
}*Dlist;
//接口实现
void free_list(void *ptr);
void free_tree(void *ptr);
void free_graph(void *ptr);
Dlist init_dlist(void);
void destroy_dlist(Dlist *dlist);//销毁链表
Boolean push_front(Dlist dlist,void *value);//头插
Boolean push_back(Dlist dlist,void *value);//尾插
Boolean pop_front(Dlist dlist);
Boolean pop_back(Dlist dlist);
//插入某节点前面
Boolean insert_prev(Dlist dlist,Dlist_node node,void *value);
//插入某节点后面
Boolean insert_next(Dlist dlist,Dlist_node node,void *value);
Boolean remove_dlist_node(Dlist dlist,Dlist_node node);
void show_dlist(Dlist dlist,Print_func print); //显示双端链表
Boolean get_front(Dlist dlist,void **value);
Boolean get_tail(Dlist dlist,void **value);
int get_dlist_count(Dlist dlist);//节点数量
#endif
