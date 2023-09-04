/************************************************ 
EXERCISE      : DS#12: Heap HeapScheduler
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona 
Date          : 20/6/23
File          : heap_scheduler_test.c
*************************************************/

#include <stdio.h>
#include <unistd.h>

#include "task.h"
#include "uid.h"
#include "heap_scheduler.h"
#include "heap_pq.h"

/* Test Functions */
static void TestCreate();
static void TestDestroy();
static void TestAdd();
static void TestRemove();
static void TestRun();
static void TestStop();
static void TestSize();
static void TestClear();
static void TestIsEmpty();

/* Operation Functions */
static int AddSix(void *param);
static int Square(void *param);
static int MultiplyByThree(void *param);
static int SubtractFive(void *param);
static int Stop(void *param);

/* Cleanup Function */
static void Cleanup(void *param);

int main()
{
	TestCreate();
	
	TestRun();
	
	TestAdd();
	
	TestRemove();
	
	TestSize();
	
	TestStop();
	
	TestIsEmpty();
	
	TestClear();
	
	TestDestroy();
		
	return(0);
}

/*-------------TestCreate-------------*/
static void TestCreate()
{
	sched_t *sched = HeapSchedCreate();
	
	printf("--------Testing Create()-----------\t");
	
	(NULL != sched) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}

/*-------------TestDestroy-------------*/
static void TestDestroy()
{
	sched_t *sched = HeapSchedCreate();
	HeapSchedDestroy(sched);
	
	/* Checks will be done through valgrind */
	printf("--------Testing Destroy()-----------\t");
	printf("Success\n");
}

/*-------------TestIsEmpty-------------*/
static void TestIsEmpty()
{
	sched_t *sched = HeapSchedCreate();
	
	printf("--------Testing IsEmpty()-----------\t");
	
	(HeapSchedIsEmpty(sched)) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}

/*-------------TestAdd-------------*/
static void TestAdd()
{
	sched_t *sched = HeapSchedCreate();
	
	void *clean_param = NULL;
	int param = 5;
	ilrd_uid_t uid = UIDBadUID;
	
	printf("--------Testing Add()-----------\t");

	uid = HeapSchedAdd(sched, 1 , 20 , &AddSix , &param , clean_param , &Cleanup);
	(!UIDIsSame(uid , UIDBadUID)) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}

/*-------------TestRun-------------*/
static void TestRun()
{
	sched_t *sched = HeapSchedCreate();
	
	sched_status_t status = -1;
	
	void *clean_param = NULL;
	int param = 5;
	
	printf("--------Testing Run()-----------\t");

	HeapSchedAdd(sched, 1 , 20 , &AddSix , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 2 , 30 , &Square , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 1 , 10 , &MultiplyByThree , &param , clean_param , &Cleanup); 
	HeapSchedAdd(sched, 2 , 15  ,&SubtractFive    , &param , clean_param , &Cleanup);
	
	status = HeapSchedRun(sched);
	
	(SUCCESS == status) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}


/*-------------TestRemove-------------*/
static void TestRemove()
{
	sched_t *sched = HeapSchedCreate();
	
	int remove_status = -1;
	
	void *clean_param = NULL;
	int param = 5;
	ilrd_uid_t uid = UIDBadUID;
	
	printf("--------Testing Remove()-----------\t");

	uid = HeapSchedAdd(sched, 1 , 20 , &AddSix , &param , clean_param , &Cleanup);
	remove_status = HeapSchedRemove(sched , uid);
	
	(SUCCESS == remove_status) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
	
	return;
}

/*-------------TestSize-------------*/
static void TestSize()
{
	sched_t *sched = HeapSchedCreate();
	
	void *clean_param = NULL;
	int param = 5;
	
	printf("--------Testing Size()-----------\t");

	HeapSchedAdd(sched, 1 , 20 , &AddSix , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 2 , 30 , &Square , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 3 , 10 , &MultiplyByThree , &param , clean_param , &Cleanup); 
	HeapSchedAdd(sched, 4 , 5  , &SubtractFive    , &param , clean_param , &Cleanup);
	
	(4 == HeapSchedSize(sched)) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}

/*-------------TestStop-------------*/
static void TestStop()
{
	sched_t *sched = HeapSchedCreate();
	
	sched_status_t status = -1;
	
	void *clean_param = NULL;
	int param = 5;
	
	printf("--------Testing Stop()-----------\t");

	HeapSchedAdd(sched, 1 , 20 , &AddSix , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 2 , 30 , &Square , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 1 , 10 , &MultiplyByThree , &param , clean_param , &Cleanup); 
	HeapSchedAdd(sched, 2 , 4  , &Stop    , sched , clean_param , &Cleanup);
	HeapSchedAdd(sched, 1 , 15  ,&SubtractFive    , &param , clean_param , &Cleanup);
	
	status = HeapSchedRun(sched);
	
	(STOPPED == status) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}


/*-------------TestClear-------------*/
static void TestClear()
{
	sched_t *sched = HeapSchedCreate();
	
	void *clean_param = NULL;
	int param = 5;
	
	printf("--------Testing Clear()-----------\t");

	HeapSchedAdd(sched, 1 , 20 , &AddSix , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 2 , 30 , &Square , &param , clean_param , &Cleanup);
	HeapSchedAdd(sched, 3 , 10 , &MultiplyByThree , &param , clean_param , &Cleanup); 
	HeapSchedAdd(sched, 4 , 15 , &SubtractFive    , &param , clean_param , &Cleanup);
	
	HeapSchedClear(sched);
	
	(HeapSchedIsEmpty(sched)) ? printf("Success\n") : printf("Failure\n");
	
	HeapSchedDestroy(sched);
}
/*-------------End of testing functions-------------*/

/*-------------Tasks-------------*/
static int AddSix(void *param)
{
	*(int*)param += 6;
	return (0);
}

static int Square(void *param)
{
	(*(int*)param) *= (*(int*)param); 	
	return (0);
}

static int SubtractFive(void *param)
{
	*(int*)param -= 5;	
	return (0);
}

static int MultiplyByThree(void *param)
{
	*(int*)param *= 3;	
	return (0);
}

static int Stop(void *param)
{
	HeapSchedStop((sched_t *)param);
	return (0);
}

/*-------------Cleanup-------------*/
static void Cleanup(void *param)
{
	(void)param;	
}


