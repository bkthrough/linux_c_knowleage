//  1.头、尾节点位置
//  2.链表
//  元素数量
#include <stdio.h>
#include <stdlib.h>
#include <strings.h> 
#include <string.h>

//链表节点信息：
//
//   1.数据域
//   2.指针域

#define TRUE     (1)
#define FALSE    (0)
#define ZERO     (0)
#define ONLY_ONE (1)
#define TWO      (2)
#define get_data_size()    ((unsigned long)&(((List_node *)0)->next))

struct List_node;    //声明一个类型

//链表控制信息
typedef struct List
{
    struct List_node *head;    //指向链表头部
    struct List_node *tail;    //指向链表尾部
    int              count;    //链表节点数量
}List;

//链表节点信息
typedef struct List_node
{
    int               data;    //数据域
    struct List_node *next;    //指针域
}List_node;

typedef unsigned char Boolean;

//  lua
//  C语言接口与实现   lcc

//链表的接口
List      *init_list(void)                        ;    //链表的初始化
void      destroy_list(List **list)               ;    //链表的销毁
Boolean   push_front(List *list, int value)       ;    //头部插入
Boolean   push_back(List  *list, int value)       ;    //尾部插入
Boolean   pop_front(List *list)                   ;    //头部删除
Boolean   pop_back(List *list)                    ;    //尾部删除
void      show_list(List *list)                   ;    //显示链表信息
void      sort_list_ascend(List *list)            ;    //升序排列
void      sort_list_descent(List *list)           ;    //降序排列
int       get_list_count(List *list)              ;    //得到链表节点数量

///
List      *merge_two_lists(List *list1, List *list2)       ;    //合并两个有序链表
List      *merge_two_lists_recure(List *list1, List *list2);    //合并两个有序链表（递归）
List_node *find_revise_node(List *list, int num)           ;   //找到链表的倒数第num个节点
List_node *find_mid_node(List *list)                       ;    //找到链表的中间节点
List      *reverse_list(List *list)                        ;    //逆置一个链表
List      *list_dump(List *list)                           ;    //链表的拷贝
void      reverse_show_list(List *list)                    ;    //逆序输出链表信息
Boolean   is_list_intersect(List *list1, List *list2)      ;    //判断链表是否有交点
List_node *get_first_common_node(List *list1, List *list2) ;    //得到第一个交点
void      delete_one_node(List *list, List_node *node)     ;    //在O（1）的时间复杂度删除节点

Boolean has_circle(List *list)                             ;   //判断一个链表是否有环
List_node *find_circle_first_node(List *list)              ;    //找到带环链表的环入口节点


static void *Malloc(size_t size);
static List_node *create_node(void); 
static void swap(void *a, void *b, int length);
static void rev_show_list(List_node *node);

static void swap(void *a, void *b, int length)
{
    void *temp = Malloc(length);
    memcpy(temp, a, length);
    memcpy(a, b, length);
    memcpy(b, temp, length);
    
    free(temp);
}

static List_node *create_node(void)    //创建链表节点
{
    List_node *node = (List_node *)Malloc(sizeof(List_node));
    bzero(node, sizeof(List_node));

    return node;
}

static void *Malloc(size_t size)
{
    void *result = malloc(size);
    if(result == NULL){
        fprintf(stderr, "the memory is full\n");
        exit(1);
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////
//
// 链表接口实现
// 
//    链表控制信息
//    typedef struct List
//    {
//        struct List_node *head;    //指向链表头部
//        struct List_node *tail;    //指向链表尾部
//        int              count;    //链表节点数量
//    }List;
//    
//    //链表节点信息
//    typedef struct List_node
//    {
//        int               data;    //数据域
//        struct List_node *next;    //指针域
//    }List_node;
//
////////////////////////////////////////////////////////////////////////////////////////




List      *init_list(void)                            //链表的初始化
{
    List *list = (List *)Malloc(sizeof(List));

    //      | head | tail | count |
    //          \      /      0
    //           \    /
    //            NULL
    bzero(list, sizeof(List));

    return list; 
}

void      destroy_list(List **list)                   //链表的销毁
{

    //              list
    //             /
    //         list_head  
    //          /
    //      | head | tail | count |
    //          \      \       n + 1
    //             
    //            \           \
    //            node->node2->node3
    if(list == NULL || *list == NULL){
        return ;
    }
   
    //  链表删除步骤：
    //  1.删除链表节点信息;
    while((*list)->count){   //头部删除链表节点
        pop_front(*list);
    }
    //  2.删除链表控制信息.
    free(*list);
    *list = NULL;
}

Boolean   push_front(List *list, int value)           //头部插入
{
    List_node *node = NULL;
  
    if(list == NULL){ 
        return FALSE;
    }   

    //创建节点并赋值
    node = create_node();
    node->data = value;

    //   case1:
    //      | head | tail | count |
    //          \      /      1
    //           \    /
    //            node
    if(list->count == ZERO){
        list->tail = node;
    }else{
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n + 1
    //           \               /
    //            node->node2->node3
        node->next = list->head;
    }
    list->head = node;
    list->count++;
    return TRUE;
}

Boolean   push_back(List  *list, int value)           //尾部插入
{
    List_node *node = NULL;

    if(list == NULL){
        return FALSE;
    }
  
    node = create_node();
    node->data = value;

    //   case1:
    //      | head | tail | count |
    //          \      /      1
    //           \    /
    //            node
    if(list->count == ZERO){
       list->head = list->tail = node;
    }else{
        //   case2:
        //      | head |              tail | count |
        //          \                 /       n + 1
        //           \               /
        //            node1->node2->node
        list->tail->next = node;
        list->tail = node;
    }
    list->count++;
    return TRUE;
}


Boolean   pop_front(List *list)                       //头部删除
{
    List_node *p_node = NULL;

    if(list == NULL || list->count == ZERO){
        return FALSE;
    }

    //   case1:
    //      | head | tail | count |
    //          \      /      1->0
    //           \    /
    //            node
    
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    p_node = list->head;
    if(list->count == ONLY_ONE){
        list->head = list->tail = NULL; 
    }else{
        list->head = list->head->next;
    }
    free(p_node);
    list->count--;
    return TRUE;
}

Boolean   pop_back(List *list)                        //尾部删除
{
    List_node *p_node = NULL;

    if(list == NULL || list->count == ZERO){ 
        return FALSE;
    }
   
    //   case1:
    //      | head | tail | count |
    //          \      /      1->0
    //           \    /
    //            node
    
    //   case2:
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    p_node = list->head; 
    if(list->count == ONLY_ONE){    
        list->head = list->tail = NULL;
        free(p_node);
    }else{
        //判断倒数第二个？
        //   p_node->next == list->tail
        while(p_node->next != list->tail){
            p_node = p_node->next;
        }
        free(list->tail);
        list->tail = p_node;
        p_node->next = NULL;
    }
    list->count--;
    return TRUE;
}

void      show_list(List *list)                       //显示链表信息
{
    List_node *p_node = NULL;

    if(list != NULL && list->count != ZERO){ 
        for(p_node = list->head; p_node; p_node = p_node->next){ 
            printf("%d ", p_node->data);
        }
        printf("\n");
    }
}

#if 1
void      sort_list_ascend(List *list)                //升序排列
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    unsigned long data_size = 0;

    if(list == NULL || list->count < TWO){
        return ;
    }
 // List_node *p = list->head;

 // p->next = NULL;

 // ((unsigned long)&(((List_node *)0)->next))

 // sizeof(List_node) - sizeof(List_node *);
 
   
    // int               data;  // 0   1   2   3
    //                          // 4   5   6   7
    // struct List_Node *next;  // 8   9  10  11
    //                            12  13  14  15
    //

    data_size = get_data_size();    //求得数据区域得大小
    for(p_node = list->head; p_node->next; p_node = p_node->next){
        for(q_node = p_node->next; q_node ; q_node = q_node->next){
            if(p_node->data > q_node->data){ 
                swap(p_node, q_node, data_size);                
            }
        }
    }
}

void      sort_list_descent(List *list)               //降序排列
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    unsigned long data_size = 0;

    if(list == NULL || list->count < TWO){
        return ;
    }
 // List_node *p = list->head;

 // p->next = NULL;

 // ((unsigned long)&(((List_node *)0)->next))

 // sizeof(List_node) - sizeof(List_node *);
 
   
    // int               data;  // 0   1   2   3
    //                          // 4   5   6   7
    // struct List_Node *next;  // 8   9  10  11
    //                            12  13  14  15
    //

    data_size = get_data_size();    //求得数据区域得大小
    for(p_node = list->head; p_node->next; p_node = p_node->next){
        for(q_node = p_node->next; q_node ; q_node = q_node->next){
            if(p_node->data < q_node->data){ 
                swap(p_node, q_node, data_size);                
            }
        }
    }
}

int       get_list_count(List *list)                  //得到链表节点数量
{
    if(list == NULL){ 
        return -1;
    }
    return list->count;
}

//   char *str1 = (char *)malloc(20);
//   strcpy(str1, "hello,world");
//
//   char *str2 = str1;
//   free(str1);
//
//   *str2  = 'c';

///
List      *merge_two_lists(List *list1, List *list2)    //合并两个有序链表
{
    List *result = NULL;
    List_node *list1_move = NULL;   
    List_node *list2_move = NULL;   
#if 0
    if(list1 == NULL){
        return result = copy_list_by_ctl(list2);
    }else if(list2 == NULL){
        return result = copy_list_by_ctl(list1);
    }
#endif
    if(list1 == NULL || list2 == NULL){
        return result;
    }

    result = init_list();   //结果链表得初始化

    list1_move = list1->head;
    list2_move = list2->head;

    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    //
    //
    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    //


    //如果两个链表都没有遍历完，进行比较
    while(list1_move != NULL && list2_move != NULL){
        if(list1_move->data <= list2_move->data){
            push_back(result, list1_move->data);
            list1_move = list1_move->next;
        }else{
            push_back(result, list2_move->data);
            list2_move = list2_move->next;
        }
    }

    //当两个链表中任何一个遍历结束，则把另外一个进行尾部添加
    while(list2_move != NULL){
        push_back(result, list2_move->data);
        list2_move = list2_move->next;
    }

    while(list1_move != NULL){
        push_back(result, list1_move->data);
        list1_move = list1_move->next;
    }

    return result;
}

List      *merge_two_lists_recure(List *list1, List *list2);    //合并两个有序链表（递归）


List_node *find_revise_node(List *list, int num)   //找到链表的倒数第num个节点
{
    List_node *move = NULL;
    int move_count = 0;
    //     10   23   5   15    50    67   45   32  
    if(list == NULL || num <= 0 || num > list->count){
        return NULL;
    }    

    move = list->head;
    //移动的步长
    move_count = list->count - num;

    while(move_count--){
        move = move->next;
    }

    return move;
}

//全局
//
//事件（select\poll\epoll）
//
//http{
//    server{
//
//        location / {
//          
//        }
//    }
//
//    server{
//        location / {
//
//        }
//    }
//}
//


List_node *find_mid_node(List *list)    //找到链表的中间节点
{
    // 1. 快慢指针：
    //
    // f  每次移动2步， s 每次移动1步
    //     10   23  5  15  50  67  45  32  82
    //
    // 2. 8 / 2 = 4
    List_node *move = NULL;
    int move_count = 0;

    if(list == NULL){
        return NULL;
    }

    move = list->head;
    move_count = list->count >> 1;

    //   0000 1010   10
    //       10 >> 1
    //   0000 0101   5
    while(move_count--){
        move = move->next;
    }

    return move;
}
//这个是我自己写的，比驰哥写的简单
List      *reverse_list(List *list)    //逆置一个链表
{
    List_node *p = NULL;
    List_node *q = NULL;
    List_node *m = NULL;

    if(list == NULL || list->count == ONLY_ONE){
        return list;
    }

    p = list->head;
    q = p->next;
    m = q->next;
    p->next = NULL;

    while(q){
        q->next = p;
        p = q;
        q = m;
        //如果m存在那么就让m指向下一个否则退出
        if(m){
            m = m->next;
        }
        else{
            break;
        }
    }
    //要注意，交换值必须传递值所在的地址
    swap(&(list->head),&(list->tail),sizeof(List_node *));

    return list;
}
#if 0
List      *reverse_list(List *list)    //逆置一个链表
    //要注意，交换值必须传递值所在的地址
{
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    List_node *m_node = NULL;


    //      | head |              tail | count |
    //          \                 /       n-> n - 1
    //           \               /
    //            node1->node2->node3
    if(list == NULL || list->count < TWO){
        return list;
    } 
    //两个节点
    if(list->count == TWO){
        list->tail->next = list->head;
        list->head->next = NULL;
    }else{    //三个节点
        p_node = list->head;
        q_node = p_node->next;
        m_node = q_node->next;
        p_node->next = NULL;
        do{
            q_node->next = p_node;   //让中间指针的next指向前一个
            p_node = q_node;    //指针整体向后搬移
            q_node = m_node;
            m_node = m_node->next;
        }while(m_node != NULL);
        q_node->next = p_node;
    }
    //交换头尾指针
    swap(&(list->head), &(list->tail), sizeof(List_node *));
    return list;
}
#endif

List      *list_dump(List *list)    //链表的拷贝
{

}

static void rev_show_list(List_node *node)
{
   //要打印当前节点，先打印其后续节点
   if(node != NULL){
       rev_show_list(node->next);
       printf("%d ", node->data);    
   }
}

void      reverse_show_list(List *list)    //逆序输出链表信息
{
    if(list == NULL || list->count == ZERO){
        return ;
    }  
    rev_show_list(list->head);
    printf("\n");
}

Boolean   is_list_intersect(List *list1, List *list2)    //判断链表是否有交点
{
    if(list1 == NULL || list2 == NULL){
        return FALSE;
    }   
    return list1->tail == list2->tail;
}

List_node *get_first_common_node(List *list1, List *list2)    //得到第一个交点
{
    int list1_len = 0;
    int list2_len = 0;
    int distance = 0;
    List_node *p_node = NULL;
    List_node *q_node = NULL;
    

    if(!is_list_intersect(list1, list2)){    //判断两个链表是否有交点
        return NULL;
    }
   
    list1_len = list1->count;
    list2_len = list2->count;

    p_node = list1->head;
    q_node = list2->head;

    //判断较长链表并首先进行移动
    if(list1_len >= list2_len){
        distance = list1_len - list2_len;
        while(distance--){ 
            p_node = p_node->next;
        }
    }else{
        distance = list2_len - list1_len;
        while(distance--){
            q_node = q_node->next;
        }
    }

    //依次对对应节点进行判断是否相等，如果相等则是第一个相交节点
    while(p_node != q_node){
        p_node = p_node->next;
        q_node = q_node->next;
    }
   
    return p_node;
}

void      delete_one_node(List *list, List_node *node)    //在O（1）的时间复杂度删除节点
{
    List_node *p_node = NULL;

    if(list == NULL || node == NULL){
        return ;
    }
 
    if(node != list->tail){    //不是最后一个节点
        p_node = node->next;
        node->data = p_node->data;
        node->next = p_node->next;
        free(p_node);
        list->count--;       
    }else{    //最后一个节点
        pop_back(list);
    }
}

Boolean has_circle(List *list)                             ;   //判断一个链表是否有环
List_node *find_circle_first_node(List *list)              ;    //找到带环链表的环入口节点

#endif
int main(int argc, char **argv)
{
    List *list1 = NULL;
    List *list2 = NULL;
    List *merge_list = NULL;
    List_node *middle = NULL;    //中间节点
    List_node *revise = NULL;    //倒数第n个节点

    int i = 0;

    list1 = init_list();   //链表初始化
    list2 = init_list();   //链表初始化

    for(i = 0; i < 10; ++i){
        push_back(list1, rand() % 200);
    }

    for(i = 0; i < 10; ++i){
        push_back(list2, rand() % 200);
    }

    show_list(list1);    //显示链表信息
    show_list(list2);   
    sort_list_ascend(list1);
    sort_list_ascend(list2);    

    merge_list = merge_two_lists(list1, list2);   //合并两个有序链表
    printf("list1 :");
    show_list(list1);    //显示链表信息
    printf("list2 :");
    show_list(list2);
    printf("merge list:\n");
    show_list(merge_list);

    middle = find_mid_node(merge_list);
    if(middle != NULL){
        printf("the mid of merge_list is:%d\n", middle->data);
    }

    revise = find_revise_node(merge_list, 5);
    if(middle != NULL){
        printf("the revise  of merge_list is:%d\n", revise->data);
    }

    reverse_list(merge_list);   //反转链表

    printf("reverse list :\n");
    show_list(merge_list);
     
    printf("merge_list revese show:\n");
    reverse_show_list(merge_list); 

    destroy_list(&list1);    //链表的销毁
    destroy_list(&list2);    //链表的销毁
    destroy_list(&merge_list);   
    return 0;
}
