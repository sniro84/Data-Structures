/************************************************ 
EXERCISE <1>    : DS#2: Stack
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 16/4/2023
File          : Stack_Test.c
*************************************************/

#include "stack.h" 
#include <stdio.h>

#define CAPACITY 20

static void TestStackPush();
static void TestStackPop();
static void TestStackPeek();
static void TestStackIsEmpty();
static void TestStackGetSize();
static void TestGetCapacity();

stack_t *stack_p = NULL;

int main(void)
{
	stack_p = StackCreate(CAPACITY,sizeof(int));
	
	TestStackIsEmpty();	
	
	TestStackPush();
	
	TestStackPeek();
	
	TestStackPop();
	
	TestStackGetSize();
	
	TestGetCapacity();

	StackDestroy(stack_p);
	
	return (0);
}
	
static void TestStackIsEmpty()
{
	printf("Testing IsEmpty : ");
	if (!StackIsEmpty(stack_p))
	{
		printf("Failed.\n");
	}

	else
	{
		printf("Success.\n");
	}
}	
	
static void TestStackPush()
{
	size_t i = 0;
	
	printf("Testing Push : ");
		
	for(i=1; i<=CAPACITY; i++)
	{
		StackPush(stack_p , &i);
		if (*(int*)StackPeek(stack_p) != (int)i)
		{
			printf("Failed.\n");
			return;
		}	
	}
	
	printf("Success.\n");	
}


static void TestStackPeek()
{
	printf("Testing Peek : ");
	if (*(int*)StackPeek(stack_p) != CAPACITY) /* stack is full at that time */   
	{
		printf("Failed.\n");
	}
	else
	{
		printf("Success.\n");
	}
}

static void TestStackPop()
{
	int i = 0;
	printf("Testing Pop : ");
	
	for(i=1; i<6; i++)
	{
		StackPop(stack_p);
		if ( *(int*)StackPeek(stack_p) != CAPACITY - i )  
		{
			printf("Failed.\n");
		}	
	}
	printf("Success.\n");
}

static void TestStackGetSize()
{
	printf("Testing GetSize : ");
	if (StackGetSize(stack_p) != CAPACITY - 5 )
	{
		printf("Failed.\n");
	}
	else
	{
		printf("Success.\n");
	}
}

static void TestGetCapacity()
{
	printf("Testing GetCapacity : ");
	
	if (StackGetCapacity(stack_p) != CAPACITY )
	{
		printf("Failed.\n");
	}
	else
	{
		printf("Success.\n");
	}
}

