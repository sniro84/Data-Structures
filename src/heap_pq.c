/************************************************ 
EXERCISE      : DS#10: Priority Queue
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona 
Date          : 20/6/23
File          : heap_pq.c
*************************************************/

#include <assert.h>
#include <stdlib.h>

#include "heap.h"
#include "heap_pq.h"

enum status {SUCCESS = 0 , FAILURE = 1};

struct priority_queue 
{
	heap_t *heap_pq;
};


pq_t *HeapPQCreate(pq_compare_t cmp)
{	
	pq_t *pq = NULL;
	
	assert(NULL != cmp);
	
	pq = (pq_t *)malloc(sizeof(pq_t));
	if (NULL == pq)
	{
		return NULL;
	}
	
	pq->heap_pq = HeapCreate(cmp);
	if (NULL == pq->heap_pq)
	{
		free(pq);
		return NULL;
	}
	
	return pq; 
}

void HeapPQDestroy(pq_t *pq)
{
	assert(NULL != pq);
		
	HeapDestroy(pq->heap_pq);
	free(pq);
}

int HeapPQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	return (SUCCESS == HeapPush(pq->heap_pq , data)) ? SUCCESS : FAILURE;
}

void *HeapPQDequeue(pq_t *pq)
{
	void *data = NULL;

	assert(NULL != pq);
	
	if (!HeapPQIsEmpty(pq))
	{
		data = HeapPQPeek(pq);
		HeapPop(pq->heap_pq);
	}
	
	return data;
}

void *HeapPQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapPeek(pq->heap_pq);
}


int HeapPQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapIsEmpty(pq->heap_pq);
}

size_t HeapPQGetSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return HeapSize(pq->heap_pq);
}


void HeapPQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!HeapIsEmpty(pq->heap_pq))
	{
		HeapPop(pq->heap_pq);
	}
}

void *HeapPQErase(pq_t *pq, pq_is_match_t func, void *param)
{		
	assert(NULL != pq);
	assert(NULL != func);
	assert(NULL != param);
	
	return HeapRemove(pq->heap_pq, func, param);
}

