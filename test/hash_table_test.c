/************************************************ 
EXERCISE      : Hash Table
Implmented by : Snir Holland
Reviewed by   : Liran Tzuman
Date          : 15/6/23
File          : hash_table_test.c
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dvector.h>

#include "hash_table.h"
#include "dlist.h"

#define CAPACITY        (30)
#define MAX_WORD_LEN    (30) 

/* Test Functions */
void TestHashCreate();
void TestHashDestroy();
void TestHashInsert();
void TestHashFind();
void TestHashRemove();
void TestHashForEach();
void TestHashIsEmpty();
void TestHashSize();
void TestSpellChecker();

extern void HashToPrint(hash_table_t *hash_table);

static size_t Hash(const void *key);
static int IntCmp(const void *key1, const void *key2);
static int ReplaceWithChar(void *data, void *param);
static int AreAllDollars(void *data, void *param);
static int StrCmp(const void *key1, const void *key2);

int main(void)
{
    TestHashCreate();

    TestHashDestroy();

    TestHashInsert();

    TestHashFind();

    TestHashRemove();

    TestHashForEach();

    TestHashIsEmpty();

    TestHashSize();

    TestSpellChecker();

    return (0);
}

void TestHashCreate()
{
    hash_table_t *hash_table = NULL;

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashCreate()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

	(NULL != hash_table) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestHashDestroy()
{
    hash_table_t *hash_table = NULL;

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashDestroy()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

	printf("Success\n");

    /* checks will be done through valgrind */
	HashDestroy(hash_table);
}

void TestHashInsert()
{
    hash_table_t *hash_table = NULL;

    size_t i = 0;

    size_t test_count = 1;

    int keys[9] = {427,500,613,45,2,88,90,113,5};
    char data[9] = {'A','B','&','#','p','c','@','*', '<'};

    int dup_key = 113;
    int dup_value = 'Q';

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashInsert()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

    for(i=0; i<9; ++i)
    {
        HashInsert(hash_table, &keys[i], &data[i]);
    }

    HashInsert(hash_table, &dup_key, &dup_value);

	(9 == HashSize(hash_table)) ? --test_count : test_count; 
    
    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestHashFind()
{
    hash_table_t *hash_table = NULL;

    size_t i = 0;

    size_t test_count = 4;

    int keys[9] = {427,500,613,45,2,88,90,113,5};
    char data[9] = {'A','B','&','#','p','c','@','*', '<'};

    int keys_to_find[4] = {88 , 666, 113,200};

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashFind()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

    for(i=0; i<9; ++i)
    {
        HashInsert(hash_table, &keys[i], &data[i]);
    }

	(NULL != HashFind(hash_table, &keys_to_find[0])) ? --test_count : test_count; 
	(NULL == HashFind(hash_table, &keys_to_find[1])) ? --test_count : test_count;
	(NULL != HashFind(hash_table, &keys_to_find[2])) ? --test_count : test_count;
	(NULL == HashFind(hash_table, &keys_to_find[3])) ? --test_count : test_count;
    
    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestHashRemove()
{
    hash_table_t *hash_table = NULL;

    size_t i = 0;

    int keys[9] = {427,500,613,45,2,88,90,113,5};
    char data[9] = {'A','B','&','#','p','c','@','*', '<'};

    int keys_to_remove[4] = {88 , 666, 113,200};

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashRemove()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

    for(i=0; i<9; ++i)
    {
        HashInsert(hash_table, &keys[i], &data[i]);
    }

    HashRemove(hash_table, &keys_to_remove[0]);
    HashRemove(hash_table, &keys_to_remove[1]);
    HashRemove(hash_table, &keys_to_remove[2]);
    HashRemove(hash_table, &keys_to_remove[3]);
	
    (7 == HashSize(hash_table)) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestHashForEach()
{
    hash_table_t *hash_table = NULL;

    size_t i = 0;

    size_t status = 0;

    size_t test_count = 2;

    char ch = '$';

    int keys[9] = {427,500,613,45,2,88,90,113,5};
    char data[9] = {'A','B','&','#','p','c','@','*', '<'};

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashForEach()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

    for(i=0; i<9; ++i)
    {
        HashInsert(hash_table, &keys[i], &data[i]);
    }

    status = HashForEach(hash_table, &ReplaceWithChar, &ch);
    (0 == status) ? --test_count : test_count;

    status = HashForEach(hash_table, &AreAllDollars, NULL);
    (0 == status) ? --test_count : test_count;

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestHashIsEmpty()
{
    hash_table_t *hash_table = NULL;

    size_t test_count = 2;

    size_t i = 0;

    int keys[9] = {427,500,613,45,2,88,90,113,5};
    char data[9] = {'A','B','&','#','p','c','@','*', '<'};

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashIsEmpty()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

    (HashIsEmpty(hash_table)) ? --test_count : test_count;

    for(i=0; i<9; ++i)
    {
        HashInsert(hash_table, &keys[i], &data[i]);
    }

    (!HashIsEmpty(hash_table)) ? --test_count : test_count;

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestHashSize()
{
    hash_table_t *hash_table = NULL;

    size_t test_count = 2;

    size_t i = 0;

    int keys[9] = {427,500,613,45,2,88,90,113,5};
    char data[9] = {'A','B','&','#','p','c','@','*', '<'};

    size_t (*hash_func)(const void *key) = &Hash;
    int (*cmp_keys)(const void *key1, const void *key2) = &IntCmp;
    size_t hash_range = CAPACITY;

    printf("--------Testing HashSize()--------\t");

    hash_table = HashCreate(hash_func, cmp_keys, hash_range);

    (0 == HashSize(hash_table)) ? --test_count : test_count;

    for(i=0; i<9; ++i)
    {
        HashInsert(hash_table, &keys[i], &data[i]);
    }

    (9 == HashSize(hash_table)) ? --test_count : test_count;

    (0 == test_count) ? printf("Success\n") : printf("Failure\n");

	HashDestroy(hash_table);
}

void TestSpellChecker()
{
    hash_table_t *hash_table = NULL; 
    FILE *fp = NULL;
    char input[MAX_WORD_LEN] = {'\0'};
    char *dictionary = NULL;
    size_t lines = 0;
    size_t i =0;
    char c = '\0';
    
    hash_table = HashCreate(&Hash, &StrCmp, 500);
    if (NULL == hash_table)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(-1);
    }

    fp = fopen("/usr/share/dict/words","r");
    if (NULL == fp)
    {
        HashDestroy(hash_table);
        fprintf(stderr, "Failed to open file.\n");
        exit(-1);
    }

    /* count the number of lines in the file */
    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if ('\n' == c) 
        {
            ++lines;
        }
    }

    dictionary = (char*)calloc(lines * MAX_WORD_LEN, sizeof(char));
    if (NULL == dictionary)
    {
        fclose(fp);
        HashDestroy(hash_table);
        fprintf(stderr, "Failed to open file.\n");
        exit(-1);
    }

    /* scan line by line and insert words into dictionary */
    rewind(fp);
    c = '\0';

    while (EOF != fscanf(fp, "%s", dictionary + i))
    {
        i += MAX_WORD_LEN;
    }

    fclose(fp);

    /* insert words into hash table */
    for(i=0; i<lines * MAX_WORD_LEN; i += MAX_WORD_LEN)
    {
        HashInsert(hash_table, dictionary + i , dictionary + i);
    }

    /* spell checker */
    printf("Please Enter Word :\n");
    scanf("%s", input);

    printf("Is the word in linux dictionary ? ");
    (NULL == HashFind(hash_table, input)) ? printf("No") : printf("Yes");
    printf("\n");

    printf("Testing Load Factor : %7f \n", HashGetLoadFactor(hash_table));

    printf("Testing Standard Deviation : %7f \n", HashSTD(hash_table));

    free(dictionary);
    HashDestroy(hash_table);
}         

static size_t Hash(const void *key)
{
    return (size_t)*(int*)key;
}

static int IntCmp(const void *key1, const void *key2)
{
    return *(int*)key1 - *(int*)key2;
}

static int StrCmp(const void *key1, const void *key2)
{
    return strcmp((char*)key1 , (char*)key2);
}

static int ReplaceWithChar(void *data, void *param)
{
    *(char*)data = *(char*)param;
    return (0); 
}

static int AreAllDollars(void *data, void *param)
{
    (void)param;
    if ('$' != *(char*)data)
    {
        return (1);
    }
    return (0); 
}
