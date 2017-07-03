#include <stdio.h>
#include <stdarg.h>

// /usr/include

#if 1

void print_array1(int *array, int length);
void print_array2(int *array, int length);
static void print_array(int *array, int length);

int find_value(int *array, int length, int value);

int find_value(int *array, int length, int value)
{
    int i = 0;

    if(array != NULL && length > 0){ 
        for(i = 0; i < length; ++i){ 
            if(array[i] == value){ 
                return i;
            }
        }
    }
    return -1;
}




static void print_array(int *array, int length)
{
    //如果长度 <= 0
    //     print(5)
    //    print(4)
    //   print(3)
    //  print(2)
    // print(1)
    //print(0)
    //   12  23  34 45 56 67
    int *arr = array + length - 1;

    if(length <= 0){
        return ;
    }else{
        print_array(array, length - 1);
        printf("%d  ", *arr);
    }



}




void print_array2(int *array, int length)
{
    if(array == NULL || length <= 0){
        return ;
    }

    print_array(array, length);
}


void print_array1(int *array, int length)
{
    int i = 0;

    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            printf("%d  ", array[i]);
        }
        printf("\n");
    }
}


int main(int argc, char **agrv)
{
    int array[] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 100};
    int length = sizeof(array) / sizeof(int);

    int index = 0;

    printf("show array:\n");
    print_array1(array, length);
    print_array2(array, length);

    index = find_value(array, length, 45);
    if(index >= 0){ 
        printf("\nthe index of value is:%d\n", index);
    }else{ 
        printf("\nnot found!\n");
    }

    return 0;
}

#endif

#if 0

int fact1(int num);

//尾部递归：

int fact2(int num, int value);
int fact3(int num);

int fact3(int num)
{
    int result = 1;

    while(num-- > 1){
        result *= num;
    }

    // 5! = 5 * 4 * 3 * 2 * 1
    return result;
}

int fact2(int num, int value)
{
    if(num < 0){
        return 0;
    }else if(num == 0){
        return 1;
    }else if(num == 1){
        return value;
    }else{
        return fact2(num - 1, num * value);
    }
}
//   fact2(5,1) =
//      fact2(4, 5) = 
//         fact2(3, 20) = 
//            fact2(2, 60) = 
//               fact2(1 , 120)


int fact1(int num)    //一般递归
{
    if(num < 0){ 
        return 0;
    }else if(num == 0 || num == 1){
        return 1;
    }else{
        return num * fact1(num - 1);
    }
}

   //fact1(5)
   //    5 * fact1(4)
   //            4 * fact1(3)
   //                   3 * fact(2)
   //                          2 * fact(1)
   //                          2 * 1 = 2
   //                    3 * 2 = 6
   //            4 * 6 = 24
   //    5 * 24 = 120
   //120
   //
   //
   //

int main(int argc, char **argv)
{
    // n! = n * (n - 1)!
    //
    // (n - 1)! = (n - 1) * (n - 2)！
    //
    // 5! = 5 * 4！= 5 * 4 * 3 * 2 * 1 = 120
    int result = 0;

    result = fact2(13, 1);

    printf("the result is:%d\n", result);

    return 0;
}

#endif

#if 0

int sum(int num, ...);

int sum(int num, ...)
{
    int result = 0;
    va_list args;
    int i = 0;

    va_start(args, num);
   
    for(i = 0; i < num; ++i){
        result += va_arg(args, int);
    }

    va_end(args);

    return result;
}

int main(int argc, char **argv)
{
    int result = 0;
  
    result = sum(8, 1, 2, 3, 100, 200, 300, 400, 500);

    printf("the sum is:%d\n", result);

    return 0;
}

#endif

#if 0
//函数的参数在传递中满足：
//
//1.参数的个数要相同；
//2.参数的类型要相同；
//3.参数的顺序要相同；

int max(int a, int b);
int max2(int a, int b, int c);

int max2(int a, int b, int c)
{
    return max(max(a, b), c);
}

int max(int a, int b)
{
    return b > a ? b : a;
}

#define  _AUPBND           (sizeof(acpi_native_int) - 1)
#define  _ADNBND           (sizeof(acpi_native_int) - 1)

#define _bnd(X, bnd)       ( ((sizeof(X)) + (bnd)) & (~(bnd)))

//   4 + 3 
//
//   0000 0111
//   1111 1100
//
//   0000 0100
//
//   4

//   11
//
//   0000 1011
//   1111 1100
//
//   0000 1000

#if 0
#define va_start(ap, A)    ((ap) = ((char *)&(A)) + (_bnd(A, _AUPBND)))
#define va_arg(ap, T)     (*(T *)(((ap) += (_bnd(T, _AUPBND))) - (_bnd(T, _ADNBND))))
#define va_end(ap)         (ap = (va_list)NULL)

void func1(int a, ...);

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    int c = 30;

    int result = 0;

    result = max(a, b);
    result = max2(a, b, c);    

    printf("---%d--%c-%%-%d--%s\n", 10, 'c', 20, "asfasda");

    return 0;
}

#endif

#endif
