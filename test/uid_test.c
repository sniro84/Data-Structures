/************************************************ 
EXERCISE      : DS#9: ILRD_UID
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 16/5/2023
File          : uid_test.c
*************************************************/

#include "uid.h"
#include <stdio.h>

static void PrintUID(ilrd_uid_t uid);

int main()
{
	size_t test_count = 8;	
	
	ilrd_uid_t my_uid1 = UIDCreate();
	ilrd_uid_t my_uid2 = UIDCreate();
	
	(0 == my_uid1.counter) ? --test_count : test_count;
	(0 != my_uid1.time) ? --test_count : test_count;
	(0 != my_uid1.pid) ? --test_count : test_count;
	(NULL != my_uid1.ip) ? --test_count : test_count;
	
	(1 == my_uid2.counter) ? --test_count : test_count;
	(0 != my_uid2.time) ? --test_count : test_count;
	(0 != my_uid2.pid) ? --test_count : test_count;
	(NULL != my_uid2.ip) ? --test_count : test_count;
	
	printf("Testing UIDCreate():\t");
	(0 == test_count) ? printf("Success") : printf("Failure");
	
	printf("\n");
	
	printf("Testing UIDIsSame():\t");
	(!UIDIsSame(my_uid1 ,my_uid2)) ? printf("Success") : printf("Failure");
	
	printf("\n");
	
	(void)PrintUID;
	
	return (0);
	
}

static void PrintUID(ilrd_uid_t uid)
{
	printf("Counter : %lu\t" , uid.counter);
	printf("Time    : %lu\t" , (size_t)uid.time);
	printf("Process ID : %lu\t" , uid.pid);
	printf("IP : %s\n" , uid.ip);
}
