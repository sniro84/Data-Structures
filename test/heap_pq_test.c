/************************************************ 
EXERCISE      : DS#10: Priority Queue
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona  
Date          : 20/6/23
File          : heap_pq_test.c
*************************************************/

#include <stdio.h>
#include "heap_pq.h"

/*------Test Functions------------*/
static void TestIsEmpty();
static void TestEnqueue();
static void TestDequeue();
static void TestPeek();
static void TestGetSize();
static void TestClear();
static void TestErase();
/*-------------------------------*/

/*------Helper Functions------------*/
static int IntCmp(const void * , const void *);
static int IsEqualInt(const void *data1, const void *data2);


int main(void)
{	
	TestIsEmpty();
	
	TestEnqueue();
	
	TestDequeue();
	
	TestPeek();
	
	TestGetSize();
	
	TestErase();
	
	TestClear();

	return (0);
}

static void TestEnqueue()
{
	pq_t *pq = NULL;
	
	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	int failed = 0;
	
	pq = HeapPQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == HeapPQEnqueue(pq, &numbers[i]))
		{
			failed = 1;
			break;
		}			
	}
	
	printf("--------Testing Enqueue()--------\t");
	(0 == failed)? printf("Success\n") : printf("Failure\n");
	
	HeapPQDestroy(pq);
}

static void TestDequeue()
{
	int data = 0;
	
	pq_t *pq = NULL;
	
	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = HeapPQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == HeapPQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}

	data = *(int*)HeapPQDequeue(pq);	
		
	printf("--------Testing Dequeue()--------\t");
	
	(-8 == data)? printf("Success\n") : printf("Failure\n");
	
	HeapPQDestroy(pq);
}

static void TestIsEmpty()
{
	pq_t *pq = NULL;
	
	pq = HeapPQCreate(&IntCmp);
	
	printf("--------Testing IsEmpty()--------\t");
	(HeapPQIsEmpty(pq)) ? printf("Success\n") : printf("Failure\n");
	
	HeapPQDestroy(pq);
}

static void TestPeek()
{
	int data = 0;
	
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = HeapPQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == HeapPQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}
	
	data = *(int*)HeapPQPeek(pq);
		
	printf("--------Testing Peak()-----------\t");

	(-8 == data)? printf("Success\n") : printf("Failure\n");
	
	HeapPQDestroy(pq);
}

static void TestGetSize()
{
	size_t elem_count = 0;
	
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = HeapPQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == HeapPQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}
		
	elem_count = HeapPQGetSize(pq);	
	printf("--------Testing GetSize()-----------\t");
	(7 == elem_count)? printf("Success\n") : printf("Failure\n");	
	
	HeapPQDestroy(pq);
}

static void TestErase()
{
	int data = 12;
	
	int result = 0;
	
	size_t test_count = 2;
	
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = HeapPQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == HeapPQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}

	result = *(int*)HeapPQErase(pq, &IsEqualInt, &data);
		
	printf("--------Testing Erase()-----------\t");
	(12 == result) ? --test_count : test_count;
	(6 == HeapPQGetSize(pq)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
	
	HeapPQDestroy(pq);
}

static void TestClear()
{
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = HeapPQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == HeapPQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}

	HeapPQClear(pq);
	
	printf("--------Testing Clear()-----------\t");
	
	(HeapPQIsEmpty(pq)) ? printf("Success\n") : printf("Failure\n");
	
	HeapPQDestroy(pq);
}

/*----------End of Testing Functions--------------------*/


/*--------------- Compare Function--------------------*/
static int IntCmp(const void *data1, const void *data2)
{
	return (*(int*)data1 - *(int*)data2);
}

/*--------------- Match Function--------------------*/
static int IsEqualInt(const void *data1, const void *data2)
{
	return (*(int*)data1 == *(int*)data2);
}
