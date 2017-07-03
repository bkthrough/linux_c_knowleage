#include "dlist.h"
#include <stdio.h>

void print_int(void *value);

void print_int(void *value)
{
    printf("%d ", *(int *)value);
}

int main(int argc, char **argv)
{
    Dlist *dlist = NULL;

    dlist = init_dlist();    //双端链表的初始化
    int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 100};
    int length = sizeof(array) / sizeof(array[0]);
    int i = 0;
    int value = 3;
    for(i = 0; i < length; ++i){
        push_back(dlist, &array[i]);
    }
    insert_prev(dlist,dlist->head->next,&value);
    show_dlist(dlist, print_int);   //显示链表信息
 

    destroy_dlist(&dlist);    //双端链表的销毁 
    return 0;
}
