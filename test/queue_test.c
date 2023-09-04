/************************************************ 
EXERCISE <1>    : DS#5: Queue
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 29/4/2023
File          : Queue_Test.c
*************************************************/

#include "queue.h" 
 
#include <stdio.h>

static void TestEnqueue();
static void TestDequeue();
static void TestIsEmpty();
static void TestGetSize();
static void TestPeek();
static void TestAppend(); 

/* Global list */
queue_t *queue1 = NULL;
queue_t *queue2 = NULL;

/* Globla arrays */
int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };
int numbers2[3] = {2000, 4000 , 6000};

int main(void)
{
	queue1 = QCreate();
	queue2 = QCreate();
	
	TestIsEmpty();

	TestEnqueue();
	
	TestGetSize();
	
	TestPeek();
	
	TestDequeue();
	
	TestAppend(); 

	QDestroy(queue1);
	QDestroy(queue2);

	return (0);
}

/* ------------TestEnqueue------------ */
static void TestEnqueue()
{
	int test_counter = 7;
	
	size_t i = 0;
	
	for(i=0; i<7; ++i)
	{
		if (0 == QEnqueue(queue1, &numbers[i]))
		{
			--test_counter;
		}		
	}
	
	printf("--------Testing Enqueue--------\t");
	(0 == test_counter) ? printf("Success\n") : printf("Failure\n");
}

/* ------------TestDequeue----------- */
static void TestDequeue()
{		
	QDequeue(queue1);
	QDequeue(queue1);
	QDequeue(queue1);
	
	printf("--------Testing Dequeue--------\t");
	
	(4 == QGetSize(queue1)) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestIsEmpty------------*/
static void TestIsEmpty()
{
	printf("--------Testing IsEmpty--------\t");

	(QIsEmpty(queue1)) ? printf("Success\n") : printf("Failure\n");	
}

/* ------------TestPeek------------ */
static void TestPeek()
{
	int data = 0;	
	printf("--------Testing Peek--------\t");
	
	data = *(int*)QPeek(queue1);
	
	(numbers[0] == data) ? printf("Success\n") : printf("Failure\n");	
}


/*------------TestGetSize------------*/
static void TestGetSize()
{
	printf("--------Testing GetSize------\t");
	
	(7 == QGetSize(queue1)) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestAppend------------*/
static void TestAppend()
{
	size_t i = 0;
	
	for(i=0; i<3; ++i)
	{
		QEnqueue(queue2, &numbers2[i]);		
	}
	
	QAppend(queue1 , queue2);
	
	printf("--------Testing Append------\t");
	
	if (7 == QGetSize(queue1) && 0 == QGetSize(queue2))
	{
		printf("Success\n"); 
	}
	else
	{
		printf("Failure\n");
	}
}


