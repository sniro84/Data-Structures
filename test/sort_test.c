/************************************************ 
EXERCISE      : Sorting Algorithms
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 30/5/2023
File          : sort_test.c
*************************************************/

#include "sort.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* rand() */
#include <time.h>   /* clock_t , clock()*/
#include <string.h> /* strcmp */

#define MAX_NAME_LEN (16)


static void TestBinarySearchIter();
static void TestBinarySearchRec();
static void TestBubbleSort();
static void TestInsertionSort();
static void TestSelectionSort();
static void TestCountingSort();
static void TestRadixSort();
static void TestMergeSort();
static void TestQuickSort();
static void DisplayQuickSortResults();

static int IntCmp(const void *value1, const void *value2);
static int StrCmp(const void *value1, const void *value2);


int main()
{
	TestBinarySearchIter();
	TestBinarySearchRec();
	TestBubbleSort();
	TestInsertionSort();
	TestSelectionSort();
	TestCountingSort();
	TestRadixSort();	
	TestMergeSort();
	TestQuickSort();
	DisplayQuickSortResults();
	
   	return (0);	
}

static void TestBubbleSort()
{
	size_t i =0;
	
	int arr[5000] = {0};
	size_t size = 5000;
	
	int is_sorted = 1;
	
	clock_t start = 0;
	clock_t end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = rand();
	}
	
	start = clock();
	BubbleSort(arr, size);
	end = clock();
	
	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	printf("------------ Testing BubbleSort --------------- \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
	
	printf("Clock ticks for BubbleSort : %ld\n" , end - start);
	printf("\n");
}

static void TestInsertionSort()
{
	size_t i =0;
	
	int arr[5000] = {0};
	size_t size = 5000;
	
	int is_sorted = 1;
	
	clock_t start = 0;
	clock_t end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = rand();
	}
	
	start = clock();
	InsertionSort(arr, size);	
	end = clock();
	
	
	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	printf("------------ Testing InsertionSort ------------ \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
	
	printf("Clock ticks for InsertionSort : %ld\n" , end - start);
	printf("\n");	
}

static void TestSelectionSort()
{
	size_t i =0;
	
	int arr[5000] = {0};
	size_t size = 5000;
	
	int is_sorted = 1;
	
	clock_t start = 0;
	clock_t end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = rand();
	}
	
	start = clock();
	SelectionSort(arr, size);
	end = clock();	
	
	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	printf("------------ Testing SelectionSort ------------ \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
	
	printf("Clock ticks for SelectionSort : %ld\n" , end - start);
	printf("\n");	
}

static void TestCountingSort()
{
	size_t i =0;
	
	int arr[5000] = {0};
	size_t size = 5000;
	
	int is_sorted = 1;
	
	clock_t start = 0;
	clock_t end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = rand() % 100 + 1;
	}
	
	start = clock();
	CountingSort(arr, size);
	end = clock();	
	
	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	printf("------------ Testing CountingSort ------------- \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
	
	printf("Clock ticks for CountingSort : %ld\n" , end - start);
	printf("\n");
}

static void TestRadixSort()
{
	size_t i =0;
	
	int arr[5000] = {0};
	size_t size = 5000;
	
	int is_sorted = 1;
	
	clock_t start = 0;
	clock_t end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = 100000 + rand() % 900000;
	}
	
	start = clock();
	RadixSort(arr, size);
	end = clock();	
	
	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	printf("------------ Testing RadixSort ---------------- \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
	
	printf("Clock ticks for RadixSort : %ld\n" , end - start);
	printf("\n");
}

static void TestQuickSort()
{
	size_t i =0;

	int is_sorted = 1;
	
	int numbers[10] = {9,1,7,2,6,11,78,4,13,12};
	char friends[6][MAX_NAME_LEN] = {"Ross", "Chandler", "Pheobe", "Monica", "Rachel", "Joey"};

	QuickSort(numbers, 10, sizeof(int), &IntCmp);

	for(i = 0 ; i<9 ; ++i) 
	{
		if(numbers[i] > numbers[i+1])
		{
			is_sorted = 0;
			break;
		}
	}

	if (is_sorted)
	{
		QuickSort(friends, 6, MAX_NAME_LEN * sizeof(char), &StrCmp);
		for(i = 0 ; i<5 ; ++i) 
		{
			if(strcmp(friends[i], friends[i+1]) > 0)
			{
				is_sorted = 0;
				break;
			}
		}
	}

	printf("------------ Testing QuickSort ---------------- \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
}

static void DisplayQuickSortResults()
{
	size_t i =0;
	size_t size = 5000;
	
	int arr[5000] = {0};

	int arr2[5000] = {0};
	
	int is_sorted = 1;
	int is_sorted2 = 1;
	
	clock_t start = 0;
	clock_t end = 0;

	clock_t qsort_start = 0;
	clock_t qsort_end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = rand();
	}

	for(i = 0 ; i<size ; ++i) 
	{
		arr2[i] = rand();
	}
	
	start = clock();
 	QuickSort(arr, size, sizeof(int) , &IntCmp); 
	end = clock();

	qsort_start = clock();
 	qsort(arr2, size, sizeof(int) , &IntCmp); 
	qsort_end = clock();	

	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	
	if(is_sorted)
	{
		printf("Clock ticks for QuickSort : %ld\n" , end - start);
	}
	else
	{
		printf("Error : Something went wrong with our quicksort\n");
	}

	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr2[i] > arr2[i+1])
		{
			is_sorted2 = 0;
			break;
		}
	}
	
	if(is_sorted2)
	{
		printf("Clock ticks for qsort : %ld\n" , qsort_end - qsort_start);
	}
	else
	{
		printf("Error : Something went wrong with the system quicksort\n");
	}
}

static void TestBinarySearchIter()
{
	int sorted_array[10] = {1,5,7,11,14,17,22,26,27,33};
	int keys_to_find[8] = {1,11,17,33,0,9,15,34};

	size_t test_count = 8;

	size_t i = 0;

	printf("------------ Testing BinarySearchIter --------- \t");

	for(i=0; i<4; ++i)
	{
		(1 == BinarySearchIter(sorted_array, 10, keys_to_find[i])) ? --test_count : test_count;
	}

	for(i=4; i<8; ++i)
	{
		(0 == BinarySearchIter(sorted_array, 10, keys_to_find[i])) ? --test_count : test_count;
	}

	(0 == test_count) ? printf("Success") : printf("Failure"); 	
	printf("\n");
}

static void TestBinarySearchRec()
{
	int sorted_array[10] = { 1,5,7,11,14,17,22,26,27,33 };
	int keys_to_find[8] = {1,11,17,33,0,9,15,34};

	size_t test_count = 8;

	size_t i = 0;

	printf("------------ Testing BinarySearchRec ---------- \t");

	for(i=0; i<4; ++i)
	{
		(1 == BinarySearchRec(sorted_array, 10, keys_to_find[i])) ? --test_count : test_count;
	}

	for(i=4; i<8; ++i)
	{
		(0 == BinarySearchRec(sorted_array, 10, keys_to_find[i])) ? --test_count : test_count;
	}

	(0 == test_count) ? printf("Success") : printf("Failure"); 	
	printf("\n");
}

static void TestMergeSort()
{
	size_t i =0;
	
	int arr[5000] = {0};
	size_t size = 5000;
	
	int is_sorted = 1;
	
	clock_t start = 0;
	clock_t end = 0;
	
	for(i = 0 ; i<size ; ++i) 
	{
		arr[i] = rand();
	}
	
	start = clock();
	MergeSort(arr, size);
	end = clock();
	
	for(i = 0 ; i<size-1 ; ++i) 
	{
		if(arr[i] > arr[i+1])
		{
			is_sorted = 0;
			break;
		}
	}
	printf("------------ Testing MergeSort ---------------- \t"); 	
	(is_sorted) ? printf("Success") : printf("Failure"); 	
	printf("\n");
	
	printf("Clock ticks for MergeSort : %ld\n" , end - start);
	printf("\n");
}


static int IntCmp(const void *value1, const void *value2)
{
	return *(int*)value1 - *(int*)value2;
}

static int StrCmp(const void *value1, const void *value2)
{
	char *str1 = (char*)value1;
	char *str2 = (char*)value2;

	return strcmp(str1, str2);
}
