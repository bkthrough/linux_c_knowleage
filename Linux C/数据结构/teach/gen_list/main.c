#include <stdio.h>
#include <stdlib.h>
#include "gen_list.h"

int main(int argc, char **argv)
{
    Gen_list list = NULL;
    Gen_list list2 = NULL;
    char str[] = "((20, 'd', (30, 'f')), ('g', 'i'), 60)";

    list = init_genlist(str);
  
    show_genlist(list);    //显示广义表信息
    printf("the count of list:%d\n", get_genlist_count(list));
    printf("the depth of list:%d\n", get_genlist_depth(list));

    list2 = copy_genlist(list);   //广义表的拷贝
 
    show_genlist(list2);    //显示广义表信息

    destroy_genlist(&list);   //广义表的销毁
    destroy_genlist(&list2); 
    return 0;
}


//(15, 'c', (20, 'd', (30, 'f')), ('g', 'i'), 60)
