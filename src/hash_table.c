/************************************************ 
EXERCISE      : Hash Table
Implmented by : Snir Holland
Reviewed by   : Liran Tzuman
Date          : 15/6/23
File          : hash_table.c
*************************************************/

#include <stddef.h> /* size_t , offset */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* stderr */
#include <math.h>

#include "dlist.h"
#include "hash_table.h"

struct hash_table
{
    size_t (*hash_func)(const void *key);
    size_t table_size;         /* num of buckets */
    int (*cmp_keys)(const void *key1, const void *key2);
    dlist_t *table[1];
};

typedef struct info
{
    const void *key;
    void *data;
} info_t;

typedef struct cmp_wrapper
{
	int (*cmp_keys)(const void *key1, const void *key2);
	const void *key_to_find;
} cmp_wrapper_t;

typedef struct action_wrapper
{
	int (*action_func)(void *data, void *param);
	void *param;
} action_wrapper_t;

enum boolean_status
{
    FALSE,
    TRUE
};

enum
{
    SUCCESS,
    FAILURE
};

/* static functions */
static void CleanHashTable(hash_table_t *hash_table);
static void InitHashTable(hash_table_t *hash_table, size_t(*hash_func)(const void *key),int (*cmp_keys)(const void *key1, const void *key2) ,size_t hash_range);
static size_t GenerateIndex(const hash_table_t *hash_table, const void *key);
static int BooleanMatch(const void *info , const void *cmp_wrapper);
static int ActionHashNode(void *info, void *action_wrapper);
static dlist_iter_t FindIter(const hash_table_t *hash_table, const void *key);

/* ------------- HashCreate ------------- */
hash_table_t *HashCreate(size_t (*hash_func)(const void *key), int (*cmp_keys)(const void *key1, const void *key2), size_t hash_range)
{
    hash_table_t *hash_table = NULL;	
	
	assert(0 != hash_range);
    assert(NULL != hash_func);
    assert(NULL != cmp_keys);

	hash_table = (hash_table_t*)malloc(offsetof(hash_table_t, table) + hash_range * sizeof(dlist_t *));
	if (NULL == hash_table)
	{
		return NULL;
	}

    InitHashTable(hash_table, hash_func, cmp_keys, hash_range);

    return hash_table;
}

/* ------------- HashDestroy ------------- */
void HashDestroy(hash_table_t *hash_table)
{
    size_t i = 0;

    assert(NULL != hash_table);

    for(i=0; i<hash_table->table_size; ++i)
    {
        dlist_iter_t iter = DListGetBegin(hash_table->table[i]);
        dlist_iter_t end = DListGetEnd(hash_table->table[i]);

        while (!DListIsEqual(iter,end))
        {
            free(DListGetData(iter));

            iter = DListRemove(iter);
        }

        DListDestroy(hash_table->table[i]);
    }

    CleanHashTable(hash_table);

    free(hash_table);
    hash_table = NULL;
}

/* ------------- HashIsEmpty ------------- */
int HashIsEmpty(const hash_table_t *hash_table)
{
    assert(NULL != hash_table);

    return (0 == HashSize(hash_table));
}

/* ------------- HashSize ------------- */
size_t HashSize(const hash_table_t *hash_table)
{
    size_t i = 0;
    size_t total = 0;

    assert(NULL != hash_table);

    for(i=0; i<hash_table->table_size; ++i)
    {
        total += DListCount(hash_table->table[i]);
    }    

    return total;
}

/* ------------- HashInsert ------------- */
int HashInsert(hash_table_t *hash_table, const void *key, void *data)
{
    info_t *info = NULL;
    size_t index = 0;
    dlist_t *list = NULL;

    assert(NULL != hash_table);
    assert(NULL != key);

    info = (info_t *)malloc(sizeof(info_t));
    if (NULL == info)
    {
        return FAILURE;
    }

    info->key = key;
    info->data = data;

    index = GenerateIndex(hash_table, key);

    list = hash_table->table[index];

    /* if key is already there, it is overridden */
    if (NULL != HashFind(hash_table, key))
    {
        /* override the data */
        HashRemove(hash_table, key);
    }   
    
    if (DListIsEqual(DListGetEnd(list), DListPushFront(list, info)))
    {
        free(info);
        info = NULL;
        return FAILURE;
    }

    return SUCCESS;
}

/* ------------- HashFind ------------- */
void *HashFind(const hash_table_t *hash_table, const void *key)
{
    info_t *info = NULL;   

    dlist_iter_t result = NULL;

    assert(NULL != hash_table);
    assert(NULL != key);

    result = FindIter(hash_table, key);
    if (NULL == result)
    {
        return NULL;
    }

    info = (info_t *)DListGetData(result);
	return info->data;
}

/* ------------- HashRemove ------------- */
void HashRemove(hash_table_t *hash_table, const void *key)
{
    info_t *info = NULL;   

    dlist_iter_t result = NULL;

    assert(NULL != hash_table);
    assert(NULL != key);

    result = FindIter(hash_table, key);
    if (NULL == result)
    {
        return;
    }

    info = (info_t *)DListGetData(result);
    free(info);
    info = NULL;

	DListRemove(result);
}

/* ------------- HashForEach ------------- */
int HashForEach(hash_table_t *hash_table, int (*action_func)(void *data, void *param), void *param)
{
    size_t i = 0;

    action_wrapper_t action_wrapper = {NULL};
    
    assert(NULL != hash_table);
    assert(NULL != action_func);

    action_wrapper.action_func = action_func;
    action_wrapper.param = param;

    for(i=0; i<hash_table->table_size; ++i)
    {
        dlist_iter_t begin = DListGetBegin(hash_table->table[i]);
        dlist_iter_t end = DListGetEnd(hash_table->table[i]);

        if (FAILURE == DListForEach(begin, end, &ActionHashNode, &action_wrapper))
        {
            return FAILURE;
        }
    }
    return SUCCESS;
}

/* ---------------- Static Functions -------------------*/

/* Helper Function: clean hash table parameters */
static void CleanHashTable(hash_table_t *hash_table)
{
    hash_table->hash_func = NULL;
    hash_table->cmp_keys = NULL;
    hash_table->table_size = 0;
}

/* Helper Function: inititalize hash table */
static void InitHashTable(hash_table_t *hash_table, size_t(*hash_func)(const void *key),int (*cmp_keys)(const void *key1, const void *key2) ,size_t hash_range)
{
    size_t i = 0;

    hash_table->hash_func = hash_func;
    hash_table->cmp_keys = cmp_keys;
    hash_table->table_size = hash_range;

    for(i=0; i<hash_range; ++i)
    {
        hash_table->table[i] = DListCreate();
        
        if (NULL == hash_table->table[i])
        {
            size_t j = 0;

            for(j=0; j<i; ++j)
            {
                DListDestroy(hash_table->table[j]);
            }

            free(hash_table);
            hash_table = NULL;

            fprintf(stderr, "Memory Allocation error.");
            exit(-1);
        } 
    }
}

/* Helper Function: generate index */
static size_t GenerateIndex(const hash_table_t *hash_table, const void *key)
{
    size_t generated_key = 0;

    assert(NULL != hash_table);

    generated_key = hash_table->hash_func(key);
    generated_key = (3 * (generated_key + 7)) % hash_table->table_size;
    
    return generated_key;
}

/* Helper Function: boolean match function for iterator's info */
static int BooleanMatch(const void *info , const void *cmp_wrapper)
{
	int (*cmp_keys)(const void *key1, const void *key2) = ((cmp_wrapper_t*)cmp_wrapper)->cmp_keys;
	const void *key_to_find = ((cmp_wrapper_t*)cmp_wrapper)->key_to_find;
	
	return (cmp_keys(((info_t*)info)->key , key_to_find) == 0);	
}

/* Helper Function: action function for iterator's info */
static int ActionHashNode(void *info, void *action_wrapper)
{   
    int (*action_func)(void *data, void *param) = ((action_wrapper_t *)action_wrapper)->action_func;
    void *param = ((action_wrapper_t *)action_wrapper)->param;

    return (action_func(((info_t*)info)->data, param));
}

/* Helper Function: finds iterator and returns iterator or null if not found*/
static dlist_iter_t FindIter(const hash_table_t *hash_table, const void *key)
{
    size_t index = 0;  

    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    dlist_iter_t result = NULL;

    cmp_wrapper_t cmp_wrapper = {NULL};  

    assert(NULL != hash_table);
    assert(NULL != key);

    cmp_wrapper.cmp_keys = hash_table->cmp_keys;
    cmp_wrapper.key_to_find = key;

    index = GenerateIndex(hash_table, key);

    begin = DListGetBegin(hash_table->table[index]);
    end = DListGetEnd(hash_table->table[index]);

    result = DListFind(begin, end, &BooleanMatch , &cmp_wrapper);
    if (DListIsEqual(result, end))
    {
        return NULL;
    }

    return result;
}

double HashGetLoadFactor(const hash_table_t *hash_table)
{
    assert(NULL != hash_table);

    return ( (double)(HashSize(hash_table)) / (hash_table->table_size));
}

double HashSTD(const hash_table_t *hash_table)
{
    size_t buckets = 0; 
    size_t sum_of_squares = 0;
    double average = 0.0; 
    size_t elem_count = 0;     

    size_t i = 0;

    assert(NULL != hash_table);

    buckets = hash_table->table_size;
    average = HashGetLoadFactor(hash_table);

    for(i=0; i<buckets; ++i)
    {
        elem_count = DListCount(hash_table->table[i]);
        sum_of_squares += pow((elem_count - average), 2);
    }

    return sqrt( (double)sum_of_squares / buckets );
}


/* STD = sqrt( sum(xi - x`)^2) / n)

xi : element count at a cretain bucket
x` : avg number of elements in a bucket
n  : number of buckets */


/* sum = (x1-x`)^2 + (x2-x`)^2 +... */