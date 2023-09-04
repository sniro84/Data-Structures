/************************************************ 
EXERCISE <1>    : DS#4: Singly Linked List
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 29/4/2023
File          : LinkedList.c
*************************************************/


#include <stddef.h>  /* size_t */
#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */

#include "slist.h" 

typedef struct slist_node
{							
	void *data;
	struct slist_node *next;
} slist_node_t;

struct slist
{
	slist_node_t *head;
	slist_node_t *tail;
};

/* Action function which counts iterators */
static int Increment(void *, void *);

/*-----------------SListCreate-----------------*/
slist_t *SListCreate( void )
{
	slist_t *list = NULL;
	slist_node_t *dummy_node = NULL;
	
	list = (slist_t*)malloc(sizeof(slist_t));
	if (NULL == list)
	{
		return NULL;
	}
	
	dummy_node = (slist_node_t*)malloc(sizeof(slist_node_t));
	if (NULL == dummy_node)
	{
		free(list);
		return NULL;
	}
	
	list -> head = dummy_node;	
	list -> tail = dummy_node;

	dummy_node -> data = list;
	dummy_node -> next = NULL;
		
	return list;
}

/*-----------------SListDestroy-----------------*/
void SListDestroy(slist_t *list)
{
	slist_node_t *temp = NULL;	
	assert(list);
	
	while(NULL != list->head)
	{
		temp = list->head->next;
		free(list->head);
		list->head = temp;
	}
	
	free(list -> head); 
	free(list);
}

/*-----------------SListGetData-----------------*/
void *SListGetData(slist_iter_t iter)
{
	assert(iter);
	
	if (NULL == iter -> next)  
	{
		return NULL;
	}
	
	return (iter -> data);
}

/*-----------------SListSetData-----------------*/
void SListSetData(slist_iter_t iter, void *data)
{
	assert(iter);
	assert(iter -> next);
	
	iter -> data = data;
}

/*-----------------SListGetBegin-----------------*/
slist_iter_t SListGetBegin(const slist_t *list)
{
	assert(list);
	
	return (list -> head);
}

/*-----------------SListGetEnd-----------------*/
slist_iter_t SListGetEnd(const slist_t *list)
{
	assert(list);
	
	return (list -> tail);
}

/*-----------------SListNext-----------------*/
slist_iter_t SListNext(slist_iter_t iter)
{
	assert(iter);
	
	return (iter -> next);
} 

/*-----------------SListInsert-----------------*/
slist_iter_t SListInsert(slist_iter_t where, void *data)
{
	slist_node_t *new_node = NULL;
	
	assert(where);
	
	new_node = (slist_node_t*)malloc(sizeof(slist_node_t));
	if (NULL == new_node)
	{
		while(NULL != (where -> next))
		{
			where = where -> next;
		}
		return where;
	}
	
	new_node -> data = where -> data;
	new_node -> next = where -> next;
		
	where -> data = data;
	where -> next = new_node;
	
	/* update tail address if new node became the dummy */
	if (NULL == new_node -> next)
	{
		((slist_t *)new_node->data)->tail = new_node;
	} 
	
	return where;		
}

/*-----------------SListRemove-----------------*/
slist_iter_t SListRemove(slist_iter_t iter)
{
	slist_node_t *next_iter = NULL;
	
	assert(iter);
	assert(iter -> next);
	
	next_iter = iter -> next;
	
	iter -> data = next_iter -> data;
	iter -> next = next_iter -> next;
	
	free(next_iter);
	
	/* update tail address if iter became the dummy */
	if (NULL == iter->next)
	{
		((slist_t *)iter->data)->tail = iter;
	}
	
	return iter;	
	
}

/*-----------------SListForEach-----------------*/
int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param)
{
	int status = 0;	
	
	slist_iter_t runner = NULL;
	
	assert(from);
	assert(to);
	assert(action_func);
	
	runner = from;
	
	while (runner != to)
	{
		status = (*action_func)(runner -> data , param);
		if (1 == status)
		{
			break;
		}
		else
		{
			runner = runner -> next;		
		}
	}
	
	return status;
}

/*-----------------SListCount-----------------*/
size_t SListCount(const slist_t *list)
{
	size_t count = 0;

	assert(list);

	SListForEach(list -> head, list -> tail , &Increment, &count);

	return (count);
}

/*-----------------SListIsEqual-----------------*/
int SListIsEqual(slist_iter_t left_iter, slist_iter_t right_iter)
{
	assert(left_iter);
	assert(right_iter);
	
	return (left_iter == right_iter);	
}

/*-----------------SListFind-----------------*/
slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t match_func, void *param)
{	
	
	assert(from);
	assert(to);
	assert(match_func);
	
	while (from != to)
	{
		if (0 == match_func(from->data , param))
		{
			return from;
		}
		from = from->next;
	} 
	
	return from;
}

/*-----------------SListAppend-----------------*/
void SListAppend(slist_t *dest, slist_t *src)
{
	
	assert(src);
	assert(dest);
	
	/* connecting head of src to tail of dest */
	dest -> tail -> data = src -> head -> data;
	dest -> tail -> next = src -> head -> next;
	
	/* update tail of dest */
	dest -> tail = src -> tail;
	dest -> tail -> data = (void*)(dest->tail);
	
	/* update head and tail of source (both become dummy) */
	src -> tail = src -> head;
	src -> tail -> next = NULL;
	src -> head -> data = (void*)src;
}

/* Helper function to increment node count */
static int Increment(void *nothing , void *count_pnt)
{
	++(*(size_t*)count_pnt);
	(void)nothing;
	
	return (0);	
}

