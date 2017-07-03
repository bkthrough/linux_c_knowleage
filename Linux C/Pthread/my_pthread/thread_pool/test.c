#include <apue.h>

void _sig_int(int sig)
{

}
void test()
{
    while(1){
        pause();
        printf("running!!\n");
        printf("-------------------\n");
    }
}
struct Test
{
    int a;
};
int main()
{
    int a[10] = {1,2,3,4,5,6,7,8,9};
    void *b = malloc(100);

    memcpy(b,(void *)a,sizeof(a)/sizeof(a[0]));
    bzero(b,sizeof(struct Test));
    printf("asd\n");
    return 0;
}
