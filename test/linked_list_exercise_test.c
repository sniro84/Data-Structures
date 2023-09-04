/************************************************ 
EXERCISE      : Linked List Exercises
Implmented by : Snir Holland
Reviewed by   :
Date          : 1/5/2023
File          : LinkedListExercise_Test.c
*************************************************/

#include "linked_list_exercise.h" 
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */

static node_t *PushNode(node_t **head_pnt , int *data);
static void DestroyList(node_t *head);
static void PrintList(node_t *head);

int main()
{
	node_t *head1 = NULL;
	
	node_t *head2 = NULL;
	
	node_t *intersection = NULL;
	
	int x = 1000;
	int y = 2000;
	int z = 3000;
	
	int numbers[6] = {3,6,1,8,9,10};
	
	size_t i = 0;
	
	/* creating the first list */
	for(i = 0; i < 6; ++i)
	{
		PushNode(&head1 , &numbers[i]);
	}
	
	/* creating the second list */		
	PushNode(&head2 , &x);
	PushNode(&head2->next , &y);
	PushNode(&head2->next->next , &z);
	head2->next->next->next = head1->next->next->next;

	printf("\nList BEFORE flipping : \n");
	PrintList(head1);
	
	head1 = Flip(head1);
	
	printf("\nList AFTER flipping : \n");
	PrintList(head1);
	
	printf("\nDoes current list have a loop ? : ");
	(HasLoop(head1)) ? printf("Yes!\n") : printf("No...\n");
	
	/* Loop */
	head1 -> next -> next -> next -> next -> next -> next = head1;
	printf("\nCreated a loop inside the list... \n");
	
	printf("\nDoes current list have a loop ? : ");
	(HasLoop(head1)) ? printf("Yes!\n") : printf("No...\n");
	
	/* Unloop*/
	head1 -> next -> next -> next -> next -> next -> next = NULL;
	head1 = Flip(head1);
	printf("\nrevert back to original list (no loop)... \n");
	
	printf("List 1:\n");	
	PrintList(head1);
	
	printf("List 2:\n");
	PrintList(head2);
	
	intersection = FindIntersection(head1 , head2);
	printf("\nDo the lists have a common node ? : ");
	(NULL != intersection) ? printf("Yes!\n") : printf("No...\n");
	(NULL != intersection) ? printf("Value :  %d\n" , *(int*)(intersection->data)) : printf("Bummer...\n");
	
	head1 -> next -> next -> next = NULL;

	DestroyList(head1);	
	DestroyList(head2);
	
	return (0);
	
}

static node_t *PushNode(node_t **head_pnt , int *data)
{	
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node -> data = data;
	new_node -> next = *head_pnt;
	
	*head_pnt = new_node;
	
	return *head_pnt;
}

static void DestroyList(node_t *head)
{
	node_t *prev = NULL;
	node_t *runner = head;
	while (NULL != runner)
	{
		prev = runner;
		runner = runner -> next;
		free(prev);
	}
}

static void PrintList(node_t *head)
{
	node_t *runner = head;
	while (NULL != runner)
	{
		printf("%d --> " , *(int*)(runner -> data));
		runner = runner -> next;
	}
	printf("NULL\n");
}


