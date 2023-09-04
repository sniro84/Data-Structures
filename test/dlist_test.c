/************************************************ 
EXERCISE      : DS#7: LinkedList
Implmented by : Snir Holland
Reviewed by   : Noga Rotem 
Date          : 6/5/2023
File          : dlist_test.c
*************************************************/

#include "dlist.h" 
#include <stdio.h>

/*------Test Functions------------*/
static void TestIsEqual();
static void TestIsEmpty();
static void TestNext();
static void TestPrev();
static void TestInsert();
static void TestRemove();
static void TestGetData();
static void TestGetBegin();
static void TestGetEnd();
static void TestCount();
static void TestForEach();
static void TestPushFront();
static void TestPushEnd();
static void TestPopFront();
static void TestPopEnd();
static void TestFind();
static void TestSplice();
static void TestMultiFind();
/*-------------------------------*/

/*------Helper Functions---------*/
static void PrintList(dlist_t *);               
static int Triple(void * , void *);                  
static int PrintData(void * , void *);                
static int IntCmp(const void * , const void *);        
static int IsMultipleOf(const void * , const void *);
/*-------------------------------------------------*/

/*-------Global lists----*/
dlist_t *list = NULL;
dlist_t *output_list = NULL;
/*--------------------------*/

/*-------Global arrays----*/
int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };
int numbers2[3] = {500 , 600 , 700};
int numbers3[6] = {1993 , 1994 , 1995 , 1996 , 1997 , -1};
int push_pop[2] = {-999 , 404};
int val_for_splice = 1998;
/*------------------------*/

int main(void)
{
	list = DListCreate();
	output_list = DListCreate();
	
	TestIsEqual();		
	TestIsEmpty();
	TestInsert();
	TestGetData();
	TestGetBegin();
	TestGetEnd();
	TestNext();
	TestPrev();
	TestForEach();
	TestRemove();
	TestCount();
	TestPushFront();
	TestPushEnd();
	TestPopFront();
	TestPopEnd();
	TestFind();
	TestSplice();
	TestMultiFind();

	DListDestroy(list);
	DListDestroy(output_list);

	(void)PrintList;

	return (0);
}

/*---------TestIsEqual---------*/
static void TestIsEqual()
{
	size_t result = 0;
	dlist_iter_t head = DListGetBegin(list);
	dlist_iter_t tail = DListGetEnd(list);
	
	printf("--------Testing IsEqual()--------\t");
	
	result = DListIsEqual(head,tail);
	(1 == result) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestIsEmpty---------*/
static void TestIsEmpty()
{
	size_t result = 0;
	
	printf("--------Testing IsEmpty()--------\t");
	
	result = DListIsEmpty(list);
	(1 == result) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestInsert---------*/
static void TestInsert()
{
	size_t i = 0;
	
	int data_first = 0;
	
	size_t test_count = 2;
	
	dlist_iter_t head = DListGetBegin(list);
	
	for(i=0; i<7; ++i)
	{
		DListInsert(head, &numbers[i]);			
	}
	
	printf("--------Testing Insert()--------\t");
	
	data_first = *(int*)DListGetData(DListGetBegin(list));
		
	(numbers[0] == data_first) ? --test_count : test_count;
	(!DListIsEmpty(list)) ? --test_count : test_count;
		
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestRemove---------*/
static void TestRemove()
{

	int data_first = 0;
	
	size_t test_count = 2;
	
	dlist_iter_t head = DListGetBegin(list);
	
	DListRemove(head);
	
	printf("--------Testing Remove()--------\t");
	
	data_first = *(int*)DListGetData(DListGetBegin(list));
		
	(numbers[1] == data_first) ? --test_count : test_count;
	(!DListIsEmpty(list)) ? --test_count : test_count;
		
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestNext---------*/
static void TestNext()
{	
	dlist_iter_t head = DListGetBegin(list);
	
	dlist_iter_t third_iter = DListNext(DListNext(head));
	
	int *data = DListGetData(third_iter);
	
	printf("--------Testing Next()------------\t");
	
	(numbers[2] == *data) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestPrev---------*/
static void TestPrev()
{
	
	dlist_iter_t second = DListNext(DListGetBegin(list));
		
	dlist_iter_t iter = DListPrev(second);
	
	dlist_iter_t head = DListGetBegin(list);
	
	printf("--------Testing Prev()------------\t");

	(DListIsEqual(iter , head)) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestGetData---------*/
static void TestGetData()
{
	dlist_iter_t head = DListGetBegin(list);
	dlist_iter_t iter = DListNext(head);
	
	int *data = DListGetData(iter);
	
	printf("--------Testing GetData()--------\t");
	
	(numbers[1] == *data) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestGetBegin---------*/
static void TestGetBegin()
{
	dlist_iter_t first = DListGetBegin(list);
	
	int *data = DListGetData(first);
	
	printf("--------Testing GetBegin()--------\t");
	
	(numbers[0] == *data) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestGetEnd---------*/
static void TestGetEnd()
{	
	dlist_iter_t invalid_iter = DListGetEnd(list);
	
	printf("--------Testing GetEnd()--------\t");
	
	(NULL != invalid_iter) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestCount---------*/
static void TestCount()
{
	size_t iter_count = 0;
	
	iter_count = DListCount(list);
	
	printf("--------Testing Count()-----------\t");
	
	(6 == iter_count) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestForEach---------*/
static void TestForEach()
{
	dlist_iter_t iter = DListGetBegin(list);
	dlist_iter_t invalid_iter = DListGetEnd(list);
	
	int status = -1;
	
	int factor = 3;
	
	status = DListForEach(iter , invalid_iter , &Triple , &factor);
	
	printf("--------Testing ForEach()-----------\t"); 
	
	(0 == status) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestPushFront---------*/
static void TestPushFront()
{
	dlist_iter_t begin = NULL;
	
	int data = 0;
	
	printf("--------Testing PushFront()-----------\t");
		
	DListPushFront(list , &push_pop[0]);
	
	begin = DListGetBegin(list); 
	
	data = *(int*)DListGetData(begin);
	(push_pop[0] == data) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestPushEnd---------*/
static void TestPushEnd()
{
	dlist_iter_t end = NULL;
	
	int data = 0;
	
	printf("--------Testing PushEnd()-----------\t");
		
	end = DListPushEnd(list , &push_pop[1]);
		
	data = *(int*)DListGetData(end);
	(push_pop[1] == data) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestPopFront---------*/
static void TestPopFront()
{
	int data = 0;
	size_t node_count = 0;
	
	printf("--------Testing PopFront()-----------\t");
		
	data = *(int*)DListPopFront(list);
	node_count = DListCount(list);
	
	(push_pop[0] == data && 7 == node_count) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestPopEnd---------*/
static void TestPopEnd()
{
	int data = 0;
	size_t node_count = 0;
	
	printf("--------Testing PopEnd()-----------\t");
		
	data = *(int*)DListPopEnd(list);
	node_count = DListCount(list);
	
	(push_pop[1] == data && 6 == node_count) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestFind---------*/
static void TestFind()
{
	int num1 = 1998;
	int num2 = 45;
	
	dlist_iter_t result1 = NULL;
	dlist_iter_t result2 = NULL;
	
	size_t test_count = 2;
	
	dlist_iter_t begin = DListGetBegin(list);
	dlist_iter_t end = DListGetEnd(list); 	
	
	printf("--------Testing Find()-----------\t");
	
	result1 = DListFind(begin , end , &IntCmp , &num1);
	result2 = DListFind(begin , end , &IntCmp , &num2);  
	
	(num1 == *(int*)DListGetData(result1)) ? --test_count : test_count;
	(DListIsEqual(end , result2)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

/*---------TestSplice---------*/
static void TestSplice()
{
	size_t i = 0;
	
	size_t test_count = 2;
	 
	dlist_iter_t begin = DListGetBegin(list);
	dlist_iter_t end = DListGetEnd(list); 
	
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	dlist_iter_t where = NULL;
	
	for(i=0; i<6; ++i)
	{
		DListInsert(end, &numbers3[i]);			
	}
	
	from = DListFind(begin , end , &IntCmp , &numbers3[0]);
	to = DListFind(begin , end , &IntCmp , &numbers3[5]);
	where = DListFind(begin , end , &IntCmp , &val_for_splice);
		
	printf("--------Testing Splice()-----------\t");
	
	where = DListSplice(from , to , where);	
	
	(val_for_splice == *(int*)DListGetData(where)) ? --test_count : test_count;
	(numbers3[4] == *(int*)DListGetData(DListPrev(where))) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");	
}

/*---------TestMultiFind---------*/
static void TestMultiFind()
{
	int factor = 4;
	
	int status = -1; 
	
	dlist_iter_t begin = DListGetBegin(list);
	dlist_iter_t end = DListGetEnd(list); 	

	printf("--------Testing MultiFind()-----------\t");	
	
	status = DListMultiFind(begin , end , &IsMultipleOf , &factor , output_list);
	
	(0 == status) ? printf("Success\n") : printf("Failure\n");
}
/*---------------End of test functions----------------*/


/*---------------Helper Functions-------------------- */

/* This function multiplies an element by 3 */   
static int Triple(void *data , void *factor)
{
	*(int*)data *= *(int*)factor;
	return (0); 
}

/* This function compares between two integers */ 
static int IntCmp(const void *data , const void *param)
{
	return ( *(int*)data == *(int*)param );
}

/* This function returns 0 if data is a multiple of param */ 
static int IsMultipleOf(const void *data , const void *param)
{
	return *(int*)data  %  *(int*)param;
}

/* This function prints a single element */ 
static int PrintData(void *data , void *param)
{
	printf("%d -> " , *(int*)data);
	(void)param;
	return (0); 
}

/* This function prints the data of entire list */
static void PrintList(dlist_t *list)
{
	dlist_iter_t iter = DListGetBegin(list);
	dlist_iter_t invalid_iter = DListGetEnd(list);
	
	void *nothing = NULL;
	
	printf("Printing list :  ");
	
	DListForEach(iter , invalid_iter , &PrintData , nothing); 
	
	printf("NULL\n");
}
/*---------------End of helper functions----------------*/







