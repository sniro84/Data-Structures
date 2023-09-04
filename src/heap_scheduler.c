/************************************************ 
EXERCISE      : DS#12: Heap HeapScheduler
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona 
Date          : 20/6/23
File          : heap_scheduler.c
*************************************************/

#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <unistd.h> /* sleep */

#include "heap_scheduler.h"
#include "heap_pq.h"
#include "uid.h"
#include "task.h"

struct scheduler
{
	pq_t *pq;
	int to_stop; 
	task_t *current_task;
	int to_remove_current;
};

enum boolean_status {FALSE = 0 , TRUE = 1};

/*--------------- Compare Function--------------------*/
static int TaskCmp(const void *task1, const void *task2);

/*--------------- Match Function--------------------*/
static int IsMatch(const void *task, const void *uid);

/*---------------HeapSchedCreate--------------------*/
sched_t *HeapSchedCreate(void)
{
	sched_t *scheduler = (sched_t *)malloc(sizeof(sched_t));
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->pq = HeapPQCreate(&TaskCmp);
	if (NULL == scheduler->pq)
	{
		free(scheduler);
		scheduler = NULL;
		
		return NULL;
	}
	
	scheduler->to_stop = FALSE;
	scheduler->current_task = NULL;
	scheduler->to_remove_current = FALSE;
	
	return scheduler; 
	
}

/*---------------HeapSchedDestroy--------------------*/
void HeapSchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	HeapSchedClear(sched);
	
	HeapPQDestroy(sched->pq);
	free(sched);
	sched = NULL;
}

/*---------------HeapSchedAdd--------------------*/
ilrd_uid_t HeapSchedAdd(sched_t *sched,
			   size_t delay,
			   size_t interval_in_sec,
			   int (*oper_func)(void *param),
			   void *operation_func_params,
			   void *clean_func_params,
			   void (*clean_func)(void *param))
{
	task_t *task = NULL;
	
	assert(NULL != sched);
	assert(NULL != oper_func);
	assert(NULL != clean_func);
	
	task = TaskCreate(delay, interval_in_sec, oper_func, operation_func_params, clean_func_params, clean_func);
	
	if (NULL == task)
	{
		return UIDBadUID;
	}
	
	if (SUCCESS != HeapPQEnqueue(sched->pq , task))
	{
		TaskDestroy(task);
		return UIDBadUID;
	}
	
	return TaskGetUID(task);
}

/*---------------HeapSchedRemove--------------------*/
int HeapSchedRemove(sched_t *sched, ilrd_uid_t uid)
{	
	task_t *task_to_remove = NULL;
	
	assert(NULL != sched);
	assert(!UIDIsSame(uid , UIDBadUID));
	
	/* a task is found inside the schedule queue */
	task_to_remove = HeapPQErase(sched->pq , &IsMatch , &uid);
	if (NULL != task_to_remove)
	{
		TaskDestroy(task_to_remove);
		return SUCCESS;	
	}
	
	/* the current task (outside of queue) is the one to be removed */
	if (NULL != sched->current_task  &&  TaskIsMatch(uid , sched->current_task))
	{
		sched->to_remove_current = TRUE;
		return SUCCESS;
	}
	
	/* task not found */	
	return FAILURE;
}

/*---------------HeapSchedRun--------------------*/
int HeapSchedRun(sched_t *sched)
{
	int op_status = SUCCESS;
	
	time_t time_diff = 0;
	
	sched->to_stop = FALSE; 

	assert(NULL != sched);
	
	while ((FALSE == sched->to_stop) && (!HeapPQIsEmpty(sched->pq))) 
	{
		time_t curr_time = 0; 

		sched->current_task = (task_t *)HeapPQDequeue(sched->pq);
		
		curr_time = TaskGetTimeToRun(sched->current_task);
				 
		while (curr_time < time(NULL))
		{	
			time_diff = curr_time - time(NULL);	
			sleep(time_diff);
		}
		
		op_status = TaskRun(sched->current_task);
		
		if (OP_DONE == op_status || OP_ERROR == op_status)
		{
			TaskDestroy(sched->current_task);
			sched->current_task = NULL; 
		}
		else     /* op_status == OP_CONTINUE */
		{
			TaskUpdateTimeToRun(sched->current_task);
			
			if (TRUE == sched->to_remove_current)
			{
				TaskDestroy(sched->current_task);
				sched->current_task = NULL;
				sched->to_remove_current = FALSE;
			}
								
			if (SUCCESS != HeapPQEnqueue(sched->pq, sched->current_task))
			{
				TaskDestroy(sched->current_task);
				sched->current_task = NULL;
				
				return FAILURE;
			}
		}	
	} /* end of while */
	
	return sched->to_stop; 	
}

/*---------------HeapSchedStop--------------------*/
void HeapSchedStop(sched_t *sched)
{
	assert(NULL != sched);
	
	sched->to_stop = TRUE;	
}

size_t HeapSchedSize(const sched_t *sched)
{
	assert(NULL != sched);
	
	if (NULL == sched->current_task)
	{
		return HeapPQGetSize(sched->pq);
	}
	return HeapPQGetSize(sched->pq) + 1;
}

void HeapSchedClear(sched_t *sched)
{
	void *task_to_destroy = NULL;

	assert(NULL != sched);
		
	while (!HeapPQIsEmpty(sched->pq))
	{
		task_to_destroy = HeapPQDequeue(sched->pq); 
		TaskDestroy((task_t *)task_to_destroy);
	}
	
	if (NULL != sched->current_task)
	{
		sched->to_remove_current = TRUE;
	}
}

/*---------------HeapSchedIsEmpty--------------------*/
int HeapSchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return ((HeapPQIsEmpty(sched->pq)) && (NULL == sched->current_task));
}


/*--------------- Compare Function--------------------*/
static int TaskCmp(const void *task1, const void *task2)
{
	assert(NULL != task1);
	assert(NULL != task2);
	
	return TaskGetTimeToRun((task_t*)task1) - TaskGetTimeToRun((task_t*)task2);
}

/*--------------- Match Function--------------------*/
static int IsMatch(const void *task, const void *uid)
{
	assert(NULL != task);
	assert(NULL != uid);
	
	return TaskIsMatch(*(ilrd_uid_t *)uid , (const task_t *)task);
}

