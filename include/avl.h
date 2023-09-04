/************************************************ 
EXERCISE      : AVL Tree
Implmented by : Snir Holland
Reviewed by   : 
Date          : 5/6/23
File          : avl.h
*************************************************/

#ifndef __AVL_H__
#define __AVL_H__

#include "dlist.h"

typedef struct avl avl_t;

typedef enum traversal
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} traversal_t;

/*
*
*    Creates a new empty AVL tree
*
*    Arguments:
*		cmp: the function determining the ordering criteria. can't be NULL.
*
*    Return: a pointer to the new AVL tree if successful
*                otherwise return NULL.
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
avl_t *AVLCreate(int (*cmp)(const void *key1, const void *key2));

/*
*
*    Deallocate all memory allocated for a AVL tree
*
*    Arguments:
*        tree - Pointer to the AVL tree to destroy. must be valid.
*
*    Return: void (Allways succeed).
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(n) best/average/worst
*
*/
void AVLDestroy(avl_t *tree);

/*
*    Find data in the AVL tree.
*
*    Arguments:
*		tree - Pointer to the AVL tree to which we wish to insert. must be valid.
*       key - the key we wish to find.
*
*    Return:pointer to the data that has the match key if found. else NULL. 
*
*    Time complexity: O(1) best O(log(n)) average/worst.
*    Space complexity: O(log(n)) best/average/worst.
*
*/
void *AVLFind(const avl_t *tree, const void *key);   

/*
*
*    Insert data to the AVL tree. in case of failure the AVL remain unchanged.
*
*    Arguments:
*        tree -  Pointer to the AVL tree to which we wish to insert. must be valid.
*        data - The data that we wish to insert to the AVL tree.
*		 key -  The key of data to insert.
*
*    Return: 0 if success, 1 upon fail.
*
*    Time complexity: O(1) best O((log(n)) average/worst
*    Space complexity: O(log(n)) best/average/worst
*
*/
int AVLInsert(avl_t *tree, void *data, const void *key);

/*
*
*    Remove the first occurrence of the given key from the AVL tree.
*    
*
*    Arguments:
*		 tree - the AVL tree. must be valid.
*        key - key to remove from list. must be a valid key.
*		
*    Return: void.
*
*    Time complexity: O(log(n)) best/average/worst
*    Space complexity: O(log(n)) best/average/worst
*
*/
void AVLRemove(avl_t *tree, const void *key);

/*
*
*    Return the number of data stored in a AVL tree.
*
*    Arguments:
*       tree - Pointer to the AVL tree. can't be NULL.
*		
*    Return: number of elements in the AVL tree.
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(n) best/average/worst
*
*/
size_t AVLSize(const avl_t *tree);

/*
*    Do an operation on each data in a AVL tree.
*
*    Arguments:
*
*        tree - AVL tree pointer. must be valid. 
*        action_func - action to do for each data in AVL tree. must be a valid pointer
*        param - the param to do action to each data in AVL tree.
*		 order - the order of traversal.
*
*    Return: 0 upun success, the return value of the last call to func upon failure
*
*    Time complexity: O(n) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *param), void *param, traversal_t order);

/*
*    Checking if the AVL tree is empty.
*
*    Arguments:
*        tree - pointer to the AVL tree. can't be NULL.
*
*    Return: 1 if the AVL tree is empty, otherwise 0
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
int AVLIsEmpty(const avl_t *tree);

/*
*
*    Return the height of the AVL tree.
*
*    Arguments:
*       tree - Pointer to the AVL tree. can't be NULL.
*		
*    Return: height of the AVL tree.
*
*    Time complexity: O(1) best/average/worst
*    Space complexity: O(1) best/average/worst
*
*/
size_t AVLHeight(const avl_t *tree);

/*Ad.*/

/*
*    Find data in the AVL tree and store it in a new AVL tree.
*
*    Arguments:
*		tree - Pointer to the AVL tree . must be valid.
*       keys - the dlist of keys we wish to find.  must be valid.
*
*    Return: pointer to the AVL tree that contains all the match keys if found. in case of failure NULL. 
*
*    Time complexity: O(n) best/average/worst.
*    Space complexity: O(n) best/average/worst.
*
*/
avl_t *AVLMultiFind(const avl_t *tree, const dlist_t *keys);

/*
*    Remove data from the AVL tree that match keys.
*
*    Arguments:
*		tree - Pointer to the AVL tree . must be valid.
*       keys - the dlist of keys we wish to remove. must be valid.
*
*    Return: void. 
*
*    Time complexity: O(n) best/average/worst.
*    Space complexity: O(n) best/average/worst.
*
*/
void AVLMultiRemove(avl_t *tree, const dlist_t *keys);


void print2D(avl_t* tree);

#endif /*__AVL_H__*/