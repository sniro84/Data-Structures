/************************************************ 
EXERCISE      : AVL Tree
Implmented by : Snir Holland
Reviewed by   : 
Date          : 5/6/23
File          : avl_test.c
*************************************************/

#include <stdio.h> /* printf */

#include "avl.h"

/* Test Functions */
static void TestAVLCreate();
static void TestAVLInsert();
static void TestAVLDestroy();
static void TestAVLIsEmpty();
static void TestAVLRemove();
static void TestAVLForEach();
static void TestAVLSize();
static void TestAVLHeight();
static void TestAVLFind();
static void TestAVLMultiFind();
static void TestAVLMultiRemove(); 

/* Compare Function */
static int IntCmp(const void *key1 , const void *key2);

/* Operation Functions */
static int ReplaceWithHashtags(void *data, void *param);
static int AreAllHashtags(void *data, void *param);

int main(void)
{
	TestAVLCreate();
	TestAVLInsert();
	TestAVLDestroy();
	TestAVLIsEmpty();
    TestAVLRemove();
	TestAVLForEach();
	TestAVLSize();
    TestAVLHeight();
    TestAVLFind();
    TestAVLMultiFind();
    TestAVLMultiRemove();

	return (0);
}

/*----------- TestAVLCreate() -----------*/
static void TestAVLCreate()
{
	avl_t *tree = AVLCreate(&IntCmp);

	printf("--------Testing AVLCreate()--------\t");
	
	(NULL != tree) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLInsert() -----------*/
static void TestAVLInsert()
{
	avl_t *tree = AVLCreate(&IntCmp);
    
    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};
    
    size_t i = 0;

    size_t test_count = 8;

	printf("--------Testing AVLInsert()--------\t");

    for(i=0; i<8; ++i)
    {
        if (0 == AVLInsert(tree, &data[i], &keys[i]))
        {
            --test_count;
        }
    }
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLIsEmpty() -----------*/
static void TestAVLIsEmpty()
{
	avl_t *tree = AVLCreate(&IntCmp);
    
    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};
    
    size_t i = 0;

    size_t test_count = 2;

	printf("--------Testing AVLIsEmpty()--------\t");

    (AVLIsEmpty(tree)) ? --test_count : test_count;

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

    (!AVLIsEmpty(tree)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLDestroy() -----------*/
static void TestAVLDestroy()
{
	avl_t *tree = AVLCreate(&IntCmp);
    
    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};
    
    size_t i = 0;

	printf("--------Testing AVLDestroy()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }
	
	AVLDestroy(tree);

    /* Checks of Destroy function will be done through valgrind */
    printf("Success\n");
}

/*----------- TestAVLRemove() -----------*/
static void TestAVLRemove()
{
	avl_t *tree = AVLCreate(&IntCmp);

    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};
    
    size_t i = 0;

	printf("--------Testing AVLRemove()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }
    
    for(i=0; i<8; ++i)
    {
        AVLRemove(tree, &keys[i]);
    }

    (0 == AVLSize(tree)) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLForEach() -----------*/
static void TestAVLForEach()
{
	avl_t *tree = AVLCreate(&IntCmp);
    traversal_t traversal = PRE_ORDER;

    void *param = NULL;
    
    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};

    size_t i = 0;

    size_t test_count = 2;

	printf("--------Testing AVLForEach()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

    (0 == AVLForEach(tree, &ReplaceWithHashtags, param, traversal)) ? --test_count : test_count;
    (0 == AVLForEach(tree, &AreAllHashtags, param, traversal)) ? --test_count : test_count;

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLSize() -----------*/
static void TestAVLSize()
{
	avl_t *tree = AVLCreate(&IntCmp);
    
    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};

    size_t i = 0;

	printf("--------Testing AVLSize()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

	(8 == AVLSize(tree)) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLHeight() -----------*/
static void TestAVLHeight()
{
	avl_t *tree = AVLCreate(&IntCmp);

    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};

    size_t i = 0;

	printf("--------Testing AVLHeight()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

	(4 == AVLHeight(tree)) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLFind() -----------*/
static void TestAVLFind()
{
	avl_t *tree = AVLCreate(&IntCmp);

    int key1 = 30;
    int key2 = 49;
    
    size_t test_count = 2;

    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};

    size_t i = 0;

	printf("--------Testing AVLFind()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

    ('D' == *(char*)AVLFind(tree, &key1)) ? --test_count : test_count;
    (NULL == AVLFind(tree, &key2)) ? --test_count : test_count;

	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
}

/*----------- TestAVLMultiFind() -----------*/
static void TestAVLMultiFind()
{
	avl_t *tree = AVLCreate(&IntCmp);

    size_t i = 0;

    dlist_t *list_of_keys = DListCreate();
    int numbers[4] = {3, -12 , 25 , 666};

    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};

    avl_t *output_tree = NULL; 

    size_t test_count = 3;

    /* insert keys */
    for (i=0; i<4; ++i)
    {
        DListInsert(DListGetBegin(list_of_keys), &numbers[i]);
    }

	printf("--------Testing AVLMultiFind()--------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

    output_tree = AVLMultiFind(tree, list_of_keys);

    (NULL != AVLFind(output_tree, &numbers[0])) ? --test_count : test_count;
    (NULL != AVLFind(output_tree, &numbers[2])) ? --test_count : test_count;
    (2 == AVLSize(output_tree)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
    AVLDestroy(output_tree);
    DListDestroy(list_of_keys);
}

/*----------- TestAVLMultiRemove() -----------*/
static void TestAVLMultiRemove()
{
	avl_t *tree = AVLCreate(&IntCmp);

    size_t i = 0;

    dlist_t *list_of_keys = DListCreate();
    int numbers[4] = {3, -12 , 25 , 666};

    int keys[8] = {17,3,9,30,25,6,13,1};
    char data[8] = {'A','B','C','D','E','F','G','H'};

    size_t test_count = 3;

    /* insert keys */
    for (i=0; i<4; ++i)
    {
        DListInsert(DListGetBegin(list_of_keys), &numbers[i]);
    }

	printf("--------Testing AVLMultiRemove()------\t");

    for(i=0; i<8; ++i)
    {
        AVLInsert(tree, &data[i], &keys[i]);
    }

    AVLMultiRemove(tree, list_of_keys);

    (NULL == AVLFind(tree, &numbers[0])) ? --test_count : test_count;
    (NULL == AVLFind(tree, &numbers[2])) ? --test_count : test_count;
    (6 == AVLSize(tree)) ? --test_count : test_count;
	
	(0 == test_count) ? printf("Success\n") : printf("Failure\n");

	AVLDestroy(tree);
    DListDestroy(list_of_keys);
}


/*----------End of Test Functions---------*/

/* Compare Function: returns difference between ints */
static int IntCmp(const void *key1 , const void *key2)
{
	return (*(int*)key1 - *(int*)key2);
}

/* Operation Function: replace all data to hashtags*/
static int ReplaceWithHashtags(void *data, void *param)
{
    *(char*)data = '#';
    (void)param;
    return 0;
}

/* Operation Function: are all hashtags */
static int AreAllHashtags(void *data, void *param)
{
    if ('#' != *(char*)data)
    {
        return (1);
    }

    (void)param;
    return 0;
}