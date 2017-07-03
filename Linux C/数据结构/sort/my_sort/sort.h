#ifndef _SORT_H_
#define _SORT_H_

#include <stdio.h>
#include "tools.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

//冒泡排序
void bubble_sort(int *a,int length);
//选择排序
void select_sort(int *a,int length);
//插入排序
void insert_sort(int *a,int length);
//希尔排序
void shell_sort(int *a,int length);
//归并排序
void merge_sort(int *a,int length);
//计数排序
void count_sort(int *a,int length,int range);
//快速排序
void qsort_sort(int *a,int length);
//基数排序
void base_sort(int *a,int length);

#endif
