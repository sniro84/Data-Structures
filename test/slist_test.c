/************************************************ 
EXERCISE <1>    : DS#4: LinkedList
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona 
Date          : 29/4/2023
File          : LinkedList_Test.c
*************************************************/

#include "slist.h" 
#include <stdio.h>

/* Test functions */
static void TestSetData();
static void TestGetData();
static void TestGetBegin();
static void TestGetEnd();
static void TestInsert();
static void TestRemove();
static void TestListCount();
static void TestIsEqual();
static void TestFind();
static void TestForEach();
static void TestListAppend();

/* This match function returns the difference between num1 and num2 */ 
static int IntCmp(void *num1 , void *num2);

/* This action function adds the value of x to each integer, until devil is reached (666) */
static int AddIntUntilDevil(void *data , void* x);

/* Global lists */
slist_t *list = NULL;
slist_t *list2 = NULL;

/* Globla arrays */
int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };
int numbers2[4] = {500 , 600 , 700};
int set_arr[2] = {8338 , 4994};

int main(void)
{
	list = SListCreate();
	list2 = SListCreate();

	TestInsert();
	
	TestListCount();
	
	TestSetData();	
	
	TestGetData();
		
	TestForEach();	
		
	TestGetBegin();
	
	TestGetEnd();
	
	TestRemove();
	
	TestIsEqual();
	
	TestFind();
	
	TestListAppend();

	SListDestroy(list);
	SListDestroy(list2);

	return (0);
}

/*------------TestSetData------------*/
static void TestSetData()
{
	int data = 0;

	slist_iter_t head = SListGetBegin(list);
		
	SListSetData(head , &set_arr[0]);
	
	printf("--------Testing SetData--------\t");

	data = *(int*)SListGetData(head);
	(set_arr[0] == data) ? printf("Success\n") : printf("Failure\n");	
}

/*------------TestGetData------------*/
static void TestGetData()
{
	int data = 0;
	
	slist_iter_t second = SListGetBegin(list);
	
	second = SListNext(second);
		
	SListSetData(second , &set_arr[1]);
	
	printf("--------Testing GetData--------\t");
	
	data = *(int*)SListGetData(second);
	(set_arr[1] == data) ? printf("Success\n") : printf("Failure\n");	
}

/*------------TestGetBegin------------*/
static void TestGetBegin()
{
	slist_iter_t head = SListGetBegin(list);
	int value = 0;

	printf("--------Testing GetBegin--------");

	value = *(int*)SListGetData(head); 	
	(value == 8343) ? printf("Success\n") : printf("Failure\n"); 
}

/*------------TestGetEnd------------*/
static void TestGetEnd()
{
	slist_iter_t tail = SListGetEnd(list);

	printf("--------Testing GetEnd--------\t");
	
	(SListNext(tail) == NULL) ? printf("Success\n") : printf("Failure\n"); 
	
}

/*------------TestInsert------------*/
static void TestInsert()
{
	int test_counter = 7;
	
	size_t i = 0;
	
	slist_iter_t iter = SListGetBegin(list);	
	slist_iter_t new_iter = NULL;
	
	for(i=0; i<7; ++i)
	{
		iter = SListInsert(iter, &numbers[i]);
		new_iter = SListGetBegin(list);	
		if (iter == new_iter)
		{
			--test_counter;
		}		
	}
	
	printf("--------Testing Insert--------\t");

	(0 == test_counter) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestRemove------------*/
static void TestRemove()
{	
	slist_iter_t iter = NULL;
	
	int data = 0;
	
	iter = SListGetBegin(list);
	
	iter = SListRemove(iter);
	
	data = *(int*)SListGetData(iter);
	
	printf("--------Testing Remove--------\t");
	
	(4999 == data) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestListCount------------*/
static void TestListCount()
{
	printf("--------Testing ListCount------\t");
	
	(7 == SListCount(list)) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestIsEqual------------*/
static void TestIsEqual()
{
	slist_iter_t iter1 = SListGetBegin(list);
	slist_iter_t iter2 = SListNext(iter1);

	printf("--------Testing IsEqual--------\t");

	(0 == SListIsEqual(iter1 , iter2)) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestFind------------*/
static void TestFind()
{
	int x = 12;
	slist_iter_t iter1 = SListGetBegin(list);
	slist_iter_t iter2 = SListGetEnd(list);
	
	slist_iter_t it_result = SListFind(iter1 , iter2 , &IntCmp , &x);  
	
	
	printf("--------Testing Find--------\t");	
	
	(0 == SListIsEqual(it_result , SListGetEnd(list))) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestForEach------------*/
static void TestForEach()
{
	int x = 5;
	
	int result = 0;
	
	printf("--------Testing ForEach--------\t");
	
	result = SListForEach(SListGetBegin(list) , SListGetEnd(list) , &AddIntUntilDevil , &x);	
	(1 == result) ? printf("Success\n") : printf("Failure\n");
}

/*------------TestListAppend------------*/
static void TestListAppend()
{
	size_t testCount = 2;

	size_t i = 0;
	
	slist_iter_t iter = SListGetBegin(list2);	
	
	for(i=0; i<3; ++i)
	{
		iter = SListInsert(iter, &numbers2[i]);
	}
	
	printf("--------Testing ListAppend----- ");
	
	/* append to original list */
	SListAppend(list, list2);
	
	(9 == SListCount(list)) ? (--testCount) : (testCount) ;
	(0 == SListCount(list2)) ? (--testCount) : (testCount) ;
	(0 == testCount) ? printf("Success\n") : printf("Failure\n");
}

/*--------Match function: IntCmp---------*/
static int IntCmp(void *num1 , void *num2)
{
	return ( (*(int*)num1) - (*(int*)num2) ); 
}

/*-------Action function: AddIntUntilDevil--------*/
static int AddIntUntilDevil(void *data , void* x)
{
	if (*(int*)data == 666)
	{
		return (1);
	}
	
	*(int*)data += *(int*)x;
	return (0);
}

