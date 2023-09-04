/************************************************ 
EXERCISE      : Recursion
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 9/6/2023
File          : recursion.c
*************************************************/

#include <stddef.h>   /* size_t  */
#include <string.h>   /* strncmp */
#include <assert.h>   /* assert  */
#include <stdio.h>    /* stderr */
#include <stdlib.h>   /* malloc, free */

#include "recursion.h"

/* Helper function: perform fibonacci series calculations with tail recursion */
static int FiboTailRec(int n, int a, int b);

/* Helper function: perform fibonacci series calculations with array of results */
static int FiboWithMemoRec(int index, int *res);

/* Helper function: push element into stack in sorted order */
static void StackPushByOrder(stack_t *stack, int data);


/* ------------- FibonacciIter -------------- */
int FibonacciIter(int element_index)
{

    int i = 0;
    int a = 1;
    int b = 1;
    int result = a + b;

    assert(element_index >= 0);

    if (element_index < 2)
    {
        return (1);
    }

    for (i = 2; i<element_index; ++i)
    {
        a = b;
        b = result;
        result = a+b;
    }

    return result;
}

/* ------------- Fibonacci -------------- */
int Fibonacci(int element_index)
{
    int a = 1;
    int b = 1;

    assert(element_index >= 0);

    return FiboTailRec(element_index, a, b);
}

static int FiboTailRec(int n, int a, int b)
{
    assert(n >= 0);
    assert(a >= 0);
    assert(b >= 0);

    if (0 == n)
    {
        return a;
    }

    else if (1 == n)
    {
        return b;
    }

    return FiboTailRec(n - 1 , b , a + b);
}

/* Returns the element of fibonacci series in an index (efficient recursive solution) */
int FibonacciWithMemoization(int element_index)
{
    int i = 0;
    int final_result = 0;
    int *results = (int*)malloc((element_index + 1) * sizeof(int));


    if (NULL == results)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }

    for(i=0; i<element_index+1; ++i)
    {
        results[i] = -1;
    }
    results[0] = 1;
    results[1] = 1;

    final_result = FiboWithMemoRec(element_index, results);

    free(results);
    results = NULL;

    return final_result;
}

static int FiboWithMemoRec(int index, int *res)
{
    if (0 == index || 1 == index)
    {
        return res[index];
    }

    if (-1 == res[index])
    {
        res[index] = FiboWithMemoRec(index - 1, res) + FiboWithMemoRec(index - 2, res);
    }
    return res[index];
}

/* ------------- FlipList -------------- */
node_t *FlipList(node_t *node)
{
    node_t *reversed_list_head = NULL;
    
    if (NULL == node || NULL == node->next)
    {
        return node;
    }

    reversed_list_head = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;

    return reversed_list_head;
}

/* ------------- StrLen -------------- */
size_t StrLen(char *str)
{
    assert(NULL != str);

    if ('\0' == *str)
    {
        return 0;
    }
    return 1 + StrLen(str + 1);
}

/* ------------- StrCmp -------------- */
int StrCmp(const char *str1, const char *str2)
{
    assert(NULL != str1);
    assert(NULL != str2);

    if (*str1 != *str2)
    {
        return (*str1 - *str2);
    }

    if ('\0' == *str1 && '\0' == *str2)
    {
        return (0);
    } 
    return StrCmp(str1 + 1, str2 + 1);
}

/* ------------- StrCpy -------------- */
char *StrCpy(char *dest, const char *src)
{
    assert(NULL != dest);
    assert(NULL != src);

    if ('\0' == *src)
    {
        return dest;
    }

    *dest = *src;

    StrCpy(dest + 1, src + 1);
    
    return dest;
}

/* ------------- StrCat -------------- */
char *StrCat(char *dest, const char *src)
{
    assert(NULL != dest);
	assert(NULL != src);

	if ('\0' == *dest)
	{
		return StrCpy(dest, src);
	}

	StrCat(dest + 1, src);
	return dest;
}

/* ------------- StrStr -------------- */
char *StrStr(const char *haystack, const char *needle)
{
    assert(NULL != haystack);
    assert(NULL != needle);

    if (*haystack == '\0')
    {
        return NULL; 
    }

    if (0 == strncmp(needle, haystack, StrLen((char*)needle)))
    {
        return (char*)haystack;
    }

    return StrStr(haystack + 1, needle);
}

/* ------------- StackSort -------------- */
void StackSort(stack_t *stack)
{
    if (!StackIsEmpty(stack))
    {
        int data = *(int*)StackPeek(stack);
        StackPop(stack);
        
        StackSort(stack);

        StackPushByOrder(stack, data);
    }
}

static void StackPushByOrder(stack_t *stack, int data)
{
    int larger_data = 0;
    if ((StackIsEmpty(stack)) || (data > *(int*)StackPeek(stack)))
    {
        StackPush(stack, &data);
        return;
    }

    larger_data = *(int*)StackPeek(stack);
    StackPop(stack);

    StackPushByOrder(stack, data);

    StackPush(stack, &larger_data);
}
