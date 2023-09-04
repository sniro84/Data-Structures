/************************************************ 
EXERCISE <1>    : DS#4: Singly Linked List
Implmented by : Snir Holland
Reviewed by   : Yehuda Tarona
Date          : 29/4/2023
File          : LinkedList.h
*************************************************/

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct slist_node *slist_iter_t;
typedef struct slist slist_t;

/*
*	compare function between data and param.
*
*	Arguments:
*		data - the data to do compare.
*		param - the param to do compare.
*
*	Return: integer less than, equal to, or greater than zero if data is found, respectively, to be less than, to match, or be greater than param.
*
*/
typedef int (*match_func_t)(void *data, void *param);


/*
*	do action to data.
*
*	Arguments:
*		data - the data to do action.
*		param - the param to do action to data.
*
*	Return: 0 if succeed, otherwise 1.
*/
typedef int (*action_func_t)(void *data, void *param);

/*
*
*	creates a new Singly Linked List
*
*	Arguments:
*		void.
*
*	Return: a new Singly Linked List if successful
*				otherwise return NULL.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
slist_t *SListCreate(void);

/*
*
*	frees all memory allocated for the Singly Linked List
*
*	Arguments:
*		list - Singly Linked List to destroy. must be a valid address.
*
*	Return: Allwayes succeed.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
void SListDestroy(slist_t *list);

/*
*
*	insert a data to the list, before the iterator where. in case of failure 
*	the list remain unchanged.
*	causes iterator invalidation.
*
*	Arguments:
*		where - iterator to insert date before.
*		data - The data that we wish to insert to the list.
*
*	Return: the new iterator that created if successful or end upon fail
*
*	Time complexity: O(1) best/average O(n) worst
*	Space complexity: O(1) best/average/worst
*
*/
slist_iter_t SListInsert(slist_iter_t where, void *data);

/*
*
*	get the next iterator.
*
*	Arguments:
*		iter - current iterator. must be a valid iterator.
*
*	Return: the next valid iterator or end if it is the last iterator.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
slist_iter_t SListNext(slist_iter_t iter); 

/*
*
*	remove data from the list.
*	causes iterator invalidation.
*	
*	Arguments:
*		iter - iterator to remove from list. must be a valid iterator.
*
*	Return: the next iterator or end if it is the last valid iterator.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
slist_iter_t SListRemove(slist_iter_t iter);

/*
*
*	get data from iterator.
*
*	Arguments:
*		iter - iterator to get data from. must be a valid iterator.
*
*	Return: the data in iterator on NULL if it is invalid iterator.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
void *SListGetData(slist_iter_t iter);

/*
*
*	set data to iterator.
*
*	Arguments:
*		iter - iterator to set data. must be a valid iterator.
*		data - The data that we wish to set to the iterator.
*
*	Return: Allways succeed.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
void SListSetData(slist_iter_t iter, void *data);

/*
*
*	count the number of data that is stored in the list.
*
*	Arguments:
*		list - Singly Linked List that count data from. must be a valid list.
*
*	Return: how much data stored in list.
*
*	Time complexity: O(n) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
size_t SListCount(const slist_t *list);

/*
*	get the first iterator in the list.
*
*	Arguments:
*		list - Singly Linked List. must be a valid list.
*
*	Return: the first iterator or end if the list is empty.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
slist_iter_t SListGetBegin(const slist_t *list);

/*
*	get the last iterator in the list.
*
*	Arguments:
*		list - Singly Linked List. must be a valid list.
*
*	Return: the end in list, NOTICE: the last iterator is invalid iterator.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
slist_iter_t SListGetEnd(const slist_t *list);


/*
*	find iterator in range.
*
*	Arguments:
*		from - iterator from where(including) start to search. must be a valid iterator.
*		to - iterator where(excluding) stop to search.
*		match_func - compare between data function. must be a valid pointer.
*		param - the param to compare between data.
*
*	Return: iterator in the range between from and to that data compare to parm if there exist.
*				otherwise return to. 
*
*	Time complexity: O(1) best O(n) average/worst.
*	Space complexity: O(1) best/average/worst.
*
*/
slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t match_func, void *param);


/*
*	do action to do for each iterator in range.
*
*	Arguments:
*		from - iterator from where(including) start to call the function. must be a valid iterator.
*		to - iterator where(excluding) stop to call the function.
*		action_func - action to do for each data in iterator. must be a valid pointer.
*		param - the param to do action to each data in iterator.
*
*	Return: action func status. 
*
*	Time complexity: O(1) best O(n) average/worst.
*	Space complexity: O(1) best/average/worst.
*
*/
int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param);

/*
*	compare between two iterators.
*
*	Arguments:
*		left_iter - one iterator.
*		right_iter - other iterator.
*
*	Return: 1 if left_iter equal to right_iter otherwise 0. 
*
*	Time complexity: O(1) best/average/worst.
*	Space complexity: O(1) best/average/worst.
*
*/
int SListIsEqual(slist_iter_t left_iter, slist_iter_t right_iter);

/*
*
*	Append src to dest.
*
*	Arguments:
*		dest - Singly linked list to which the function append src. must be vaild.
*		src - Singly linked list to append to dest. must be vaild.
*
*	Return: void.
*
*	Time complexity: O(1) best/average/worst
*	Space complexity: O(1) best/average/worst
*
*/
void SListAppend(slist_t *dest, slist_t *src);


#endif /*__LINKED_LIST_H__*/


