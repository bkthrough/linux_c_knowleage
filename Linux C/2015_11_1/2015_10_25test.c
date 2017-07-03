#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0

int main(int argc, char **argv)
{
    char a = 10;
    int b = 20;

    b = a + b;  //a(char) --> a(int)

    //1.数值范围小的转化成大的
    //2.整型：有符号转化为无符号；
    //3.整型和浮点类型--->double；

    int c = 10;  //t1
    unsigned char d = 20; //t2
 
    int *p[20];

    int (*q)[40]; // int[40]  *q; 
 
    //a*b + c*d + e*f
    //
    //a * b + c * d + e * f
    //


    int *m;
 

    return 0;
}

#endif

#if 0

#define FALSE (0)
#define TRUE  (1)

typedef unsigned char Boolean;

int main(int argc, char **argv)
{
    Boolean ok = FALSE;

    if(ok == FALSE){
    }

    return 0;
}

#endif

#if 1

int main(int argc, char **argv)
{
    int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90};
    char str1[] = "hello,world";


    printf("%d\n", array[2]);

    printf("%c\n", str1[2]);

    printf("%c\n", 2["hello,world"]);
 

    printf("%d\n", 2[array]);


   // []   ==   +
   //
   // a[b]  => b[a]
   //
   // a + b = b + a

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
   // && || 
   //
   // 短路运算:提前预知真或假
   int a = 10;
   int b = 20;
   if(a < 20 && b > 30){
   } 

   if(a > 5 || b < 30){
   
   }

   int c = (10, 20);
   
   //20;

  // , 30;

   printf("%d\n", c);   

  
  
    return 0;
}

#endif

#if 0

char *my_strcpy(char *des, const char *src);

char *my_strcpy(char *des, const char *src)
{
    return (char *)memcpy(des, src,     //把src内容拷贝到des,
                         strlen(src));  //拷贝strlen(src)长度
}


int main(int argc, char **argv)
{
    char *str1 = "hello,world";
    char str2[20] = {0};   

    my_strcpy(str2, str1);

    printf("str2：%s\n", str2);

    return 0;
}

#endif

#if 0

int max(int a, int b);
int max2(int a, int b, int c);
int max3(int a, int b, int c, int d, int e, int f);   //可变参函数

int max4(int count, ...);

//glic 
int max2(int a, int b, int c)
{
    //return (a > b) ? ((a > c) ? a : c) : ( (b > c) ? b : c ); 
    return max(max(a, b), c);
}

int max(int a, int b)
{
    return b > a ? b : a; 
}

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    int c = 30;
    int max_value = 0;

    max_value = max(a, b);
    max_value = max2(a, b, c);


    if(1 < a < 20){
        printf("1 < a < 20!\n");
    }

    if(1 < a && a < 20){
        printf("1 < a < 20!\n");
    }

   

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    int i = 0;

    for(i = 0; i < 10; ++i){

    }

    int *p = NULL;

    p = (int *)malloc(100);
   

//前置++
//_Self& operator++() {
//    this->_M_incr();
//    return *this;
//}
////后置++
//_Self operator++(int) {
//    _Self __tmp = *this;
//    this->_M_incr();
//    return __tmp;
//}

    // !  ++  --  - +  ~ & *  sizeof (类型)
    //
    // int a  = 10;
    // int *p = &a;
    //
    // a = 20;
    // *p = 20;
    //
    // ++  -- 
    //
    // int a = 10;
    // int b = 20;
    //
    // b = ++a + b;  // b = 11 + 20 = 31  , a = 11
    //
    // b = a++ + b;   // b = 10 + 20 = 30 , a = 11
    //
    //
    // int i = 0;
    //
    // for(i = 0; i < 10; i++){
    //
    // }
    //
    // for(i = 0; i < 10; ++i){
    //
    // }
    // 
    //

    return 0;
}

#endif


#if 0

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20; 
    int c = 30;
    int d = 40;

    int this_value_is_too_short = 20;


    //1.变量名称过长采用复合赋值语句
    this_value_is_too_short = this_value_is_too_short + 10;

    this_value_is_too_short += 10;
    
    //2.赋值语句的结合性
    a = b + c;

    a = b = c = d = 10;

    // a = (b = c = d = 10)
    //
    // a = (b = (c = d = 10))
    //  
    // a = (b = (c = (d = 10)))

    //3.左值和右值

    // a = b;
    //
    //  左值：空间(变量、内存中的值)
    //  右值：值；
    //  
    //  int *p = &a;
    //  int *q = &b;
    //
    //  *p = *q;
    //  
    //(++b)--;    //int b = 20; b=21
    //(a++)++;
    //
    //   if(NULL = p){
    //
    //   }


    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;

    // a &= b   //   0000 1010   a 
    //               0001 0100   b
    //               0000 0000

    // a |= b   //   0000 1010
    //               0001 0100
    //               0001 1110

    // a ^= b   //   0000 1010
    //               0001 0100
    //               0001 1110
    //
    // 布尔代数
    //
    //  <<   >>  & | ^ ~
    //
    //  给定一个signed int 类型的值，判断其中1的位数？
    //
    //  00001000 10010000 01001010 11001100
    //
    //  int a = 10;
    //
    //   00000000 00000000 00000000 00001010
    //
    //  //移位操作
    //  int get_one_count(int value);
    //  void print_bits(int value);
    //
    
    

    return 0;
}

#endif

#if 0

void swap1(int *a, int *b);
void swap2(int *a, int *b);
void swap3(int *a, int *b);
void swap4(int *a, int *b);

void swap(void *a, void *b, int length);

void swap(void *a, void *b, int length)
{
    void *temp = malloc(length);
   
    memcpy(temp, a, length);
    memcpy(a, b, length);
    memcpy(b, temp, length);

    free(temp);
}


#if 0
typedef double TYPE;

void swap6(TYPE *a, TYPE *b)
{
    TYPE temp = *a;
    *a = *b;
    *b = temp;
}
#endif

void swap4(int *a, int *b)
{
    *a =*b - *a;
    *b =*b - *a;
    *a =*a + *b;
}

void swap3(int *a, int *b)
{
    // 10 20   30
    if(a != b){
        *a = *a + *b;    
        *b = *a - *b;
        *a = *a - *b;
    }
}


void swap2(int *a, int *b)
{
    // 0001 1001
    // 0110 1000     
    // 0111 0001
    //
    // 10   0000 1010    *a
    //
    // 20   0001 0100    *b
    //
    //      0001 1110    *a  (*a ^ *b)
    //
    //      0000 1010    *b  (*b ^ *a)   10
    //
    //      0001 0100    *a              20
    // 1000 1000
    // 1000 1000
    // 0000 0000 
    //
    //
    if(a != b){
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}


void swap1(int *a, int *b)
{
    int temp = *a;
    *a = *b; 
    *b = temp;
}

int main(int argc, char **argv)
{
    int a = 2000000000;
    int b = 2100000000;
    double c = 10.5;
    double d = 20.5;


    printf("a = %d, b = %d\n", a, b);

    printf("c = %lf, d = %lf\n", c, d);
    swap(&a, &b, sizeof(int));
    swap(&c, &d, sizeof(double));

    printf("a = %d, b = %d\n", a, b);
    printf("c = %lf, d = %lf\n", c, d);

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{ 
    int a = 10;
    // 00000000 00000000 00000000 00000101
    a >>= 31;
   
    printf("%d\n", a);

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    int a = 4;
    int b = 7;

    a <<= 1;  // a * 2
    // 0000 0100 ---> 0000 1000 
    b >>= 1;
    // 0000 0111 ---> 0000 0011
    //  7 / 2 = 3

    // 80 / 9  = ? 
    //
    // 乘法和除法可以用移位得到。
    char c = -10;

    c >>= 2;

    printf("%d\n", c);
    // -1 = 0 - 1 = 1111 1111
    // 
    // char  0000 0000 

    // -10 = 0 - 10 = 1111 0101 = F5
    //
    //  1111 0101  ---> 1111 1101
    //                  0011 1101
    //
    //   signed 类型右移补充的位是符号位，如果为1，左边补充1.
    unsigned char d = 150;
    //   128 + 16 + 4 + 2
    //
    //   1001 0110
    //
    //   1100 1011
    //   
    //   0100 1011
    //
    //   unsigned 类型右移补充0
    d >>= 1;
    printf("%u\n", d);
 
    

    return 0;
}

#endif

#if 0

int main(int argc, char **argv)
{
    // + - * / % 

    // + - 的优先级低于乘除
    //
    // + - * / （针对于整型和浮点都适用）
    //
    // %  (取余运算只能针对整型，浮点不可以)

    char d = 20;
    int a = 100000;
    int b = -20; 
    float c = 40.5;

    a += b;   //a = a + b;
    c = c + a;   //
   
    d = a + d;
   
    //c %= 10;

    b %= -6;   //取余结果的正负由被取余对象决定
   
        



    //printf("%lf\n", c);
    //printf("%d", d);


    return 0;
}

#endif
