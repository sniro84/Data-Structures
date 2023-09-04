/************************************************ 
EXERCISE      : Binary Search Tree
Implmented by : Snir Holland
Reviewed by   : Amitai Bar
Date          : 5/6/23
File          : bst.h
*************************************************/

#include <stddef.h>

#ifndef __BST_H__
#define __BST_H__

/*
*    Compare function between two datas
*
*    Arguments:
*        data1 - a data to compare
*        data2 - a data to compare
*
*    Return: integer less than, equal to, or greater than zero if data is found, respectively, to be less than, equal, or be greater than param.
*
*/
typedef int(*bst_cmp_func_t)(const void *data1, const void *data2);

/*
*    action to perform
*
*    Arguments:
*        data -  the data to perform action on
*        param - the param to perform the action with 
*
*    Return: 0 for success, 1 for failure.
*
*/
typedef int(*bst_action_func_t)(void *data1, void *param);

/* BST iterator */
typedef struct bst_node *bst_iter_t;

/* Managerial struct */
typedef struct bst bst_t;

/*
*
*    Creates a new empty binary search tree
*
*    Arguments:
*		cmp: the function determining the ordering criteria. can't be NULL.
*
*    Return: a pointer to the new binary search tree if successful
*                otherwise return NULL.
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
bst_t *BSTCreate(bst_cmp_func_t cmp);					

/*
*
*    Deallocate all memory allocated for a binary search tree
*
*    Arguments:
*        bst - Pointer to the binary search tree to destroy. must be valid.
*
*    Return: void (Allways succeed).
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
void BSTDestroy(bst_t *bst);							

/*
*
*    Return the number of data stored in a binary search tree.
*
*    Arguments:
*        bst - Pointer to the binary search tree. can't be NULL.
*
*    Return: number of elements in the binary search tree.
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
size_t BSTSize(const bst_t *bst);						


/*
*
*    Insert data to the binary search tree. in case of failure the bst remain unchanged.
*
*    Arguments:
*        bst -  Pointer to the binary search tree to which we wish to insert. must be valid.
*        data - The data that we wish to insert to the binary search tree.
*
*    Return: iterator to the new data if successful or to the BST's end upon fail
*
*    Time complexity: O(1) best O((log(n)) average/worst
*    Space complexity: O(1) best/average/worst
*
*/
bst_iter_t BSTInsert(bst_t *bst, void *data);			

/*
*
*    Remove the given iterator from the binary search tree.
*    
*
*    Arguments:
*        iter - iterator to be removed from the bst. must be a valid iterator.
*
*    Return: void.
*
*    Time complexity: O(1) best, O(log(n)) average/worst
*    Space complexity: O(1) best/average/worst
*
*/
void BSTRemove(bst_iter_t iter);						

/*
*    Find data in range in a binary search tree.
*
*    Arguments:
*		bst - Pointer to the binary search tree to which we wish to insert. must be valid.
*       data - the data we wish to find.
*
*    Return: iterator to the found data. iterator to END if not found
*
*    Time complexity: O(1) best O(log(n)) average/worst.
*    Space complexity: O(1) best/average/worst.
*
*/
bst_iter_t BSTFind(const bst_t *bst, void *data);		



/*
*    get an iterator to the first data in a binary search tree
*
*    Arguments:
*        bst - pointer to the binary search tree. can't be NULL.
*
*    Return: iterator to the first data in a binary search tree or to it's end undefined if the BST is empty
*
*    Time complexity: O(log(n)) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
bst_iter_t BSTGetBegin(const bst_t *bst);			


/*
*    get an iterator to the last data in a binary search tree
*
*    Arguments:
*        bst - pointer to the binary search tree. can't be NULL.
*
*    Return: the last iterator in the binary search tree. NOTICE: Invalid Iterator.
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
bst_iter_t BSTGetEnd(const bst_t *bst);				

/*
*
*    Get the iterator to the next data
*
*    Arguments:
*        iter - current iterator. Must be a valid iterator.
*
*    Return: iterator to the next data or to the end of the binary search tree. next on end is undefined
*
*    Time complexity: O(1) amortized
*    Space complexity: O(1) best/average/worst
*
*/
bst_iter_t BSTNext(bst_iter_t iter);				

/*
*
*    Get the iterator to the previous data
*
*    Arguments:
*        iter - current iterator. Must be a valid iterator that doesn't point to the first data.
*
*    Return: iterator to the previous data in the binary search tree. prev on end is undefined
*
*    Time complexity: O(1) amortized
*    Space complexity: O(1) best/average/worst
*
*/
bst_iter_t BSTPrev(bst_iter_t iter);			

/*
*    Get data from an iterator.
*
*    Arguments:
*        iter - iterator to get data from. must be a valid iterator.
*
*    Return: the data in iterator.
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
void *BSTGetData(bst_iter_t iter);

/*
*    Checks if two iterators point to the same element
*
*    Arguments:
*        iter1 - a valid iterator
*        iter2 - a valid iterator
*
*    Return: 1 if the iterators point at the same element, otherwise 0.
*
*    Time complexity: O(1) best/average/worst.
*    Space complexity: O(1) best/average/worst.
*
*/
int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2);

/*
*    Do an operation on each data in a range.
*
*    Arguments:
*        from - iterator to the start of the range (including). Must be a valid
*        to - iterator to the end of the range (excluding). must be valid or END
*        func - action to do for each data in iterator. must be a valid pointer
*        param - the param to do action to each data in iterator
*
*    Return: 0 upun success, the return value of the last call to func upon failure
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_func_t func, void *param);

/*
*    Checking if the binary search tree is empty.
*
*    Arguments:
*        bst - pointer to the binary search tree. can't be NULL.
*
*    Return: 1 if the binary search tree is empty, otherwise 0
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
int BSTIsEmpty(const bst_t *bst);



#endif   /* __BST_H__ */
/*=============================================================*/