#include "queue.h"
#include <stdio.h>
int main(int argc,char *argv[])
{
    Queue queue = init_queue();
    int a[10] = {1,2,3,4,5,6,7,8,9,0};
    int length = sizeof(a)/sizeof(a[0]);
    int i = 0;
    int *value = NULL;
    for(i = 0 ; i < length; ++i){
        in(queue,&a[i]);
    }
    printf("%d\n",is_queue_empty(queue));
    printf("%d\n",get_queue_count(queue));
    for(i = 0; i < length; ++i){
        get_queue_front(queue,(void **)&value);
        printf("%d ",*value);
        out(queue);
    }
    printf("\n");
    destroy_queue(&queue);
    return 0;
}
