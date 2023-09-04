/************************************************ 
EXERCISE      : DS#11: Task
Implmented by : Snir Holland
Reviewed by   :  
Date          : 18/5/2023
File          : task_test.c
*************************************************/

#include <stdio.h>
#include <unistd.h>
#include "task.h"
#include "uid.h"

/* Test Functions */
static void TestCreate();
static void TestDestroy();
static void TestRun();
static void TestIsMatch();
static void TestUpdateTimeToRun();
static void TestGetTimeToRun();
static void TestGetUID();
static void TestIsBefore();

/* Operation Functions */
static int AddSix(void *param);
static int Square(void *param);

/* Cleanup Function */
static void Cleanup(void *param);

int main()
{
	TestCreate();
	
	TestRun();
	
	TestIsMatch();
	
	TestUpdateTimeToRun();
	
	TestGetTimeToRun();
	
	TestGetUID();
	
	TestIsBefore();
	
	TestDestroy();
		
	return(0);
}

/*-------------TestCreate-------------*/
static void TestCreate()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);
	
	printf("--------Testing Create()-----------\t");
	
	(NULL != task1 && NULL != task2) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

/*-------------TestDestroy-------------*/
static void TestDestroy()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);	
	
	/* Check will be done by valgrind */
	printf("--------Testing Destroy()-----------\t");
	printf("Success\n"); 
	
	TaskDestroy(task1);
	TaskDestroy(task2);	
}

/*-------------TestRun-------------*/
static void TestRun()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;

	int status1 = -1 , status2 = -1;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);		
	
	printf("--------Testing Run()-----------\t");
	
	status1 = TaskRun(task1);
	status2 = TaskRun(task2);
	
	(0 == status1 && 0 == status2) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

/*-------------TestIsMatch-------------*/
static void TestIsMatch()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	int is_match = 0;
	size_t test_count = 2;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);

	printf("--------Testing IsMatch()-----------\t");
	
	is_match = TaskIsMatch(TaskGetUID(task1), task1);
	(1 == is_match) ? --test_count : test_count;
	
	is_match = TaskIsMatch(TaskGetUID(task1), task2);
	(0 == is_match) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

/*-------------TestUpdateTimeToRun-------------*/
static void TestUpdateTimeToRun()
{
	task_t *task1 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	time_t diff = 0;
	time_t old_exec_time = 0;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	
	old_exec_time = TaskGetTimeToRun(task1);
	
	printf("--------Testing UpdateTimeToRun()---\t");
	
	TaskUpdateTimeToRun(task1);
	
	diff = TaskGetTimeToRun(task1) - old_exec_time;
	
	(20 == diff) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
}

/*-------------TestGetTimeToRun-------------*/
static void TestGetTimeToRun()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	time_t time1 = 0 , time2 = 0 , diff = 0;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);
	
	time1 = TaskGetTimeToRun(task1);
	time2 = TaskGetTimeToRun(task2);
	diff = time2 - time1;

	printf("--------Testing GetTimeToRun()---\t");
		
	(5 == diff) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

/*-------------TestGetUID-------------*/
static void TestGetUID()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	ilrd_uid_t uid1 = UIDBadUID;
	ilrd_uid_t uid2 = UIDBadUID;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);
	
	uid1 = TaskGetUID(task1);
	uid2 = TaskGetUID(task2);
	
	printf("--------Testing GetUID()---------\t");
	
	(!UIDIsSame(uid1, uid2)) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

/*-------------TestIsBefore-------------*/
static void TestIsBefore()
{
	task_t *task1 = NULL;
	task_t *task2 = NULL;
	
	void *clean_param = NULL;
	int param = 5;
	
	task1 = TaskCreate(10 , 20 , &AddSix , &param , clean_param , &Cleanup); 
	task2 = TaskCreate(15 , 30 , &Square , &param , clean_param , &Cleanup);
	
	printf("--------Testing IsBefore()---------\t");
	
	(TaskIsBefore(task1, task2)) ? printf("Success\n") : printf("Failure\n");
	
	TaskDestroy(task1);
	TaskDestroy(task2);
}

/*-------------End of testing functions-------------*/

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

static void Cleanup(void *param)
{
	(void)param;	
}


