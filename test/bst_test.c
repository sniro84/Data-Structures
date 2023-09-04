/************************************************ 
EXERCISE      : Binary Search Tree
Implmented by : Snir Holland
Reviewed by   : Amitai Bar
Date          : 5/6/23
File          : bst_test.c
*************************************************/
#include <stdio.h> /* printf */

#include "bst.h"

/* Test Functions */
static void TestBSTCreate();
static void TestBSTInsert();
static void TestBSTSize();
static void TestBSTDestroy();
static void TestBSTRemove();
static void TestBSTFind();
static void TestBSTGetBegin();
static void TestBSTGetEnd();
static void TestBSTNext();
static void TestBSTPrev();
static void TestBSTGetData();
static void TestBSTIsSameIter();
static void TestBSTForEach();
static void TestBSTIsEmpty();

/* Compare Function */
static int IntCmp(const void *data1 , const void *data2);

/* Operation Functions */
static int Quadruple(void *data1 , void *data2);

int main(void)
{
	TestBSTCreate();

	TestBSTInsert();

	TestBSTSize();

	TestBSTDestroy();

	TestBSTRemove();

	TestBSTFind();

	TestBSTGetBegin();

	TestBSTGetEnd();
	
	TestBSTNext();
	
	TestBSTPrev();

	TestBSTGetData();

	TestBSTIsSameIter();

	TestBSTForEach();
	
	TestBSTIsEmpty();

	return (0);
}

/*----------- TestBSTCreate() -----------*/
static void TestBSTCreate()
{
	bst_t *bst = BSTCreate(&IntCmp);

	printf("--------Testing BSTCreate()--------\t");
	
	(NULL != bst) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTInsert() -----------*/
static void TestBSTInsert()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t test_count = 1;
	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	(7 == BSTSize(bst) ? --test_count : test_count);

	printf("--------Testing BSTInsert()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTSize() -----------*/
static void TestBSTSize()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t test_count = 2;
	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};

	(0 == BSTSize(bst)) ? --test_count : test_count; 

	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	(7 == BSTSize(bst) ? --test_count : test_count);

	printf("--------Testing BSTSize()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTDestroy() -----------*/
static void TestBSTDestroy()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t test_count = 1;
	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	(7 == BSTSize(bst) ? --test_count : test_count);

	BSTDestroy(bst);

	printf("--------Testing BSTDestroy()--------\t");

	/* checks will be done through valgrind (no leaks and errors) */
	printf("Success\n");
}

/*----------- TestBSTRemove() -----------*/
static void TestBSTRemove()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t test_count = 3;

	int data = 20;

	size_t i = 0;

	bst_iter_t iter_to_remove = NULL;

	int numbers[7] = {20,13,18,24,6,19,21};

	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	iter_to_remove = BSTGetBegin(bst);
	BSTRemove(iter_to_remove);

	(6 == BSTSize(bst) ? --test_count : test_count);

	iter_to_remove = BSTGetBegin(bst);
	BSTRemove(iter_to_remove);

	(5 == BSTSize(bst) ? --test_count : test_count);

	iter_to_remove = BSTFind(bst, &data);
	BSTRemove(iter_to_remove);

	(4 == BSTSize(bst) ? --test_count : test_count);

	printf("--------Testing BSTRemove()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTFind() -----------*/
static void TestBSTFind()
{
	bst_t *bst = BSTCreate(&IntCmp);

	int data1 = 21; /* in the tree */
	int data2 = 666; /* not in the tree */


	size_t test_count = 2;
	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};

	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	(BSTGetEnd(bst) != BSTFind(bst, &data1) ? --test_count : test_count);
	(BSTGetEnd(bst) == BSTFind(bst, &data2) ? --test_count : test_count);

	printf("--------Testing BSTFind()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTGetBegin() -----------*/
static void TestBSTGetBegin()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	printf("--------Testing BSTGetBegin()--------\t");

	(6 == *(int*)BSTGetData(BSTGetBegin(bst))) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTGetEnd() -----------*/
static void TestBSTGetEnd()
{
	bst_t *bst = BSTCreate(&IntCmp);

	bst_iter_t invalid_iter = BSTGetEnd(bst);

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	printf("--------Testing BSTGetEnd()--------\t");

	(NULL == BSTGetData(invalid_iter)) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTNext() -----------*/
static void TestBSTNext()
{
	bst_t *bst = BSTCreate(&IntCmp);

	bst_iter_t iter = NULL;

	size_t test_count = 2;

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	iter = BSTGetBegin(bst);

	iter = BSTNext(iter);
	(13 == *(int*)BSTGetData(iter)) ? --test_count : test_count;


	iter = BSTNext(iter);
	(18 == *(int*)BSTGetData(iter)) ? --test_count : test_count;

	printf("--------Testing BSTNext()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTPrev() -----------*/
static void TestBSTPrev()
{
	bst_t *bst = BSTCreate(&IntCmp);

	bst_iter_t iter = NULL;

	size_t test_count = 2;

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	iter = BSTGetBegin(bst);

	iter = BSTNext(iter);
	iter = BSTNext(iter);
	iter = BSTNext(iter);
	iter = BSTNext(iter);
	iter = BSTNext(iter);

	iter = BSTPrev(iter);
	(20 == *(int*)BSTGetData(iter)) ? --test_count : test_count;


	iter = BSTPrev(iter);
	(19 == *(int*)BSTGetData(iter)) ? --test_count : test_count;

	printf("--------Testing BSTPrev()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTGetData() -----------*/
static void TestBSTGetData()
{
	bst_t *bst = BSTCreate(&IntCmp);

	bst_iter_t iter = NULL;

	size_t test_count = 2;

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	iter = BSTGetBegin(bst);
	(6 == *(int*)BSTGetData(iter)) ? --test_count : test_count;

	iter = BSTNext(iter);
	(13 == *(int*)BSTGetData(iter)) ? --test_count : test_count;

	printf("--------Testing BSTGetData()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTIsSameIter() -----------*/
static void TestBSTIsSameIter()
{
	bst_t *bst = BSTCreate(&IntCmp);

	bst_iter_t iter1 = NULL;
	bst_iter_t iter2 = NULL;

	int data = 19;

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	iter1 = BSTFind(bst, &data);	
	iter2 = BSTFind(bst, &data);

	printf("--------Testing BSTIsSameIter()--------\t");

	(BSTIsSameIter(iter1, iter2)) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTForEach() -----------*/
static void TestBSTForEach()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t test_count = 2;

	bst_iter_t from = NULL;
	bst_iter_t to = NULL;

	bst_iter_t new_tree_begin = NULL;

	int for_each_status = -1;


	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};
	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	from = BSTGetBegin(bst);	
	to = BSTGetEnd(bst);

	printf("--------Testing BSTForEach()--------\t");

	for_each_status = BSTForEach(from, to, &Quadruple, NULL);
	new_tree_begin = BSTGetBegin(bst);

	(0 == for_each_status) ? --test_count : test_count;
	(24 == *(int*)BSTGetData(new_tree_begin)) ? --test_count : test_count;

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------- TestBSTIsEmpty() -----------*/
static void TestBSTIsEmpty()
{
	bst_t *bst = BSTCreate(&IntCmp);

	size_t test_count = 2;

	size_t i = 0;

	int numbers[7] = {20,13,18,24,6,19,21};

	(BSTIsEmpty(bst)) ? --test_count : test_count;

	for(i=0; i<7; ++i)
	{
		BSTInsert(bst, &numbers[i]);
	}

	(!BSTIsEmpty(bst)) ? --test_count : test_count;

	printf("--------Testing BSTIsEmpty()--------\t");

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	BSTDestroy(bst);
}

/*----------End of Test Functions---------*/

/* Compare Function: returns difference between ints */
static int IntCmp(const void *data1 , const void *data2)
{
	return (*(int*)data1 - *(int*)data2);
}

/* Operation Function: multiplies by 4 */
static int Quadruple(void *data1 , void *data2)
{
	*(int*)data1 *= 4;
	(void)data2;

	return (0);
}