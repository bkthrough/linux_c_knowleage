#include "mydlist.h"
#include <stdio.h>
#include <stdlib.h>

void print(void *value)
{
    printf("%d ",*(int *)value);
}
int main(int argc,char *argv[])
{
    Dlist dlist = init_dlist();
    int a[10] = {0};
    int i;
    for(i = 0;i < 10; ++i){
        a[i] = rand() % 100;
    }
    for(i = 0;i < 10; ++i){
        push_front(dlist,&a[i]);
    }
    //remove_dlist_node(dlist,dlist->head);
    show_dlist(dlist,print);
    destroy_dlist(&dlist);
    return 0;
}
