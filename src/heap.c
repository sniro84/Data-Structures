/************************************************ 
EXERCISE      : Heap
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 20/6/23
File          : heap.c
*************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <stdio.h>  /* stderr */
#include <string.h> /* memcpy */

#include "dvector.h"
#include "heap.h"

enum status {SUCCESS = 0 , FAILURE = 1};

struct heap
{
    d_vector_t *heap_vector;
    heap_cmp_func_t cmp;
};

static void HeapifyUp(heap_t *heap, int index);
static void HeapifyDown(heap_t *heap, int index, int last_index);
static void GenericSwap(void *p1, void *p2, size_t nbytes);

/* ------------- HeapCreate ------------- */
heap_t *HeapCreate(heap_cmp_func_t cmp)
{
    heap_t *heap = NULL;

    assert(NULL != cmp);

    heap = (heap_t*)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }

    heap->cmp = cmp;
    heap->heap_vector = DVectorCreate(1, sizeof(void*));
    if (NULL == heap->heap_vector)
    {
        free(heap);
        heap = NULL;

        return NULL;
    }

    return heap;
}

/* ------------- HeapDestroy ------------- */
void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    DVectorDestroy(heap->heap_vector);

    free(heap);
    heap = NULL;
}

/* ------------- HeapIsEmpty ------------- */
int HeapIsEmpty(heap_t *heap)
{
    assert(NULL != heap);

    return (0 == DVectorGetSize(heap->heap_vector));
}

/* ------------- HeapSize ------------- */
size_t HeapSize(heap_t *heap)
{
    assert(NULL != heap);

    return DVectorGetSize(heap->heap_vector);
}

/* ------------- HeapPeek ------------- */
void *HeapPeek(heap_t *heap)
{
    assert(NULL != heap);

    return *(void**)DVectorGetAccess(heap->heap_vector, 0);
}

/* ------------- HeapPush ------------- */
int HeapPush(heap_t *heap, void *data)
{
    assert(NULL != heap);

    if (FAILURE == DVectorPushBack(heap->heap_vector, &data))
    {
        return FAILURE;
    }

    HeapifyUp(heap, DVectorGetSize(heap->heap_vector) - 1);

    return SUCCESS;
}

/* ------------- HeapPop ------------- */
void HeapPop(heap_t *heap)
{
    size_t first_index = 0;
    size_t last_index = 0;

    void **first_data = NULL; 
    void **last_data = NULL;

    assert(NULL != heap);

    first_data = DVectorGetAccess(heap->heap_vector, first_index);

    last_index = DVectorGetSize(heap->heap_vector) - 1;
    last_data = DVectorGetAccess(heap->heap_vector, last_index);

    GenericSwap(first_data, last_data, sizeof(void*));

    DVectorPopBack(heap->heap_vector);
    --last_index;

    HeapifyDown(heap, first_index, last_index);
}

/* ------------- HeapRemove ------------- */
void *HeapRemove(heap_t *heap, int (*is_match)(const void *data, const void *param), const void *param)
{
    size_t i =0;
    size_t last_index = DVectorGetSize(heap->heap_vector) - 1;

    void **data_to_remove = NULL;
   
    assert(NULL != heap);
    assert(NULL != is_match);
    assert(NULL != param);

    for(i=0; i<=last_index; ++i)
    {
        void **result = DVectorGetAccess(heap->heap_vector, i);
        if (is_match(*result, param))
        {
            void *temp = NULL;
            void **last_data = DVectorGetAccess(heap->heap_vector, last_index);

            data_to_remove = result;
            temp = *data_to_remove;

            GenericSwap(result, last_data, sizeof(void*));

            DVectorPopBack(heap->heap_vector);
            --last_index;

            HeapifyDown(heap, i, last_index);
            HeapifyUp(heap, i);

            data_to_remove = &temp;
            return *data_to_remove;
        }
    }

    return NULL;
}

/* ------------- End of functions ------------- */

/* ------------- Static functions ------------- */

/* Helper Function: fix heap by sending the data down the tree */
static void HeapifyDown(heap_t *heap, int index, int last_index)
{
    void **curr_data = NULL;
    void **left_child_data = NULL;
    void **right_child_data = NULL;

    assert(NULL != heap);
    assert(index >= 0);

    /* has left child */
    while(index * 2 + 1 <= last_index)
    {
        curr_data = DVectorGetAccess(heap->heap_vector ,index);
        left_child_data = DVectorGetAccess(heap->heap_vector ,index * 2 + 1);

        /* has right child */
        if (index * 2 + 2 <= last_index)
        {
            void **smaller_data = NULL;
            int result = 0;

            right_child_data = DVectorGetAccess(heap->heap_vector ,index * 2 + 2);

            /* current data is smaller than both of his children --> were finished */
            if (heap->cmp(*curr_data ,*left_child_data) < 0 && heap->cmp(*curr_data ,*right_child_data) < 0)
            {
                break;
            }

            result = heap->cmp(*left_child_data ,*right_child_data);

            if (result < 0)
            {
                smaller_data = left_child_data;
                index = index * 2 + 1;
            }
            else
            {
                smaller_data = right_child_data;
                index = index * 2 + 2;
            }

            GenericSwap(curr_data, smaller_data, sizeof(void*));
        }

        /* has only left child */
        else
        {
            if (heap->cmp(*curr_data ,*left_child_data) < 0) 
            {
                break;
            }

            GenericSwap(curr_data, left_child_data, sizeof(void*));
            index = index * 2 + 1;
        }        
    }
}

/* Helper Function: fix heap by sending the data up the tree */
static void HeapifyUp(heap_t *heap, int index)
{
    int parent_index = (index - 1) / 2;

    void **parent_data = NULL;
    void **curr_data = NULL;

    assert(NULL != heap);
    assert(index >= 0);

    while (index > 0)
    {
        curr_data = DVectorGetAccess(heap->heap_vector ,index);
        parent_data = DVectorGetAccess(heap->heap_vector, parent_index);

        if (heap->cmp(*curr_data, *parent_data) > 0)
        {
            break;
        }

        GenericSwap(parent_data, curr_data, sizeof(void*));

        index = parent_index;
        parent_index = (parent_index - 1) / 2;
    }
}

/* Helper Function: swap values of any type */
static void GenericSwap(void *p1, void *p2, size_t nbytes)
{
    void *buf = NULL;

    assert(NULL != p1);
    assert(NULL != p2);

    buf = malloc(nbytes);
    if (NULL == buf)
    {
        fprintf(stderr,"Memory allocation failed.\n");
        return;
    }

    memcpy(buf, p1, nbytes);
    memcpy(p1,  p2, nbytes);
    memcpy(p2, buf, nbytes);

    free(buf);
    buf = NULL;
}


