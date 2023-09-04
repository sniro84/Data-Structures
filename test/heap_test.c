/************************************************ 
EXERCISE      : Heap
Implmented by : Snir Holland
Reviewed by   : 
Date          : 18/6/23
File          : heap_test.c
*************************************************/
#include <stdio.h> /* printf */

#include "heap.h"

static void TestHeapCreate();
static void TestHeapDestroy();
static void TestHeapIsEmpty();
static void TestHeapSize();
static void TestHeapPeek();
static void TestHeapPush();
static void TestHeapPop();
static void TestHeapRemove();

static int IntCmp(const void *value1, const void *value2);
static int IsEqualInt(const void *data, const void *param);

int main(void)
{
    TestHeapCreate();

    TestHeapDestroy();

    TestHeapPush();

    TestHeapPop();

    TestHeapRemove();

    TestHeapIsEmpty();

    TestHeapPeek();

    TestHeapSize();

    return (0);
}

/* ------------- TestHeapCreate() ------------- */
static void TestHeapCreate()
{
    heap_t *heap = NULL;
    
    heap = HeapCreate(&IntCmp);

    printf("--------Testing HeapCreate()--------\t");

    (NULL != heap) ? printf("Success\n") : printf("Failure\n");

    HeapDestroy(heap);
}

/* ------------- TestHeapDestroy() ------------- */
static void TestHeapDestroy()
{
    heap_t *heap = NULL;
    
    heap = HeapCreate(&IntCmp);

    printf("--------Testing HeapDestroy()--------\t");

    printf("Success\n");

    /* checks will be done through valgrind */
    HeapDestroy(heap);
}

/* ------------- TestHeapPush() ------------- */
static void TestHeapPush()
{
    heap_t *heap = NULL;

    size_t test_count = 6;

    size_t i =0; 

    int numbers[6] = {8,6,5,1,20,11};
    
    heap = HeapCreate(&IntCmp);

    for(i=0; i<6; ++i)
    {
        if (0 == HeapPush(heap, &numbers[i]))
        {
            --test_count;
        }
    }

    printf("--------Testing HeapPush()--------\t");

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

    HeapDestroy(heap);
}

/* ------------- TestHeapPop() ------------- */
static void TestHeapPop()
{
    heap_t *heap = NULL;

    size_t test_count = 1;

    size_t i =0; 

    int numbers[6] = {8,6,5,1,20,11};
    
    heap = HeapCreate(&IntCmp);

    for(i=0; i<6; ++i)
    {
        if (0 == HeapPush(heap, &numbers[i]))
        {
            --test_count;
        }
    }

    printf("--------Testing HeapPop()--------\t");

    for(i=0; i<5; ++i)
    {
        HeapPop(heap);
    }

    (1 == HeapSize(heap)) ? printf("Success\n") : printf("Failure\n");

    HeapDestroy(heap);
}

/* ------------- TestHeapRemove() ------------- */
static void TestHeapRemove()
{
    heap_t *heap = NULL;

    size_t test_count = 2;

    size_t i =0;

    void *data_to_remove = NULL; 

    int numbers[6] = {8,6,5,1,20,11};
    
    heap = HeapCreate(&IntCmp);

    for(i=0; i<6; ++i)
    {
        HeapPush(heap, &numbers[i]);
    }

    printf("--------Testing HeapRemove()--------\t");

    data_to_remove = HeapRemove(heap, &IsEqualInt, &numbers[1]);

    (5 == HeapSize(heap)) ? --test_count : test_count;
    (*(int*)data_to_remove == 6) ? --test_count : test_count;

    (0 == test_count) ? printf("Success\n") : printf("Failure\n"); 

    HeapDestroy(heap);
}

/* ------------- TestHeapIsEmpty() ------------- */
static void TestHeapIsEmpty()
{
    heap_t *heap = NULL;

    size_t test_count = 2;

    size_t i =0; 

    int numbers[6] = {8,6,5,1,20,11};
    
    heap = HeapCreate(&IntCmp);

    (HeapIsEmpty(heap)) ? --test_count : test_count;

    for(i=0; i<6; ++i)
    {
        HeapPush(heap, &numbers[i]);
    }

    (!HeapIsEmpty(heap)) ? --test_count : test_count;

    printf("--------Testing HeapIsEmpty()--------\t");

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

    HeapDestroy(heap);    
}

/* ------------- TestHeapSize() ------------- */
static void TestHeapSize()
{
    heap_t *heap = NULL;

    size_t test_count = 2;

    size_t i =0; 

    int numbers[6] = {8,6,5,1,20,11};
    
    heap = HeapCreate(&IntCmp);

    (HeapIsEmpty(heap)) ? --test_count : test_count;

    for(i=0; i<6; ++i)
    {
        HeapPush(heap, &numbers[i]);
    }

    (!HeapIsEmpty(heap)) ? --test_count : test_count;

    printf("--------Testing HeapSize()--------\t");

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

    HeapDestroy(heap);  
}

/* ------------- TestHeapPeek() ------------- */
static void TestHeapPeek()
{
    heap_t *heap = NULL;

    size_t test_count = 1;

    size_t i =0; 

    int numbers[6] = {8,6,5,1,20,11};
    
    heap = HeapCreate(&IntCmp);

    for(i=0; i<6; ++i)
    {
        HeapPush(heap, &numbers[i]);
    }

    (1 == *(int*)HeapPeek(heap)) ? --test_count : test_count;

    printf("--------Testing HeapPeek()--------\t");

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

    HeapDestroy(heap);  
}

/* -------------- End of test functions -------------*/

static int IntCmp(const void *value1, const void *value2)
{
	return *(int*)value1 - *(int*)value2;
}

static int IsEqualInt(const void *data, const void *param)
{
    return ( *(int*)data == *(int*)param );
}
