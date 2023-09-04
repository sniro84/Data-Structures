/************************************************ 
EXERCISE      : Linked List Exercises
Implmented by : Snir Holland
Reviewed by   :
Date          : 1/5/2023
File          : LinkedListExercise.c
*************************************************/

#include "linked_list_exercise.h" 

#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */

/* This function reverses the order of a given slist */
node_t *Flip(node_t *head)
{
	node_t *prev = NULL;
	node_t *curr = NULL;
	node_t *next = NULL;

	assert(head);
	
	curr = head;	
	
	while (NULL != curr)
	{
		next = curr -> next;
		curr -> next = prev;
		prev = curr;
		curr = next;		
	}
	head = prev;
	
	return head;
}

/* This function tells whether a given slist has loop */
int HasLoop(const node_t *head) 
{
	const node_t *runner1 = NULL;
	const node_t *runner2 = NULL;
	
	int found_loop = 0;
	
	assert(head);
	
	runner1 = head;
	runner2 = head;
		
	while ( (NULL != runner1) && (NULL != runner2) && (NULL != runner2 -> next) )
	{
		runner1 = runner1 -> next;
		runner2 = runner2 -> next -> next;
		
		if (runner1 == runner2)
		{
			found_loop = 1;
			break;
		}
	}
	
	return found_loop;
}

node_t *FindIntersection(node_t *head_1 , node_t *head_2)
{
	node_t *runner1 = NULL;
	node_t *runner2 = NULL;
	size_t counter1 = 0 , counter2 = 0;
	int diff = 0;
	
	assert(head_1);
	assert(head_2);
	
	runner1 = head_1;
	runner2 = head_2;
	
	while(NULL != runner1 -> next   &&   NULL != runner2 -> next)
	{
		++counter1;
		++counter2;
		runner1 = runner1 -> next;
		runner2 = runner2 -> next;
	}
	
	if (runner1 != runner2)
	{
		return NULL;
	}
	
	diff = counter1 - counter2;
	if (diff > 0)
	{
		runner1 = head_1;
		runner2 = head_2;
	}
	else
	{
		runner1 = head_2;
		runner2 = head_1;
		diff *= (-1);
	}
	
	/* now runner1 points to the larger list */
	
	while(diff > 0)
	{
		runner1 = runner1 -> next;
		--diff;
	}
		
	while(runner1 != runner2)
	{
		runner1 = runner1 -> next;
		runner2 = runner2 -> next;
	}
	
	return runner1;
}




