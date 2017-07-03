#include <stdio.h>
#include <time.h>
#include "tools.h"

// 1000 * 1000 * 1000 = 1000000000

#define SIZE     (20000)
#define MOD_SIZE (10000000)

//不稳定：当出现跳跃交换而不是相邻交换现象（选择排序 快速排序 shell排序）

//1.冒泡排序   时间复杂度O(n^2)   稳定
//2.插入排序   时间复杂度O(n^2)   稳定
//3.选择排序   时间复杂度O(n^2)   不稳定
//4.shell排序
//5.归并排序   时间复杂度O(n * logn)  稳定
//6.快速排序   
//7.堆排序
//8.计数排序   时间复杂度O(n)     
//9.基数排序

//      9000 10000 8000 9100    O(n*logn)
//


void bubble_sort(int *array, int length);    //冒泡排序
void init_array(int *array, int length);
void show_array(int *array, int length);
void insert_sort1(int *array, int length);    //插入排序1
void insert_sort2(int *array, int length);    //插入排序2
void insert_sort3(int *array, int length);    //插入排序3
void select_sort(int *array, int length);    //选择排序
void merge_sort(int *array, int length);    //归并排序（分治思想）
static void Merge_sort(int *array, int left, int right, int *temp);
static void merge_array(int *array, int left, 
                int mid, int right, int *temp);
void count_sort(int *array, int length, int min, int max);    //计数排序
void base_sort(int *array, int length);    //基数排序
void quick_sort(int *array, int length);    //快速排序   时间复杂度O(n*logn) 不稳定
void quick_sort2(int *array, int length);   //快速排序2  
void shell_sort(int *array, int length);    //shell排序（缩小增量排序）


void shell_sort(int *array, int length)
{
     int gap = 0;
     int i = 0; 
     int j = 0;
     int temp = 0;
   
     for(gap = length / 2; gap > 0; gap /= 2){
         //直接插入排序的增强版
         for(i = gap; i < length; ++i){
             for(j = i - gap; j >= 0 && array[j] > array[j + gap]; j -= gap){
                //array[j] = array[j] + array[j + 1];
                //array[j + 1] = array[j] - array[j + 1];
                //array[j] = array[j] - array[j + 1];
                 temp = array[j]; 
                 array[j] = array[j + gap]; 
                 array[j + gap] = temp;
                // //swap(&array[j], &array[j + 1], sizeof(array[0]));
             }
         }
     }

     // 23   3   44   2   11   33   21   43   54   67      10 / 2 = 5
     //
     // 23                     33
     //      3                      21  
     //          43                      44
     //               2                       54  
     //                   11                       67
     /////////////////////////////////////////////////////
     // 23   3   43   2   11   33   21   44   54   67      5 / 2 = 2
     //
     // 23       43       11        21        54
     //     
     //      3        2        33        44        67
     //
     // 11       21       23        43        54 
     //
     //      2        3        33        44        67  
     //////////////////////////////////////////////////////
     //
     // 11   2   21   3   23   33   43   44   54   67     2 / 2 = 1
     //
     // 2    3   11   21  23   33   43   44   54   67     1 / 2 = 0
     //
     //
}

static void Quick_sort2(int *array,
                        int left, int right); 

static int partition(int *array, int left, int right);

static int partition(int *array, int left, int right)
{
    // 1.比关键值小的区域（S）
    // 2.比关键值大的区域（B）
    // 3.没有比较的区域（N）
    // 4.关键字（K）
    int value = array[right];   //关键值
    
    int i = left - 1;   //左界数值初始并未计算到S
    int j = left;
    int temp = 0;

    //  value = 4
    //
    //    2   8   7   1   3   5   6   4
    //
    //        i       j
    //
    //    2   1   3   4   7   5   6   8
    //
    //            i                   j

    for(j = left; j <= right; ++j){
        if(array[j] <= value){
            i++;
            temp = array[i]; 
            array[i] = array[j];
            array[j] = temp;
        }
    }
    //temp = array[i + 1];
    //array[i + 1] = array[j];
    //array[j] = temp;
    return i;
}

static void Quick_sort2(int *array,   
                        int left, int right)
{
    int index = 0;

    if(left< right){
        index = partition(array, left, right);
        Quick_sort2(array, left, index - 1);
        Quick_sort2(array, index + 1, right);
    }
}


void quick_sort2(int *array, int length)   //快速排序2
{
    if(array != NULL && length > 1){
        Quick_sort2(array, 0, length - 1);
    }
}

void Quick_sort(int *array, int left, int right);

void Quick_sort(int *array, int left, int right)
{
    int i = left;
    int j = right;
    int value = array[i];
   
    if(left < right){   //元素个数大于1
        while(i < j){
             //从后向前找比关键值小的元素
             while( j > i && array[j] > value){ 
                 j--;
             }
            
             if(j > i){
                 array[i++] = array[j];
             }
   
             //从前向后找比关键值大的元素
             while( i < j && array[i] < value){
                 i++;
             }

             if(i < j){
                 array[j--] = array[i];
             }
        }
        //结束比较后把关键值放在指定的位置
        array[i] = value;
        //递归地对关键字左右两个序列快速排序
        Quick_sort(array, left, i - 1);
        Quick_sort(array, i + 1, right);
    }

    // 12 12 12 12 12 12 12
}

void quick_sort(int *array, int length)
{   
     if(array != NULL && length > 1){ 
         Quick_sort(array, 0, length - 1);
     }
     //  快排思路：
     //
     // 1，选取一个数值为关键值并且记录下来
     // 2. 给定两个下标i,j分别指向头和尾(0, length - 1)
     //
     //
     // 3.循环操作：
     //      从后向前找遇到比关键值小的放在i下标；
     //      从前向后找遇到比关键值大的放在j下标；
     //      当i和j相等，退出
     //   把关键值填充进去
     // 
     // 4.对关键值两边做递归处理
     //
     //

     // 12 2 57 65 18 5 1 10 3
     // i                    j
     //
     // 3  2 57 65 18 5 1 10 3
     //      i               j
     //
     // 3  2 57 65 18 5 1 10 57
     //       i            j
     //
     // 3  2 10 65 18 5 1 10 57
     //         i          j
     //
     // 3  2 10 65  18 5  1  65 57
     //          i        j
     //
     // 3  2 10 1   18 5  1  65 57
     //             i     j 
     // 3  2 10 1   18 5  18 65 57
     //              i    j  
     // 3  2 10 1    5 5  18 65 57
     //              i j
     //
     // 3  2  10  1  5  12 18 65 57
     //
     // value = 12
}   


static int find_max(int *array, int length);
static int get_bit_size(int value);
static int get_num_in_bit(int value, int bit);

static int find_max(int *array, int length)
{
    int max = 0;
    int i = 0;
   
    for(i = 1, max = array[0]; i < length; ++i){
        if(array[i] > max){
            max = array[i];
        }
    }
   
    return max;
}

static int get_bit_size(int value)
{
    int bit = 0;
   
    // 100

    while(value){ 
        bit++;
        value /= 10;
    }
    
    return bit;
}


static int get_num_in_bit(int value, int bit)
{
    int num = 1;
  
    while(bit-- > 1){
       num *= 10;
    }   

    return (value / num) % 10;

    //   123456
    //
    //      100 = 1 * 10 * 10
    //
    //  1234 % 10 = 4
        
}

void base_sort(int *array, int length)
{
    int *bucket[SIZE];   //指针的数组,
    int i = 0;
    int j = 0; 
    int k = 0;
    int max_value = 0;
    int max_bit = 0;
    int bit = 0;
    int bit_num = 0;
    int count = 0;    
    int index = 0;

    //1.对每一个桶申请空间
    for(i = 0; i < SIZE; ++i){
        //多申请一个int记录元素个数
        bucket[i] = (int *)Malloc(sizeof(int) * (length + 1));
        bucket[i][0] = 0; 
    }

    //找出最大数
    max_value = find_max(array, length);
    max_bit = get_bit_size(max_value);

  //10 (n + n) O(n)

    // 1.从个位到max_bit位依次进行hash和收集的操作
    for(bit = 1; bit <= max_bit; ++bit){
        for(i = 0; i < length; ++i){
            //找到待排数据的第bit位的值，存放在对应的桶里
            bit_num = get_num_in_bit(array[i], bit);
            bucket[bit_num][0]++;
            index = bucket[bit_num][0];   //新的元素存放的下标（刚好是元素个数）
            bucket[bit_num][index] = array[i];
        }    

        //当所有的元素存放到指定桶中，判断0号桶元素是否和总个数相等，如果
        //相等退出大循环
        // if(bucket[0][0] == length){
        //    break ;
        // }
        //

        //从0到9号桶，依次把元素放在待排序列中
        for( i = 0, j = 0; i < SIZE; ++i){
            //取出每个桶内数据
            count = bucket[i][0];
            for(k = 1; k <= count; ++k){ 
                array[j++] = bucket[i][k];
            }
            //把桶内元素个数清零，为下次hash做准备
            bucket[i][0] = 0; 
        }
    }
    
    //
    //    10000000
    //        1000
    //         200
    //           1

    // 99.99% * 365 * 24 =

    //   

    // 120 321 456 326 443 221 334 901 108 856 735 235
    //
    //
    // 0 
    // 1 120
    // 2
    // 3 321 326
    // 4 456 443
    // 5
    // 6
    // 7
    // 8
    // 9
    //
    // 按位数从低到高依次排序
    //
    // （1）按个位排序
    //
    // 0   120
    // 1   321 221 901
    // 2
    // 3   443
    // 4   334
    // 5   735 235
    // 6   456 326 856
    // 7
    // 8   108
    // 9
    //
    //120 321 221 901 443 334 735 235 456 326 856 108   
    //
    //
    //按十位排序
    //
    // 
    // 0  901 108
    // 1   
    // 2  120 321 221 326
    // 3  334 735 235
    // 4  443
    // 5  456 856
    // 6   
    // 7
    // 8   
    // 9
    //
    // 901 108 120 321 221 326 334 735 235 443 456 856
    //
    //对百位进行排序
    //
    // 
    // 0  
    // 1 108 120 
    // 2 221 235
    // 3 321 326 334
    // 4 443 456 
    // 5  
    // 6   
    // 7 735
    // 8 856
    // 9 901
    //
    // 108 120 221 235 321 326 334 443 456 735 856 901
}



void count_sort(int *array, int length, int min, int max)
{
   //1.数据比较集中；
   //2.数据范围小；
   //
   //3.对内存的消耗比较大，用空间换取时间
   
   //   18 19 18 19 19 29 21 20 25 27 29 
   int *count = NULL;
   int c_size = max - min + 1;
   int i = 0;
   int j = 0;

   //申请统计个数的数组,并且进行清0操作
   count = (int *)malloc(sizeof(int) * c_size);
   bzero(count, sizeof(int) * c_size);
   
   //计算每个数字对应的个数
   for(i = 0; i < length; ++i){
       count[array[i] - min]++;
   }


   //  for(i = 0, j = 0; i < c_size; ++i){
   //      while(count[i]--){
   //          array[j++] = i + min;
   //      }
   //  }
   

   //从min到max，把个数非0的数字依次进行尾部插入
   for(i = 0, j = 0; i < c_size;){
       if(count[i] != 0){
           array[j++] = i + min;
           count[i]--;
       }else{
           i++;
       }
   }
   free(count);
}


static void merge_array(int *array, int left, 
                int mid, int right, int *temp)
{
    int i = left;   //第一个数组的起始位置
    int j = mid + 1;    //第二个数组的起始位置
    int m = mid;    //第一个数组的终止位置
    int n = right;    //第二个数组的终止位置
    int k = 0;

    while(i <= m && j <= n){   //当两个数组都有元素时，对应位置进行比较
        if(array[i] < array[j]){
            temp[k++] = array[i++];
        }else{
            temp[k++] = array[j++];
        }
    } 

    while(i <= m){
        temp[k++] = array[i++];
    }

    while(j <= n){
        temp[k++] = array[j++];
    }

    //把temp的内容复制到array相对应的范围
    memcpy(array + left, temp, sizeof(int) * k);
}


//O(n * logn)  < O(n^2)
//
//   y = logn
//
//   y = n
//
//
//
//
//
static void Merge_sort(int *array, int left, int right, int *temp)
{
    int mid = 0;
    //1.先进行拆分，再进行合并
    if(right > left){    //元素个数不为1，可以继续拆分
     //  14 3  3  2  45  32  18  27     logn   log2 8 = 3
     //   0                       7
     // 
     //  3  14 2  3
     //
     //  2  3  3  14
     //
     //    9 + 13 = 11
     //    4 + 6 = 10
     //   mid = (right >> 1) +  (left >> 1);
        mid = left + ((right - left) >> 1);
        Merge_sort(array, left, mid, temp);    //归并左半部分
        Merge_sort(array, mid + 1, right, temp);   //归并右半部分
        //合并拆解的两部分(合并两个有序数组)
        merge_array(array, left, mid, right, temp);
    }
}


void merge_sort(int *array, int length)    //归并排序（分治思想）
{
     int *temp = NULL;

     if(array == NULL || length < 2){
         return ;
     }

     temp = (int *)Malloc(sizeof(int) * length);
     Merge_sort(array, 0, length - 1, temp);    
     free(temp);

     //  14 3  57  2  45  32  18  27     logn   log2 8 = 3
     //  拆分过程：
     //
     //  14 3  57  2         45  32  18  27
     //
     //
     //  14 3    57  2        45  32      18  27
     //
     //  14   3    57    2    45   32   18   27
     //
     //  无法拆分，开始合并
     //
     //  ------合并两个有序数组
     //
     //  3   14    2    57    32   45   18   27
     //
     //  2   3    14    57    18   27   32   45
     //
     //  2   3    14    18    27   32   45   57
     //
     //  O(n*logn)
}


void select_sort(int *array, int length)    //选择排序
{
     // 5 13 6 9 2
     //   i                
     //
     // min = i
     //
     // if(array[j]  < array[min]){
     //     min = j;
     // }
     //
     //  swap(array[min], array[i])
     //
     // min = i
     //
     // 5   13    6    9   2
     // i   j = i+1
     //
     // 0   0  13  13  2  9  
     //     i      
     //
     int min_index = 0;
     int i = 0;
     int j = 0;
     int temp = 0;

     for(i = 0; i < length - 1; ++i){
         min_index = i;   //设当前序列的第一个元素为最小值
         for(j = i + 1; j < length; ++j){ 
             if(array[j] < array[min_index]){
                 min_index = j;
             }
         }  
         if(min_index != i){       
            temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
         }
     }
}

 
void insert_sort3(int *array, int length)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    // j     i
    //

    for(i = 1; i < length; ++i){
        for(j = i - 1; j >= 0 && array[j] > array[j + 1]; --j){
           //array[j] = array[j] + array[j + 1];
           //array[j + 1] = array[j] - array[j + 1];
           //array[j] = array[j] - array[j + 1];
            temp = array[j]; 
            array[j] = array[j + 1]; 
            array[j + 1] = temp;
           // //swap(&array[j], &array[j + 1], sizeof(array[0]));
        }
    }
}

void insert_sort2(int *array, int length)
{

    // key = 2
    // 2 3 6
    // j   i
    //
    int i = 0;
    int j = 0;  
    int key = 0;

    for(i = 1; i < length; ++i){
         key = array[i];
         for(j = i - 1; j >= 0 && array[j] > key; --j){
             array[j + 1] =  array[j];
         }
         array[j + 1] = key;
    }
}


void show_array(int *array, int length)
{
    int i = 0;   
    
    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            printf("%d ", array[i]);
        }
        printf("\n");
    }
   
}

void init_array(int *array, int length)
{
    int i = 0;   //
    
    srand(time(NULL));
    if(array != NULL && length > 0){
        for(i = 0; i < length; ++i){
            array[i] = rand() % MOD_SIZE;
        }
    }
}

//冒泡排序
void bubble_sort(int *array, int length)
{
    // 12 3  5   1  40  35 64 17
    //
    // 3  12 5   1  40  35 64 17
    // 
    // 3  5  12  1  40  35 64 17
    //
    // 3  5  1  12  40  35 64 17
    // 
    // 3  5  1  12  35  40 64 17
    //
    // 3  5  1  12  35  40 17 64 
    int i = 0;
    int j = 0;

    // 统计出待排序数量：length - i

    for(i = 0; i < length - 1; ++i){    
        for(j = 1; j < length - i; ++j){
            if(array[j - 1] > array[j]){
                swap(&array[j - 1], &array[j], sizeof(int)); 
            }
        } 
    } 
}

void insert_sort1(int *array, int length)
{
    int i = 0;
    int j = 0;

    // 12  3   5   1  40
    // i   j
    //
    // 3   12  5   1  40
    // i           j
    //
    // 1   12  5   3  40
    // i               j
    //
    // 1   12  5   3  2
    //     i   j
    //
    //
    for(i = 0; i < length - 1; ++i){
        for(j = i + 1; j < length; ++j){ 
            if(array[i] > array[j]){ 
                //swap(&array[i], &array[j], sizeof(int));
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main(int argc, char **argv)
{
    clock_t start = 0; 
    clock_t end = 0;
    double use_time = 0.0;    
    int *array2 = NULL;

    int *array = (int *)Malloc(sizeof(int) * SIZE);
    array2 = (int *)Malloc(sizeof(int) * SIZE); 
   
    init_array(array, SIZE);   //待排序数组的初始化   
    memcpy(array2, array, sizeof(int) * SIZE);   


    //printf("address:%p\n", array);


#ifdef SHOW_ARRAY
    //排序过程
    start = clock();
    show_array(array, SIZE);    //显示数组元素
    //bubble_sort(array, SIZE);   //排序
    //insert_sort2(array, SIZE);    
    //count_sort(array, SIZE, 0, MOD_SIZE - 1);
    //merge_sort(array, SIZE);
    //shell_sort(array, SIZE);
    show_array(array, SIZE);    //显示数组元素
    //结束排序
    end = clock();
    use_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("sort use time:%lf\n", use_time);

    start = clock();
    show_array(array2, SIZE);    //显示数组元素
    //bubble_sort(array, SIZE);   //排序
    //insert_sort3(array2, SIZE);    
    //select_sort(array2, SIZE);
    quick_sort(array2, SIZE);
    //base_sort(array2, SIZE);
    show_array(array2, SIZE);    //显示数组元素
    //结束排序
    end = clock();
    use_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("sort use time:%lf\n", use_time);
#else 
    //排序过程
    start = clock();
    //show_array(array, SIZE);    //显示数组元素
    //bubble_sort(array, SIZE);   //排序
    //quick_sort(array, SIZE);
    //shell_sort(array, SIZE);
    //insert_sort2(array, SIZE);    
    //count_sort(array, SIZE, 0, MOD_SIZE - 1);
    merge_sort(array, SIZE);
    //show_array(array, SIZE);    //显示数组元素
    //结束排序
    end = clock();
    use_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("sort use time:%lf\n", use_time);

    start = clock();
    //show_array(array2, SIZE);    //显示数组元素
    base_sort(array,SIZE);
    //bubble_sort(array, SIZE);   //排序
    //insert_sort3(array2, SIZE);    
    //select_sort(array2, SIZE);
    //quick_sort(array2, SIZE);
    //show_array(array2, SIZE);    //显示数组元素
    //结束排序
    end = clock();
    use_time = (double)(end - start) / CLOCKS_PER_SEC;  
    printf("sort use time:%lf\n", use_time);
#endif


    free(array);
    free(array2);
    return 0;
}
