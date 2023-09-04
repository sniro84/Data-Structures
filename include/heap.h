/************************************************ 
EXERCISE      : Heap
Implmented by : Snir Holland
Reviewed by   : 
Date          : 18/6/23
File          : heap.h
*************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h> /* size_t */

typedef struct heap heap_t;

/*
*    Compare function between two datas
*
*    Arguments:
*        lhs - a data to compare
*        rhs - a data to compare
*
*    Return: integer less than, equal to, or greater than zero if data is found, respectively, to be less than, equal, or be greater than param.
*
*/
typedef int (*heap_cmp_func_t)(const void *lhs, const void *rhs);

/*
 *   Creates a new empty Heap
 *
 *   Arguments:
 *		 heap_cmp_func - the function determining the ordering criteria. can't be NULL.
 *
 *   Return: a pointer to the new Heap if successful. otherwise return NULL.
 *
 *   Time complexity: O(1) best/average/worst.
 *	 Space complexity: O(1) best/average/worst
 */
heap_t *HeapCreate(heap_cmp_func_t cmp);

/*
 *   destroys heap
 *
 *   Arguments:
 *       Heap - Pointer to the Heap to destroy. must be valid.
 *
 *   Return: void (Always succeeds).
 *
 *   Time complexity: O(1) best/average/worst
 *   Space complexity: O(1) best/average/worst
 */
void HeapDestroy(heap_t *heap);

/*
 *   Insert data to the Heap. in case of failure the Heap remain unchanged.
 *
 *   Arguments:
 *       heap - Pointer to the Heap. must be valid.
 *       data - The data that we wish to insert. can be null.
 *
 *   Return: 0 if successful , 1 upon fail.
 *
 *   Time complexity: O(1) best, O(log(n)) average/worst 
 *   Space complexity: O(1) best/average, O(n)worst
 */
int HeapPush(heap_t *heap, void *data);

/*
 *   Pop data from the top of the Heap.
 *
 *   Arguments:
 *       heap - Pointer to the Heap to pop from. must be valid.
 *
 *   Return: void (Always succeeds).
 *
 *   Time complexity: O(log(n))
 *   Space complexity: O(1) best/average/worst
 */
void HeapPop(heap_t *heap);

/*
*
*	Return the element in the top of the Heap.
*
*	Arguments:
*		heap - pointer to the heap. must be valid.
*
*	Return: The element in the top of the Heap.
*
*	Time complexity: O(1) best/average/worst.
*	Space complexity: O(1) best/average/worst.
*
*/
void *HeapPeek(heap_t *heap);

/*
 *   Removes a data from the Heap.
 *
 *   Arguments:
 *       heap - Pointer to the Heap to remove from. must be valid.
 *       is_match - pointer to a function that check if data matches the param. must be valid.
 *       param - the criteria for the comparison.
 *  
 *   Return: Pointer to the removed data.
 *
 *   Time complexity: best log(n)  average/worst o(n) 
 *   Space complexity: O(1) best/average/worst
 */
void *HeapRemove(heap_t *heap, int (*is_match)(const void *data, const void *param), const void *param);

/*
 *    Return the number of elements stored in the Heap.
 *
 *    Arguments:
 *       heap - Pointer to the Heap. must be valid.
 *
 *    Return: number of elements in the Heap.
 *
 *    Time complexity: O(1) best/average/worst
 *    Space complexity: O(1) best/average/worst
 *
 */
size_t HeapSize(heap_t *heap);

/*
 *    Checking if the Heap is empty.
 *
 *    Arguments:
 *        heap - Pointer to the Heap to check if empty. must be valid.
 *
 *    Return: 1 if the Heap is empty, otherwise 0
 *
 *    Time complexity: O(n) best/average/worst
 *    Space complexity: O(1) best/average/worst
 *
 */
int HeapIsEmpty(heap_t *heap);

#endif /* __HEAP_H__ */
