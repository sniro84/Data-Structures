/************************************************ 
EXERCISE <1>    : DS#6: Circular Buffer
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 18/4/2023
File          : CBuffer_Test.c
*************************************************/

#include "cbuffer.h" 
#include <stdio.h>  /* printf */

static void TestRead();
static void TestWrite();
static void	TestGetFreeSpace();
static void	TestSiz();	
static void	TestIsEmpty();

c_buff_t *buff = NULL;

int main(void)
{
	buff = CBuffCreate(6);
	
	TestWrite();
	
	TestRead();
	
	TestGetFreeSpace();

	TestSiz();	

	TestIsEmpty();
	
	CBuffDestroy(buff);
	
	return (0);
}

static void TestRead()
{
	size_t result = 0;
	
	char str[10] = {'H' , 'e' , 'l' , 'l' , 'o' , 's' , 'n' , 'i' , 'r' , '\0'};
	
	result = CBuffRead(buff, str, 2);
	
	printf("----Testing Read()--------\t");
	(2 == result) ? printf("Success\n") : printf("Failure\n");
}

static void TestWrite()
{
	int result = 0;
	size_t test_count = 2;

	char str[10] = {'H' , 'e' , 'l' , 'l' , 'o' , 's' , 'n' , 'i' , 'r' , '\0'};
		
	result = CBuffWrite(buff, str, 8);
	if (6 == result)
	{
		--test_count;
	}
	
	result = CBuffWrite(buff, str, 1);
	if (-1 == result)
	{
		--test_count;
	}
	
	printf("----Testing Write()--------\t");
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
}

static void TestGetFreeSpace()
{
	size_t result = 0;

	result = CBuffGetFreeSpace(buff);	
	
	printf("----Testing GetFreeSpace()---\t");
	(2 == result) ? printf("Success\n") : printf("Failure\n");	
}

static void TestSiz()
{
	size_t result = 0;

	result = CBuffSiz(buff);	
	
	printf("----Testing BuffSiz()-------\t");
	(4 == result) ? printf("Success\n") : printf("Failure\n");	
}

static void TestIsEmpty()
{
	size_t result = 0;

	result = CBuffIsEmpty(buff);
	printf("----Testing IsEmpty()----\t");
	(0 == result) ? printf("Success\n") : printf("Failure\n");
}

