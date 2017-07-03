#include <stdio.h>
#include <stdlib.h>

const int d = 3;
struct node{
    int a[10];
    int value;
};

int main(int argc,char *argv[])
{
    //struct node *node = (struct node *)malloc(sizeof(struct node));
    struct node *node;
    struct node1;

    node = &node1;

    node->value = 10;
    int *b;
    int *d = NULL;
    
    *d = 10;
    int i = 5;
    node->value = &i;
    //node->a[0] = 1;
    //node->a[1] = 2;
    //b = node->a;
    //b++;
    
    printf("%d\n",b);
    return 0;
}
