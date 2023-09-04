/************************************************ 
EXERCISE      : DS#10: Priority Queue
Implmented by : Snir Holland
Reviewed by   : Amitai Bar  
Date          : 17/5/2023
File          : priority_queue_test.c
*************************************************/


#include <stdio.h>
#include "priority_queue.h"
#include "sorted_list.h"


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
	
	pq = PQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == PQEnqueue(pq, &numbers[i]))
		{
			failed = 1;
			break;
		}			
	}
	
	printf("--------Testing Enqueue()--------\t");
	(0 == failed)? printf("Success\n") : printf("Failure\n");
	
	PQDestroy(pq);
}

static void TestDequeue()
{
	int data = 0;
	
	pq_t *pq = NULL;
	
	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = PQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == PQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}

	data = *(int*)PQDequeue(pq);	
		
	printf("--------Testing Dequeue()--------\t");
	
	(666 == data)? printf("Success\n") : printf("Failure\n");
	
	PQDestroy(pq);
}

static void TestIsEmpty()
{
	pq_t *pq = NULL;
	
	pq = PQCreate(&IntCmp);
	
	printf("--------Testing IsEmpty()--------\t");
	(PQIsEmpty(pq)) ? printf("Success\n") : printf("Failure\n");
	
	PQDestroy(pq);
}

static void TestPeek()
{
	int data = 0;
	
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = PQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == PQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}
	
	data = *(int*)PQPeek(pq);
		
	printf("--------Testing Peak()-----------\t");

	(666 == data)? printf("Success\n") : printf("Failure\n");
	
	PQDestroy(pq);
}

static void TestGetSize()
{
	size_t elem_count = 0;
	
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = PQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == PQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}
		
	elem_count = PQGetSize(pq);	
	printf("--------Testing GetSize()-----------\t");
	(7 == elem_count)? printf("Success\n") : printf("Failure\n");	
	
	PQDestroy(pq);
}

static void TestErase()
{
	int data = 12;
	
	int result = 0;
	
	size_t test_count = 2;
	
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = PQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == PQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}

	result = *(int*)PQErase(pq, &IntCmp, &data);
		
	printf("--------Testing Erase()-----------\t");
	(12 == result) ? --test_count : test_count;
	(7 == PQGetSize(pq)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
	
	PQDestroy(pq);
}

static void TestClear()
{
	pq_t *pq = NULL;

	int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };

	size_t i = 0;
	
	pq = PQCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		if (1 == PQEnqueue(pq, &numbers[i]))
		{
			printf("Error in Enqueue\n");
			break;
		}			
	}

	PQClear(pq);
	
	printf("--------Testing Clear()-----------\t");
	
	(PQIsEmpty(pq)) ? printf("Success\n") : printf("Failure\n");
	
	PQDestroy(pq);
}

/*----------End of Testing Functions--------------------*/


/*--------------- Compare Function--------------------*/
static int IntCmp(const void *data1, const void *data2)
{
	return (*(int*)data1 - *(int*)data2);
}


