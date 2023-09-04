/************************************************ 
EXERCISE      : DS#12: HeapScheduler
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona 
Date          : 20/6/23
File          : heap_scheduler.h
*************************************************/

#ifndef _HEAP_SCHEDULER_H__
#define _HEAP_SCHEDULER_H__

#include <stddef.h>
#include <time.h>

#include "uid.h"

typedef enum operation_status 
{
	OP_DONE,
	OP_CONTINUE,
	OP_ERROR
} op_status_t;

typedef enum sched_status
{
	SUCCESS,
	STOPPED, /* Returned by HeapSchedRun when stopped explicitly */
	FAILURE
} sched_status_t;

typedef struct scheduler sched_t;

/*
*	creates a new HeapScheduler
*
*	Arguments: None		
*
*	Return: a new HeapScheduler pointer if successful
*				otherwise return NULL.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
sched_t *HeapSchedCreate(void);

/*
*	frees all memory allocated for the HeapScheduler
*
*	Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*
*	Return: void.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
void HeapSchedDestroy(sched_t *sched);

/*
*	Add a Task to the HeapScheduler, sorted by priority.
	
*
*	Arguments:
*		delay - initial time to run the task in seconds.
*		interval - a cyclist value for rerun the task.
*		oper_func - pointer to operational function. Must be valid.
*		operation_func_param - The parameter that we wish to execute in operational function. Can be NULL.
*		clean_func - pointer to cleanup function. Must be valid.
*		clean_func_param - The parameter that we wish to execute in cleanup function. Can be NULL.

*	Return: UID - success,
*			NULL- failure.
*
*	Time complexity: O(1) best, O(n) - average/worst
*	Space complexity: O(1) best/average/worst
*/
ilrd_uid_t HeapSchedAdd(sched_t *sched,
			   size_t delay,
			   size_t interval_in_sec,
			   int (*oper_func)(void *param),
			   void *operation_func_params,
			   void *clean_func_params,
			   void (*clean_func)(void *param));


/*
*    Remove the match task of the given scheduale.
*
*    Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*		uid - Uniqe Identification of the task.
*
*	 Return: 0 - success,
*			1- failure.
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*/
int HeapSchedRemove(sched_t *sched, ilrd_uid_t uid);

/*
*    Start to execute the tasks.
*
*    Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*
*	 Return: 	
*		 	 0 - success
*			 1 - memory allocation error
*			 2 - function error
			 3 - stopped		
*			
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*/
int HeapSchedRun(sched_t *sched);

/*
*    Stop to execute tasks.
*
*    Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*			
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*/
void HeapSchedStop(sched_t *sched);

/*
*	Return the number of current tasks in the HeapScheduler.
*
*	Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*
*	Return: number of tasks in the HeapScheduler.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
size_t HeapSchedSize(const sched_t *sched);

/*
*	Clears HeapScheduler from tasks. HeapScheduler remains valid but empty.
*
*	Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*
*	Return: void.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
void HeapSchedClear(sched_t *sched);

/*
*	Checks if the HeapScheduler is empty
*
*	Arguments:
*		sched - a HeapScheduler pointer. must be a valid address.
*
*	Return: 1 - if the HeapScheduler is empty, 0 - otherwise
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*/
int HeapSchedIsEmpty(const sched_t *sched);


#endif   /* __SCHEDULER_H__ */


