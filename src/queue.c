/************************************************ 
EXERCISE <1>    : DS#5: Queue
Implmented by : Snir Holland
Reviewed by   : <REVIEWER>
Date          : 25/4/2023
File          : Queue.c
*************************************************/

#include "queue.h" 

#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */

struct queue
{
	slist_t *queue;
};

queue_t *QCreate(void)
{
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
	if (NULL == queue)
	{
		return NULL;
	}
	
	queue -> queue = SListCreate();
	
	return queue;
}

void QDestroy(queue_t *queue)
{
	SListDestroy(queue->queue);
	free(queue);
}

int QEnqueue(queue_t *queue, void *data)
{	
	slist_iter_t rear = NULL;
	
	assert(queue);
	
	rear = SListGetEnd(queue -> queue);
	
	if (NULL == SListInsert(rear , data))
	{
		return (1);
	}
	
	return (0);
}

void QDequeue(queue_t *queue)
{
	slist_iter_t front = NULL;
	
	assert(queue);
	
	front = SListGetBegin(queue -> queue);
	
	SListRemove(front); 
}

void *QPeek(const queue_t *queue)
{
	slist_iter_t front = NULL;
	
	assert(queue);
	
	front = SListGetBegin(queue -> queue);
	
	return (SListGetData(front)); 
}

int QIsEmpty(const queue_t *queue)
{
	slist_iter_t front = NULL;

	assert(queue);
	
	front = SListGetBegin(queue -> queue);
	
	return (NULL == SListNext(front));
}

size_t QGetSize(const queue_t *queue)
{
	assert(queue);
	
	return SListCount(queue -> queue);
	
}

void QAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);
	
	SListAppend(dest -> queue, src -> queue);
}


