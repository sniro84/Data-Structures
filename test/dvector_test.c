/************************************************ 
EXERCISE <3>    : DS: Dyncamic vector
Implmented by : Snir Holland
Reviewed by   : Daniel Haimov
Date          : 27/4/2023
File          : DVector_Test.c
*************************************************/

#include "dvector.h" 
#include <stdio.h>

static void TestGetCapacity();
static void TestGetSize();
static void TestPushBack();
static void TestPopBack();
static void TestGetAccess();
static void TestDVectorReserve();
static void TestDVectorShrink();

d_vector_t *vecpnt = NULL;

int main(void)
{
	
	vecpnt = DVectorCreate(3,sizeof(int));
		
	TestPushBack();
	
	TestGetAccess();
	
	TestGetCapacity();
	
	TestGetSize();
	
	TestPopBack();

	TestDVectorReserve();
	
	TestDVectorShrink();
	
	DVectorDestroy(vecpnt);
	
	return (0);
}


static void TestGetCapacity()
{
	size_t cap = DVectorGetCapacity(vecpnt);
	printf("----Testing GetCapacity()---- ");
	(cap == 24) ? printf("Success\n") : printf("Failure\n");
}


static void TestGetSize()
{
	size_t elem_count = DVectorGetSize(vecpnt);
	printf("----Testing GetSize()----     ");
	(elem_count == 20) ? printf("Success\n") : printf("Failure\n");
}

static void TestPushBack()
{
	int i = 0;
	
	int is_push_valid = 1;
	
	printf("----Testing PushBack()----    ");
	
	for(i=0; i<20; ++i)
	{
		DVectorPushBack(vecpnt , &i );
		if (i != *(int*)DVectorGetAccess(vecpnt , i))
		{
			is_push_valid = 0;
			break;	
		}
	}

	(is_push_valid) ? printf("Success\n") : printf("Failure\n");
	
}

static void TestPopBack()
{
	int i = 0;
	
	int is_pop_valid = 1;
	
	printf("----Testing PopBack()----     ");
	
	for(i=0; i<20; ++i)
	{
		DVectorPopBack(vecpnt);
	}
 
	if (DVectorGetCapacity(vecpnt) != 6  ||  DVectorGetSize(vecpnt) != 0)
	{
		is_pop_valid = 0;
	}
		
	(is_pop_valid) ? printf("Success\n") : printf("Failure\n");
}

static void TestGetAccess()
{
	int is_access_valid = 1;	
	
	int value = 0;
	
	printf("----Testing GetAccess()----   ");
	
	*(int*)DVectorGetAccess(vecpnt , 1) = 666;
	value = *(int*)DVectorGetAccess(vecpnt , 1);
	if (value != 666)
	{
		is_access_valid = 0;
	}
	
	(is_access_valid) ? printf("Success\n") : printf("Failure\n");
}

static void TestDVectorReserve()
{
	size_t cap = 0;
	printf("----Testing Reserve()----     ");
	DVectorReserve(vecpnt, 70);
	
	cap = DVectorGetCapacity(vecpnt);
	
	(cap == 70) ? printf("Success\n") : printf("Failure\n");
}

static void TestDVectorShrink()
{
	int a = 7;
	int b = 9;
	
	size_t cap = 0;

	int is_shrink_valid = 1;	
		
	printf("----Testing Shrink()----      ");	
	
	DVectorShrink(vecpnt);
	cap = DVectorGetCapacity(vecpnt);
	if (cap != 1)
	{
		is_shrink_valid = 0;
	}
	
	DVectorReserve(vecpnt, 50);
	DVectorPushBack(vecpnt , &a );
	DVectorPushBack(vecpnt , &b );
	
	
	DVectorShrink(vecpnt);
	cap = DVectorGetCapacity(vecpnt);
	
	if (cap != 4)
	{
		is_shrink_valid = 0;
	}
	(is_shrink_valid) ? printf("Success\n") : printf("Failure\n");
}

