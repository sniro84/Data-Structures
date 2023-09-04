/************************************************ 
EXERCISE      : Sorting Algorithms
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 30/5/2023
File          : sort.h
*************************************************/

#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

int BinarySearchIter(int *sorted_arr, size_t size, int key);

int BinarySearchRec(int *sorted_arr, size_t size, int key);

int MergeSort(int *arr_to_sort, size_t num_elements);

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

void QuickSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

int CountingSort(int* array,size_t size);

int RadixSort(int* array,size_t size);


#endif /* __SORT_H__ */
