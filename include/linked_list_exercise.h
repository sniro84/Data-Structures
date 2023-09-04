/************************************************ 
EXERCISE <1>    : DS#4: Singly Linked List
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 29/4/2023
File          : LinkedListExercise.h
*************************************************/

#ifndef __LINKED_LIST_EXERCISE_H__
#define __LINKED_LIST_EXERCISE_H__

#include <stddef.h> /* size_t */

typedef struct node
{
	void *data;
	struct node *next;
} node_t;

node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
node_t *FindIntersection(node_t *head_1 , node_t *head_2);


#endif /*__LINKED_LIST_EXERCISE_H__*/


