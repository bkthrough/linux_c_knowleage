#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE (0)
#define TRUE  (1)
typedef char boolean;
typedef struct node{
    int x;
    struct node *next;
}*list_head,p_node;
p_node *input(void);
void print(p_node *p);
void *Malloc(size_t size);
boolean push_front(list_head head,int value);
boolean push_back(list_head head,int value);
boolean pop_front(list_head head);
boolean pop_back(list_head head);
boolean insert_node(list_head head,p_node *p,int value);
boolean find_node(list_head head,int value,p_node **p);
p_node *binary(list_head head);
void destroyed(list_head *head);
p_node *binary(list_head head)
{
    p_node *p = head->next;
    p_node *q = head->next;
    while(p->next&&p->next->next){
        p = p->next->next;
        q = q->next;
    }
    return q;
}
void destroyed(list_head *head)
{
    if(head == NULL||*head == NULL)
        return ;
    p_node *p = *head;
    p_node *q = NULL;
    while(p->next){
        q = p;
        free(q);
        q = NULL;
        p = p->next;
    }
    *head = NULL;
}
void sort_list_ascend(list_head head);
void sort_list_ascend1(list_head head);
void swap(p_node *p,p_node *q);
void swap(p_node *p,p_node *q)
{
    p_node *tmp = (p_node *)Malloc(sizeof(p_node));
    memcpy(tmp,p,(unsigned long)(&(((p_node *)0)->next)));
    memcpy(p,q,(unsigned long)(&((p_node *)0)->next));
    memcpy(q,tmp,(unsigned long)(&((p_node *)0)->next));
}
void sort_list_ascend1(list_head head)
{
    p_node *p = head->next;
    p_node *q = p->next;
    while(p->next){
        while(q){
            if(q->x < p->x){
                swap(q,p);
            }
            q = q->next;
        }
        p = p->next;
        q = p->next;
    }
}
//冒泡排序，外层循环p从head->next开始遍历到p->next == NULL，而q根据p，q开始等于p->next，然后
//之后q依次遍历到整个链表结束.如果q的值比p的小，那么交换两个节点
void sort_list_ascend(list_head head)
{
    p_node *p_pre = head;
    p_node *q_pre = head->next;
    p_node *p = p_pre->next;
    p_node *q = q_pre->next;
    p_node *tmp = (p_node *)Malloc(sizeof(p_node));
    while(p->next){
        while(q){
            if(q->x < p->x){
                if(p->next != q){
                    tmp = p->next;
                    p->next = q->next;
                    q->next = tmp;
                    p_pre->next = q;
                    q_pre->next = p;
                }
                else{
                    p->next = q->next;
                    q->next = p;
                    p_pre->next = q;
                    q_pre = q;
                }
            }
            q_pre = q_pre->next;
            q = q_pre->next;
            p = p_pre->next;
        }
        p_pre = p_pre->next;
        p = p_pre->next;
        q_pre = p;
        q = q_pre->next;
    }
}
//查找元素所在位置，通过二级指针接受*p存储的地址
boolean find_node(list_head head,int value,p_node **p)
{
    p_node *q;
    if(head == NULL)
        return FALSE;
    while(q != NULL){
        if(q->x == value){
            if(p != NULL){
                *p = q;
                return TRUE;
            }
        }
        q = q->next;
    }
}
boolean insert_node(list_head head,p_node *p,int value)
{
    p_node *tmp = (p_node *)Malloc(sizeof(p_node));
    if(head == NULL)
        return FALSE;
    tmp->x = value;
    tmp->next = p->next;
    p->next = tmp;
    return TRUE;
}
boolean pop_front(list_head head)
{
    p_node *p = head->next;
    if(head == NULL)
        return FALSE;
    head->next = head->next->next;
    free(p);
    p = NULL;
    return
        TRUE;
}
boolean pop_back(list_head head)
{
    p_node *p = head;
    p_node *tmp = NULL;
    if(head == NULL)
        return FALSE;
    while(p->next->next != NULL){
        p = p->next;
    }
    tmp = p->next;
    p->next = NULL;
    free(tmp);
    tmp = NULL;
    return TRUE;
}
void *Malloc(size_t size)
{
    void *result = malloc(size);
    if(result == NULL){
        fprintf(stderr,"未分配空间");
        exit(1);
    }
    return result;
}
//后面插入
boolean push_back(list_head head,int value)
{
    p_node *p = head->next;
    p_node *tmp = (p_node *)Malloc(sizeof(p_node));
    if(head == NULL)
        return FALSE;
    while(p->next != NULL){
        p = p->next;
    }
    tmp->x = value;
    p->next = tmp;
    tmp->next = NULL;
    return
        TRUE;
}
//插入到头指针的下一个节点
boolean push_front(list_head head,int value)
{
    if(head == NULL)
        return FALSE;
    p_node *p = NULL;
    p = (p_node *)Malloc(sizeof(p_node));
    p->x = value;
    p->next = head->next;
    head->next = p;
    return
        TRUE;
}
p_node *input(void)
{
    int n;
    p_node *p = NULL;
    p_node *head = (p_node *)malloc(sizeof(p_node));
    p_node *q = head;
    printf("input ele\n");
    scanf("%d",&n);
    while(n){
        p = (p_node *)malloc(sizeof(p_node));
        p->x = n;
        p->next = NULL;
        q->next = p;
        q = q->next;
        scanf("%d",&n);
    }
    return head;
}
void print(p_node *p)
{
    while(p != NULL){
        printf("%d\n",p->x);
        p=p->next;
    }
}
int main()
{
    char x;
    p_node *head = NULL;
    p_node *p = NULL;
    p_node *q = NULL;
    head = input();
    sort_list_ascend1(head);
    //push_front(head,5);
    //x = find_node(head,3,&p);
    //printf("%d\n",x);
    //q = binary(head);
    //printf("中间节点%d\n",q->x);
    //insert_node(head,p,10);
    //printf("%d\n",head->next);
    print(head->next);
    destroyed(&head);
    return 0;
}
