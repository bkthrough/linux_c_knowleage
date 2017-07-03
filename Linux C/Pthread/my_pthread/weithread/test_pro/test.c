/*ths is a demo*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread_pool.h>

void *test(void *str);

int main(int argc, char *argv[])
{
   int    thnum = 0;
   int     loop = 0;
   char str[10] = "hello";

   if (argc < TWO) {
       printf("argc is too few!\n");
       return NG;
   }

   thnum = atoi(argv[1]);
   if (pthread_pool_create(thnum) == NG) {
       printf("create failed!\n");
       return -1;
   }/*end if*/

   for (loop = 0; loop < thnum; ++loop) {
       pthread_pool_mission(test, (void *)str);
       sleep(1);
   }/*for end*/

   pthread_pool_end();

   pause();

   return 0;
}

void *test(void *str)
{
    char *p = NULL;

    p = (char *)str;
    printf("%s\n", str);
    return str;
}
