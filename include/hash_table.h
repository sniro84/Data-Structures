/************************************************ 
EXERCISE      : Hash Table
Implmented by : Snir Holland
Reviewed by   : Liran Tzuman
Date          : 15/6/23
File          : hash_table.h
*************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>

typedef struct hash_table hash_table_t;

/**
 *   Creates a new empty Hash Table
 *
 *   Arguments:
 *       hash_func - function that convert key to index. can't be NULL.
 *		cmp - the function determining the ordering criteria. can't be NULL.
 *       hash_range - the number of rows for hash table. must be greater than 0.
 *
 *   Return: a pointer to the new Hash Table if successful. otherwise return NULL.
 *
 *   Time complexity: O(n) best/average/worst
 *   Space complexity: O(n) best/average/worst
 */
hash_table_t *HashCreate(size_t (*hash_func)(const void *key), int (*cmp_keys)(const void *key1, const void *key2), size_t hash_range);

/**
 *   Deallocate all memory allocated for a Hash Table
 *
 *   Arguments:
 *       hash_table - Pointer to the Hash Table to destroy. must be valid.
 *
 *   Return: void (Allways succeed).
 *
 *   Time complexity: O(n) best/average/worst
 *   Space complexity: O(n) best/average/worst
 */
void HashDestroy(hash_table_t *hash_table);

/**
 *   Insert data to the Hash Table. in case of failure the Table remain unchanged.
 *
 *   Arguments:
 *       hash_table - Pointer to the Hash Table to destroy. must be valid.
 *       key -  The key of data to insert. must be valid.
 *       data - The data that we wish to insert.
 *
 *   Return: 0 if success, 1 upon fail.
 *
 *   Time complexity: O(1) best/average O(n) worst
 *   Space complexity: O(1) best/average/worst
 */
int HashInsert(hash_table_t *hash_table, const void *key, void *data);

/**
 *   Find data in the Hash Table.
 *
 *   Arguments:
 *       hash_table - Pointer to the Hash Table to destroy. must be valid.
 *       key - the key we wish to find. must be valid.
 *
 *   Return:pointer to the data that has the match key if found. else NULL.
 *
 *   Time complexity: O(1) best/average O(n) worst
 *   Space complexity: O(1) best/average/worst
 */
void *HashFind(const hash_table_t *hash_table, const void *key);

/**
 *
 *  Remove the key from the Hash Table.
 *
 *  Arguments:
 *       hash_table - Pointer to the Hash Table to destroy. must be valid.
 *       key - key to remove from list. must be a valid key.
 *
 *   Return: void.
 *
 *   Time complexity: O(1) best/average O(n) worst
 *   Space complexity: O(1) best/average/worst
 */
void HashRemove(hash_table_t *hash_table, const void *key);

/**
 *  Do an operation on each data in a Hash Table.
 *
 *  Arguments:
 *      hash_table - Pointer to the Hash Table to be scanned. must be valid.
 *      action_func - action to do for each data in Hash Table. must be a valid pointer.
 *      param - the param to do action to each data in Hash Table.
 *
 *    Return: 0 upun success, the return value of the last call to func upon failure.
 *
 *    Time complexity: O(n) best/average/worst
 *    Space complexity: O(1) best/average/worst
 *
 */
int HashForEach(hash_table_t *hash_table, int (*action_func)(void *data, void *param), void *param);

/**
 *    Checking if the Hash Table is empty.
 *
 *    Arguments:
 *        hash_table - Pointer to the Hash Table to destroy. must be valid.
 *
 *    Return: 1 if the Hash Table is empty, otherwise 0
 *
 *    Time complexity: O(n) best/average/worst
 *    Space complexity: O(1) best/average/worst
 *
 */
int HashIsEmpty(const hash_table_t *hash_table);

/**
 *    Return the number of data stored in a Hash Table.
 *
 *    Arguments:
 *       hash_table - Pointer to the Hash Table to destroy. must be valid.
 *
 *    Return: number of elements in the Hash Table.
 *
 *    Time complexity: O(n) best/average/worst
 *    Space complexity: O(1) best/average/worst
 *
 */
size_t HashSize(const hash_table_t *hash_table);


double HashGetLoadFactor(const hash_table_t *hash_table);

double HashSTD(const hash_table_t *hash_table);

#endif /*__HASH_TABLE_H__*/
