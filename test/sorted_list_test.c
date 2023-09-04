/************************************************ 
EXERCISE      : DS#8: Sorted Linked List
Implmented by : Snir Holland
Reviewed by   : Adir Askayo 
Date          : 7/5/2023
File          : sorted_list_test.c
*************************************************/

#include <stdio.h>
#include "sorted_list.h" 

/*------Test Functions------------*/
static void TestInsert();
static void TestRemove();
static void TestIsEmpty();
static void TestNext();
static void TestPrev();
static void TestGetData();
static void TestGetBegin();
static void TestGetEnd();
static void TestSize();
static void TestIsEqual();
static void TestPopFront();
static void TestPopBack();
static void TestForEach();
static void TestFind();
static void TestFindIf();
static void TestMerge();
/*-------------------------------*/



/*------Helper Functions------------*/
static int IsMultipleOf(const void *data1 , const void *data2);
static int IntCmp(const void * , const void *);
static int Quadruple(void * , void *); 
static void PrintList(sorted_list_t *list);
/*-------------------------------*/



/*-------Global lists----*/
sorted_list_t *list = NULL;
sorted_list_t *another_list = NULL;

/*-------Global array----*/
int numbers[7] = {3, 12 , -8 , 666 , -1, 20 , 40 };
int numbers2[7] = {100, 34 , 172 , 79 , 33, 171 , 49 };



int main(void)
{
	list = SortedListCreate(&IntCmp);
	
	TestIsEmpty();
	
	TestInsert();
	
	TestRemove();
	
	TestNext();
	
	TestPrev();
	
	TestGetBegin();
	
	TestGetEnd();
	
	TestGetData();
	
	TestSize();
	
	TestIsEqual();
	
	TestPopFront();
	
	TestPopBack();
	
	TestFindIf();
	
	TestFind();
	
	TestForEach();
	
	TestMerge();
	
	SortedListDestroy(list);
	
	SortedListDestroy(another_list);
	
	(void)PrintList;

	return (0);
}

static void TestInsert()
{
	size_t i = 0;
	int data = 0;
	
	for(i=0; i<7; ++i)
	{
		SortedListInsert(list, &numbers[i]);			
	}
	
	printf("--------Testing Insert()--------\t");
	data = *(int*)SortedListGetData(SortedListBegin(list));
	(-8 == data)? printf("Success\n") : printf("Failure\n");
}

static void TestRemove()
{
	int first_data = 0;
	
	sorted_list_iter_t iter = SortedListNext(SortedListBegin(list));
	
	SortedListRemove(iter);
	
	printf("--------Testing Remove()--------\t");
	first_data = *(int*)SortedListGetData(SortedListNext(SortedListBegin(list)));
	(3 == first_data)? printf("Success\n") : printf("Failure\n");
	
}

static void TestIsEmpty()
{
	printf("--------Testing IsEmpty()--------\t");
	(SortedListIsEmpty(list)) ? printf("Success\n") : printf("Failure\n");
}

static void TestNext()
{
	int data = 0;
	
	sorted_list_iter_t iter = SortedListBegin(list);
	iter = SortedListNext(SortedListNext(iter));
	
	printf("--------Testing Next()-----------\t");
	data = *(int*)SortedListGetData(iter);
	(12 == data)? printf("Success\n") : printf("Failure\n");
}

static void TestPrev()
{
	int data = 0;
	
	sorted_list_iter_t iter = SortedListEnd(list);
	iter = SortedListPrev(SortedListPrev(iter));
	
	printf("--------Testing Prev()-----------\t");
	data = *(int*)SortedListGetData(iter);
	(40 == data)? printf("Success\n") : printf("Failure\n");

}

static void TestGetData()
{
	int data = 0;
	
	sorted_list_iter_t iter = SortedListBegin(list);
	
	printf("--------Testing GetData()--------\t");
	data = *(int*)SortedListGetData(iter);
	(-8 == data)? printf("Success\n") : printf("Failure\n");
}


static void TestGetBegin()
{
	int data = 0;
	
	sorted_list_iter_t iter = SortedListBegin(list);
	
	printf("--------Testing GetBegin()--------\t");
	data = *(int*)SortedListGetData(iter);
	(-8 == data)? printf("Success\n") : printf("Failure\n");
}

static void TestGetEnd()
{
	int data = 0;
	
	sorted_list_iter_t iter = SortedListEnd(list);
	iter = SortedListPrev(iter);
	
	printf("--------Testing GetEnd()--------\t");
	data = *(int*)SortedListGetData(iter);
	(666 == data)? printf("Success\n") : printf("Failure\n");	
}

static void TestSize()
{
	size_t iter_count = 0;
		
	iter_count = SortedListSize(list);	
	printf("--------Testing Size()-----------\t");
	(6 == iter_count)? printf("Success\n") : printf("Failure\n");	
}

static void TestIsEqual()
{
	sorted_list_iter_t iter1 = SortedListBegin(list);
	sorted_list_iter_t iter2 = SortedListBegin(list);
	
	printf("--------Testing IsEqual()--------\t");
	(SortedListIsEqual(iter1 , iter2)) ? printf("Success\n") : printf("Failure\n");
}

static void TestPopFront()
{
	size_t test_count = 2;	
	
	size_t iter_count = 0;
	int data = 0;
	
	data = *(int*)SortedListPopFront(list);	
	iter_count = SortedListSize(list);
		
	printf("--------Testing PopFront()--------\t");
	
	(5 == iter_count) ? --test_count : test_count;
	(-8 == data) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

static void TestPopBack()
{
	size_t test_count = 2;	
	
	size_t iter_count = 0;
	int data = 0;
	
	data = *(int*)SortedListPopBack(list);	
	iter_count = SortedListSize(list);
		
	printf("--------Testing PopBack()--------\t");
	
	(4 == iter_count) ? --test_count : test_count;
	(666 == data) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");	
}

static void TestFind()
{
	size_t test_count = 2;
	int data_recieved = 0;
	
	sorted_list_iter_t from = SortedListBegin(list);
	sorted_list_iter_t to = SortedListEnd(list);
	sorted_list_iter_t result1 = {NULL};
	sorted_list_iter_t result2 = {NULL};		
	
	int data_to_find1 = 20;
	int data_to_find2 = 404;
	
	result1 = SortedListFind(list , from , to , &data_to_find1);
	result2 = SortedListFind(list , from , to , &data_to_find2);
	
	data_recieved = *(int*)SortedListGetData(result1);
		
	printf("--------Testing Find()-----------\t");
	
	(20 == data_recieved) ? --test_count : test_count;
	
	(SortedListIsEqual(to , result2)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

static void TestFindIf()
{
	size_t test_count = 2;
	int data_recieved = 0;
	
	sorted_list_iter_t from = SortedListBegin(list);
	sorted_list_iter_t to = SortedListEnd(list);
	sorted_list_iter_t result1 = {NULL};
	sorted_list_iter_t result2 = {NULL};		
	
	int factor = 4;
	int another_factor = 7;
	
	result1 = SortedListFindIf(from , to , &IsMultipleOf , &factor);
	result2 = SortedListFindIf(from , to , &IsMultipleOf , &another_factor);
	
	data_recieved = *(int*)SortedListGetData(result1);
		
	printf("--------Testing FindIf()--------\t");
	
	(12 == data_recieved) ? --test_count : test_count;
	(SortedListIsEqual(to , result2)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

static void TestForEach()
{
	sorted_list_iter_t from = SortedListBegin(list);
	sorted_list_iter_t to = SortedListEnd(list);
	
	int data = 0;
	
	void* nothing = NULL;
	
	SortedListForEach(from , to , &Quadruple , nothing);		

	printf("--------Testing ForEach()--------\t");
	
	data = *(int*)SortedListGetData(SortedListBegin(list));
	
	(12 == data) ? printf("Success\n") : printf("Failure\n");
}


static void TestMerge()
{
	size_t i = 0;
	size_t iter_count = 0;
	size_t test_count = 2;
	
	another_list = SortedListCreate(&IntCmp);
	
	for(i=0; i<7; ++i)
	{
		SortedListInsert(another_list, &numbers2[i]);			
	}
	
	SortedListMerge(list , another_list);
	
	printf("--------Testing Merge()-----------\t");
	
	iter_count = SortedListSize(list);
		
	(11 == iter_count) ? --test_count  :  test_count;
	(SortedListIsEmpty(another_list)) ? --test_count  :  test_count;
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}
/*----------End of Testing Functions--------------------*/


/*--------------- Helper Functions--------------------*/
static int IntCmp(const void *data1, const void *data2)
{
	return (*(int*)data1 - *(int*)data2);
}

static int IsMultipleOf(const void *data1 , const void *data2)
{
	return (0 == *(int*)data1 % *(int*)data2); 
}

/* This function prints the data of entire list */
static void PrintList(sorted_list_t *list)
{
	sorted_list_iter_t iter = SortedListBegin(list);
	sorted_list_iter_t invalid_iter = SortedListEnd(list);
	
	int *data = NULL;
	
	printf("Printing list :  ");
	
	while (!SortedListIsEqual(iter , invalid_iter))
	{
		data = SortedListGetData(iter);
		printf("%d -> " , *data);  
		iter = SortedListNext(iter);
	}
	
	printf("NULL\n");
}

/* This function muliplies an int by 4 */
static int Quadruple(void *data1 , void *data2)
{
	(void)data2;
	
	*(int*)data1 *= 4;
	
	return (0);
} 
/*---------------End of helper functions----------------*/





