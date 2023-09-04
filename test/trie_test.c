/************************************************ 
EXERCISE      : Trie
Implmented by : Snir Holland
Reviewed by   : 
Date          : 22/6/23
File          : trie_test.c
*************************************************/

#include <stdio.h> /* printf */

#include "trie.h"
	
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_RESET   "\x1b[0m"

void TestTrieCreate(void);
void TestTrieInsert(void);
void TestTrieCount(void);
void TestTrieRemove(void);

static void PrintTestResult(char *func_name, int boolean);

int main()
{
	TestTrieCreate();
	TestTrieInsert();
	TestTrieCount();
	TestTrieRemove();
		
	return 0;
}
	
static void PrintTestResult(char *func_name, int boolean)
{
	if (boolean)
	{
		printf(ANSI_GREEN "%s test : SUCCESS\n" ANSI_RESET, func_name);
	}
	else
	{
		printf(ANSI_RED "%s test : FAILED\n" ANSI_RESET, func_name);
	}
}	

void TestTrieCreate(void)
{
	size_t height = 8;
	trie_t *trie = NULL;

	trie = TrieCreate(height);
	if(NULL != trie)
	{
		PrintTestResult("TrieCreate", 1);		
	}
	
	else
	{
		PrintTestResult("TrieCreate", 0);		
	}

	TrieDestroy(trie);
}

void TestTrieInsert(void)
{
	unsigned char host1[9] = "00000000";
	unsigned char host2[9] = "00000000";
	unsigned char host3[9] = "00000000";
	unsigned char host4[9] = "00001000";
	unsigned char result[9] = {'\0'};
	size_t height = 8;
	int status = 0;
	trie_t *trie = NULL;
	size_t size = 0;

	trie = TrieCreate(height);

	size = TrieCount(trie);
 	status = TrieInsert(trie, host1, result);
 	status = TrieInsert(trie, host2, result);
	status = TrieInsert(trie, host3, result);
	status = TrieInsert(trie, host3, result);
	status = TrieInsert(trie, host4, result);

	if(0 == size && 5 == TrieCount(trie) && 0 == status)
	{
		PrintTestResult("TrieInsert", 1);		
	}
	
	else
	{
		PrintTestResult("TrieInsert", 0);		
	}

	TrieDestroy(trie);	
}

void TestTrieCount(void)
{
	unsigned char host1[9] = "00000000";
	unsigned char host2[9] = "00000000";
	unsigned char host3[9] = "00000000";
	unsigned char host4[9] = "00001000";
	unsigned char result[9] = {'\0'};
	size_t height = 8;
	int status = 0;
	trie_t *trie = NULL;
	size_t size1 = 0;
	size_t size2 = 0;

	trie = TrieCreate(height);

	size1 = TrieCount(trie);

 	status = TrieInsert(trie, host1, result);
 	status = TrieInsert(trie, host2, result);
	status = TrieInsert(trie, host3, result);

	size2 = TrieCount(trie);

	status = TrieInsert(trie, host3, result);
	status = TrieInsert(trie, host4, result);

	if(0 == size1 && size2 == 3 && 5 == TrieCount(trie))
	{
		PrintTestResult("TrieCount", 1);		
	}
	
	else
	{
		PrintTestResult("TrieCount", 0);		
	}

    (void)status;

	TrieDestroy(trie);	
}

void TestTrieRemove(void)
{
	unsigned char host1[9] = "00000000";
	unsigned char host2[9] = "00000000";
	unsigned char host3[9] = "00000000";
	unsigned char host4[9] = "00001000";
	unsigned char remove1[9] = "00000011";
	unsigned char remove2[9] = "00000000";
	unsigned char result[9] = {'\0'};
	size_t height = 8;
	int status = 0;
	trie_t *trie = NULL;

	trie = TrieCreate(height);

 	status = TrieInsert(trie, host1, result);
 	status = TrieInsert(trie, host2, result);
	status = TrieInsert(trie, host3, result);
	status = TrieInsert(trie, host3, result);
	status = TrieInsert(trie, host4, result);

	TrieRemove(trie, remove1);
	TrieRemove(trie, remove2);

	if(3 == TrieCount(trie))
	{
		PrintTestResult("TrieRemove", 1);		
	}
	
	else
	{
		PrintTestResult("TrieRemove", 0);		
	}

    (void)status;

	TrieDestroy(trie);		
}

