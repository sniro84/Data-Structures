/************************************************ 
EXERCISE      : Recursion
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 9/6/2023
File          : recursion_test.c
*************************************************/

#include <stdio.h>     /* printf */
#include <stdlib.h>    /* malloc , free*/
#include <string.h>    /* strlen, strcpy, strcmp, strcat, strstr */

#include "recursion.h"
#include "stack.h" 

void TestFiboIterative();
void TestFiboRecursive();
void TestFiboWithMemoization();
void TestFlipList();
void TestStackSort();
void TestStrLen();
void TestStrCmp();
void TestStrCpy();
void TestStrCat();
void TestStrStr();

int main(void)
{
	TestFiboIterative();

	TestFiboRecursive();

	TestFiboWithMemoization();

	TestFlipList();

	TestStackSort();

	TestStrLen();

	TestStrCmp();

	TestStrCpy();

	TestStrCat();

	TestStrStr();

	return (0);
}

/* ------------- TestFiboIterative() -------------- */
void TestFiboIterative()
{
	int test_count = 5;

	printf("--------------- Testing FibonacciIter ----------------\t");

	/* 1,1,2,3,5,8,13, ...*/

	(FibonacciIter(0) == 1) ? --test_count : test_count;
	(FibonacciIter(1) == 1) ? --test_count : test_count;
	(FibonacciIter(2) == 2) ? --test_count : test_count;
	(FibonacciIter(5) == 8) ? --test_count : test_count;
	(FibonacciIter(40) == 165580141) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success") : printf("Failure");
	printf("\n");

}

/* ------------- TestFiboRecursive() -------------- */
void TestFiboRecursive()
{
	int test_count = 5;

	printf("--------------- Testing Fibonacci ----------------\t");

	/* 1,1,2,3,5,8,13, ...*/

	(Fibonacci(0) == 1) ? --test_count : test_count;
	(Fibonacci(1) == 1) ? --test_count : test_count;
	(Fibonacci(2) == 2) ? --test_count : test_count;
	(Fibonacci(5) == 8) ? --test_count : test_count;
	(Fibonacci(40) == 165580141) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success") : printf("Failure");
	printf("\n");

}

/* ------------- TestFiboWithMemoization() -------------- */
void TestFiboWithMemoization()
{
	int test_count = 5;

	printf("--------------- Testing FiboWithMemoization -----------\t");

	/* 1,1,2,3,5,8,13, ...*/

	(FibonacciWithMemoization(0) == 1) ? --test_count : test_count;
	(FibonacciWithMemoization(1) == 1) ? --test_count : test_count;
	(FibonacciWithMemoization(2) == 2) ? --test_count : test_count;
	(FibonacciWithMemoization(5) == 8) ? --test_count : test_count;
	(FibonacciWithMemoization(40) == 165580141) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success") : printf("Failure");
	printf("\n");

}

/* ------------- TestFlipList() -------------- */
void TestFlipList()
{
	node_t *reversed_list_head = NULL;

	size_t test_count = 5;

	node_t *node1 = (node_t*)malloc(sizeof(node_t));
	node_t *node2 = (node_t*)malloc(sizeof(node_t));
	node_t *node3 = (node_t*)malloc(sizeof(node_t));
	node_t *node4 = (node_t*)malloc(sizeof(node_t));

	node1->data = 1;
	node2->data = 2;
	node3->data = 3;
	node4->data = 4;
	
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;

	reversed_list_head = FlipList(node1);

	printf("--------------- Testing FlipLinkedList ----------------\t");

	(4 == reversed_list_head->data) ? --test_count : test_count;
	(3 == reversed_list_head->next->data) ? --test_count : test_count;
	(2 == reversed_list_head->next->next->data) ? --test_count : test_count;
	(1 == reversed_list_head->next->next->next->data) ? --test_count : test_count;
	(NULL == reversed_list_head->next->next->next->next) ? --test_count : test_count;

	(0 == test_count) ? printf("Success") : printf("Failure");

	printf("\n");

	free(node1);
	free(node2);
	free(node3);
	free(node4);
}

/* ------------- TestStackSort() -------------- */
void TestStackSort()
{
	int array[4] = {30,-5,18,14};
	size_t i = 0;

	size_t test_count = 4;

	stack_t *stack = StackCreate(4, sizeof(int));
	if (NULL == stack)
	{
		return;
	}

	for(i=0; i<4; ++i)
	{
		StackPush(stack, &array[i]);
	}

	StackSort(stack);

	printf("--------------- Testing StackSort ---------------------\t");
	(30 == *(int*)StackPeek(stack)) ? --test_count : test_count;
	StackPop(stack);
	
	(18 == *(int*)StackPeek(stack)) ? --test_count : test_count;
	StackPop(stack);
	
	(14 == *(int*)StackPeek(stack)) ? --test_count : test_count;
	StackPop(stack);
	
	(-5 == *(int*)StackPeek(stack)) ? --test_count : test_count;
	StackPop(stack);

	(0 == test_count) ? printf("Success") : printf("Failure");
	printf("\n");

	StackDestroy(stack);
}

/* ------------- TestStrLen() -------------- */
void TestStrLen()
{
	int test_count = 2;

	printf("--------------- Testing StrLen ---------------------\t");
	(StrLen("banana") == 6) ? --test_count : test_count;
	(StrLen("") == 0) ? --test_count : test_count;

	(0 == test_count) ? printf("Success") : printf("Failure");
	printf("\n");
}

/* ------------- TestStrCmp() -------------- */
void TestStrCmp()
{
	int test_count = 3;

	printf("--------------- Testing StrCmp ---------------------\t");
	(StrCmp("abba", "abba") == 0) ? --test_count : test_count;
	(StrCmp("abcdefg", "abd")  < 0) ? --test_count : test_count;
	(StrCmp("abedefg", "abd")  > 0) ? --test_count : test_count;

	(0 == test_count) ? printf("Success") : printf("Failure");
	printf("\n");
}

/* ------------- TestStrCpy() -------------- */
void TestStrCpy()
{
	char *src = "banana";
	char *dest = (char*)malloc(sizeof(char) * 9);

	printf("--------------- Testing StrCpy ---------------------\t");

	(StrCpy(dest,src) == strcpy(dest,src)) ? printf("Success") : printf("Failure");
	printf("\n");

	free(dest);
}

/* ------------- TestStrCat() -------------- */
void TestStrCat()
{
	char *src1 = "banana";
	char dest1[20] = "tut";

	char *src2 = "banana";
	char dest2[20] = "tut";

	printf("--------------- Testing StrCat ---------------------\t");

	(0 == StrCmp(StrCat(dest1,src1), strcat(dest2,src2))) ? printf("Success") : printf("Failure");
	printf("\n");
}

/* ------------- TestStrStr() -------------- */
void TestStrStr()
{
	char *haystack1 = "banaGananTUT";
	char needle1[20] = "nan";

	char *haystack2 = "banaGananTUT";
	char needle2[20] = "nan";

	char *haystack3 = "banaGananTUT";
	char needle3[20] = "PnanP";

	printf("--------------- Testing StrStr ---------------------\t");

	/* Shouldn't cause segfault */
	StrStr(haystack3,needle3);

	(0 == StrCmp(StrStr(haystack1,needle1), strstr(haystack2,needle2))) ? printf("Success") : printf("Failure");

	printf("\n");
}



