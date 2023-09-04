/************************************************ 
EXERCISE      : Sorting Algorithms
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 30/5/2023
File          : sort.c
*************************************************/

#include "sort.h"

#include <stdlib.h>
#include <string.h> /* memcpy */
#include <stdio.h> /* stderr*/

/* static methods */
static int FindMax(int *array, size_t size);
static int CountingSortByDigit(int arr[], int n, int exp);
static int BinarySearch(int *sorted_arr, int key, int low, int high);
static int MergeSortRec(int *arr_to_sort, size_t low, size_t high);
static int Merge(int *arr_to_sort, size_t low, size_t mid, size_t high);
static void QuickSortRec(char* arr, size_t low, size_t high, size_t size, int (*comp)(const void*, const void*));
static size_t Partition(char* arr, size_t low, size_t high, size_t size, int (*comp)(const void*, const void*));  
static void GenericSwap(void *p1, void *p2, size_t nbytes);
static void Swap(int *arr , size_t ind1 , size_t ind2);

/* memory allocation status */
enum mem_alloc_status {FAILURE = 0, SUCCESS = 1};

/* binary search status */
typedef enum binary_search_status
{
	NOT_FOUND = 0,
	FOUND = 1
} bin_search_status_t;

/* ------------------- BubbleSort ------------------- */
void BubbleSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	assert(0 != size);
	
	for (i=0; i<size-1; ++i)
	{
		for (j=0; j<size-i-1; ++j)
		{
			if (arr[j] > arr[j+1])
			{
				Swap(arr ,j ,j + 1);
			}
		}
	}
}

/* ------------------- InsertionSort ------------------- */
void InsertionSort(int *arr, size_t size)
{
	size_t i = 0;
	int j = 0;
	
	int key = 0;
	
	assert(NULL != arr);
	assert(0 != size);
	
	for (i=1; i<size; ++i)
	{
		key = arr[i];
		j = i-1;
		
		while (j>=0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}

/* ------------------- SelectionSort ------------------- */
void SelectionSort(int *arr, size_t size)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != arr);
	assert(0 != size);
	
	for (i=0; i<size-1; ++i)
	{
		int min_index = i;
		for(j=i+1; j<size; ++j)
		{
			if (arr[j] < arr[min_index])
			{
				min_index = j;			
			}
		}
		Swap(arr, min_index , i);
	}
}

/* ------------------- CountingSort ------------------- */
int CountingSort(int *array, size_t size)
{
	int max = 0;
	int *helper_arr = NULL;
	int i = 0;

	int *temp_arr = NULL;
	
	assert(NULL != array);
	assert(0 != size);

	temp_arr = (int*)malloc(sizeof(int) * size);
	if (NULL == temp_arr)
	{
		return FAILURE;
	}
	memset(temp_arr , 0 , size);

	assert(NULL != array);
	assert(0 != size);

	max = FindMax(array, size);

	helper_arr = (int*)malloc(sizeof(int) * (max + 1));
	if (NULL == helper_arr)
	{
		free(temp_arr);
		temp_arr = NULL;
		return FAILURE;
	}

	/* Initialize */
	memset(helper_arr , 0 , max +1);	
	
	/* Adding quantities to helper array */
	for(i=0; i<(int)size; ++i)
	{
		++(helper_arr[array[i]]);
	}

	/* adding adjacent elements in helper array */
	for(i=1; i<max+1; ++i)
	{
		helper_arr[i] += helper_arr[i-1];
	}

	for(i=0; i<(int)size; ++i)
	{
		temp_arr[helper_arr[array[i]]-1] = array[i];
		--(helper_arr[array[i]]);
	}

	for(i=0; i<(int)size; ++i)
	{
		array[i] = temp_arr[i];
	}

	free(helper_arr);
	helper_arr = NULL;

	free(temp_arr);
	temp_arr = NULL;

	return SUCCESS;
}

/* ------------------- RadixSort ------------------- */
int RadixSort(int* array,size_t size)
{
	int max = 0;
	int exp =0;

	assert(NULL != array);
	assert(0 != size);

	max = FindMax(array, size);
 
    for (exp = 1; max / exp > 0; exp *= 10)
	{
		CountingSortByDigit(array, size, exp);
	}

	return SUCCESS;
}

/* ------------------- MergeSort ------------------- */
int MergeSort(int *arr_to_sort, size_t num_elements)
{
	assert(NULL != arr_to_sort);
	assert(num_elements > 0);

	return MergeSortRec(arr_to_sort, 0 ,num_elements - 1);
}

/* ------------------- BinarySearchIter ------------------- */
int BinarySearchIter(int *sorted_arr, size_t size, int key)
{
	int low = 0;
	int high = size - 1;
	
	int mid = 0;

	bin_search_status_t status = NOT_FOUND;

	while(low <= high)
	{
		mid = (low + high) / 2;

		if (key == sorted_arr[mid])
		{
			status = FOUND;
			break;
		}
		else if(key > sorted_arr[mid])
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return status;
}

/* ------------------- BinarySearchRec ------------------- */
int BinarySearchRec(int *sorted_arr, size_t size, int key)
{
	int lower_bound = 0;
	int higher_bound = size - 1;

	return BinarySearch(sorted_arr, key, lower_bound, higher_bound);
}

/* ------------------- QuickSort ------------------- */
void QuickSort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *))
{
	size_t low = 0;
	size_t high = size * (nmemb - 1);
	QuickSortRec( (char*)base, low, high, size, compare);
}

/* --------------- End of functions --------------- */
 
/* ---------------- Static functions ---------------- */

/* Helper function : driver for quicksort recursion */
static void QuickSortRec(char* arr, size_t low, size_t high, size_t size, int (*comp)(const void*, const void*))
{
	if (low < high)
	{
		size_t pivot = Partition(arr, low, high, size, comp);
		QuickSortRec(arr, low, pivot - size, size, comp);
		QuickSortRec(arr, pivot + size, high, size, comp);
	}
}

/* Helper function : returns position of pivot for quicksort */
static size_t Partition(char* arr, size_t low, size_t high, size_t size, int (*comp)(const void*, const void*))
{
	char *pivot = arr + high;
	
	size_t i = low;
	size_t j = low;

	for(j=low; j<high; j += size)
	{
		if (comp(arr + j, pivot) <= 0)
		{
			GenericSwap(arr + i, arr + j, size);
			i += size;
		}
	}

	GenericSwap(arr + i, arr + high, size);

	return i;
}

/* Helper function : swap two variables (any type) */
static void GenericSwap(void *p1, void *p2, size_t nbytes)
{
    void *buf = NULL;

    assert(NULL != p1);
    assert(NULL != p2);

    buf = malloc(nbytes);
    if (NULL == buf)
    {
        fprintf(stderr,"Memory allocation failed.\n");
        return;
    }

    memcpy(buf, p1, nbytes);
    memcpy(p1,  p2, nbytes);
    memcpy(p2, buf, nbytes);

    free(buf);
    buf = NULL;
}

/* Helper function : finds max of value in an array of ints */
static int FindMax(int *array, size_t size)
{
	size_t i = 0;
	int result = 0; 

	assert(NULL != array);
	assert(0 != size);

	for(i=0; i<size; ++i)
	{
		if (array[i] > result)
		{
			result = array[i];
		}
	}
	return result;
}

/* Helper function : swap two int variable */
static void Swap(int *arr , size_t ind1 , size_t ind2)
{
	assert(NULL != arr);

	GenericSwap(arr + ind1, arr + ind2, sizeof(int));	
}

/* Helper function : sort array by examined digit */
static int CountingSortByDigit(int arr[], int n, int exp)
{
    int i = 0;
    int *output = NULL;
	int count[10] = {0};

	output = (int*)malloc(sizeof(int) * n);
	if (NULL == output)
	{
		return FAILURE;
	}
	memset(output , 0 , n);

    for (i = 0; i < n; i++)
	{
        count[(arr[i] / exp) % 10]++;
	}
 
    for (i = 1; i < 10; i++)
	{
        count[i] += count[i - 1];
	}

    for (i = n - 1; i >= 0; i--) 
	{
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    for (i = 0; i < n; i++)
	{
        arr[i] = output[i];

	}

	free(output);

	return SUCCESS;
}

/* Helper function : driver for binary search recursion */
static int BinarySearch(int *sorted_arr, int key, int low, int high)
{
	int mid = (low + high) / 2;

	if (low > high)
	{
		return NOT_FOUND;
	}

	if (key == sorted_arr[mid])
	{
		return FOUND;
	}

	else if (key < sorted_arr[mid])
	{
		return BinarySearch(sorted_arr, key, low, mid - 1);
	}

	else
	{
		return BinarySearch(sorted_arr, key, mid + 1, high);
	}
}

/* Helper function : driver for MergeSort recursion */
static int MergeSortRec(int *arr_to_sort, size_t low, size_t high)
{
	size_t mid = (low + high) / 2;
	int status = FAILURE; 

	if (low == high)
	{
		return SUCCESS;
	}

	status = MergeSortRec(arr_to_sort, low, mid);
	if (FAILURE == status)
	{
		return FAILURE;
	}

	status = MergeSortRec(arr_to_sort, mid + 1, high);
	if (FAILURE == status)
	{
		return FAILURE;
	}

	status = Merge(arr_to_sort, low, mid, high);

	return status;
}

/* Helper function : combine two sorted array into one sorted array */
static int Merge(int *arr_to_sort, size_t low, size_t mid, size_t high)
{
	int *temp_left = NULL;
	int *temp_right = NULL;

	size_t s1 = mid - low + 1;
	size_t s2 = high - mid;

	size_t i = 0;
	size_t j = 0;

	/* index of merged array */
	size_t k = low;

	temp_left = (int*)malloc(s1 * sizeof(int));
	if (NULL == temp_left)
	{
		return FAILURE;
	}
	temp_right = (int*)malloc(s2 * sizeof(int));
	if (NULL == temp_right)
	{
		free(temp_left);
		return FAILURE;
	}

	/* copy values to temp arrays*/
	for(i=0; i<s1; ++i)
	{
		*(temp_left + i) = *(arr_to_sort + low + i);
	}
	for(j=0; j<s2; ++j)
	{
		*(temp_right + j) = *(arr_to_sort + j + mid + 1);
	}

	i = 0;
	j = 0;

	/* copy smaller elements first */
	while((i < s1) && (j < s2))
	{
		if (*(temp_left + i) < *(temp_right + j))
		{
			*(arr_to_sort + k) = *(temp_left + i);
			++i;
		}
		else
		{
			*(arr_to_sort + k) = *(temp_right + j);
			++j;
		}
		++k;
	}

	/* fill remaining elements */
	while (i < s1)
	{
		*(arr_to_sort + k) = *(temp_left + i);
		++i;
		++k;
	}
	while (j < s2)
	{
		*(arr_to_sort + k) = *(temp_right + j);
		++j;
		++k;
	}

	free(temp_left);
	temp_left = NULL;

	free(temp_right);
	temp_right = NULL;

	return SUCCESS;
}

