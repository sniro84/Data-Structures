/************************************************ 
EXERCISE      : AVL Tree
Implmented by : Snir Holland
Reviewed by   : 
Date          : 5/6/23
File          : avl.c
*************************************************/

#include <stdio.h>    /* size_t*/
#include <stdlib.h>   /* malloc, free */
#include <assert.h>   /* assert */

#include "avl.h"

#define COUNT                  (10)
#define TRAVERSALS_AMOUNT      (3)
#define BALANCE_THRESHOLD      (1)

typedef enum child_pos
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
} child_pos_t;

typedef struct info
{
    void *key;
    void *data;
}info_t;

typedef struct avl_node
{
    info_t info;
    struct avl_node *children[NUM_OF_CHILDREN];
    size_t height;
} avl_node_t;

struct avl
{
    avl_node_t *root;
    int (*cmp)(const void *key1, const void *key2);
};

typedef int (*foreach_func_t)(avl_node_t *node, action_func_t action_func, void *param);

enum status_t 
{
    SUCCESS,
    FAILURE
};

/* ---------- Helper functions ----------- */
static void KillNode(avl_node_t *node);
static void CleanNode(avl_node_t *node);
static void *GetData(const avl_t *tree, avl_node_t *node, const void *key);
static avl_node_t *FindAndInsert(avl_t *tree, avl_node_t *node, avl_node_t *new_node);
static avl_node_t *FindAndRemove(avl_t *tree, avl_node_t *root, const void *key);
static size_t CountNodes(avl_node_t *node);
static void UpdateHeight(avl_node_t *node);
static int HasLeftChild(avl_node_t *node);
static int HasRightChild(avl_node_t *node);
static avl_node_t *GetLeftmostNode(avl_node_t *node);
static int ForEachPreOrder(avl_node_t *node, int (*action_func)(void *data, void *param), void *param);
static int ForEachInOrder(avl_node_t *node, int (*action_func)(void *data, void *param), void *param);
static int ForEachPostOrder(avl_node_t *node, int (*action_func)(void *data, void *param), void *param);
static int GetBalanceFactor(avl_node_t *node);
static avl_node_t *LeftRotate(avl_node_t *node);
static avl_node_t *RightRotate(avl_node_t *node);
static avl_node_t *ApplyRotation(avl_node_t *node, int balance);
static size_t Max(size_t x, size_t y);
static void print2DUtil(avl_node_t* root, int space);

/* ---------------- AVLCreate ---------------- */
avl_t *AVLCreate(int (*cmp)(const void *key1, const void *key2))
{
    avl_t *tree = NULL;

    assert(NULL != cmp);

    tree = (avl_t *)malloc(sizeof(avl_t));
    if (NULL == tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->cmp = cmp;    

    return tree;
}

/* ---------------- AVLDestroy ---------------- */
void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);

    KillNode(tree->root);

    free(tree);
    tree = NULL;
}

/* ---------------- AVLIsEmpty ---------------- */
int AVLIsEmpty(const avl_t *tree)
{
    assert(NULL != tree);

    return (NULL == tree->root);
}

/* ---------------- AVLInsert ---------------- */
int AVLInsert(avl_t *tree, void *data, const void *key)
{
    avl_node_t *new_node = NULL;

    assert(NULL != tree);
    assert(NULL != data);
    assert(NULL != key);

    new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (NULL == new_node)
    {
        return FAILURE; 
    }

    CleanNode(new_node);

    new_node->info.data = data;
    new_node->info.key = (void*)key;
    
    tree->root = FindAndInsert(tree, tree->root, new_node);
    
    return SUCCESS;

}

/* ---------------- AVLHeight ---------------- */
size_t AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);

    return tree->root->height;
}

/* ---------------- AVLRemove ---------------- */
void AVLRemove(avl_t *tree, const void *key)
{ 
    assert(NULL != tree);
    assert(NULL != key);

    tree->root = FindAndRemove(tree, tree->root, key);
}

/* ---------------- AVLSize ---------------- */
size_t AVLSize(const avl_t *tree)
{
    assert(NULL != tree);

    return CountNodes(tree->root);
}

/* ---------------- AVLForEach ---------------- */
int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *param), void *param, traversal_t order)
{
    int status = SUCCESS;

    static foreach_func_t foreach_funcs[TRAVERSALS_AMOUNT] = 
    {
        &ForEachPreOrder,
        &ForEachInOrder,
        &ForEachPostOrder
    }; 

    status = foreach_funcs[order](tree->root, action_func, param);

    return status;
}

/* ---------------- AVLFind ---------------- */
void *AVLFind(const avl_t *tree, const void *key)
{
    assert(NULL != key);
    assert(NULL != tree);

    return GetData(tree, tree->root, key);    
}

/* ---------------- AVLMultiFind ---------------- */
avl_t *AVLMultiFind(const avl_t *tree, const dlist_t *keys)
{
    avl_t *output_tree = NULL;

    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    dlist_iter_t runner = NULL;

    assert(NULL != tree);
    assert(NULL != keys);

    output_tree = AVLCreate(tree->cmp);

    begin = DListGetBegin(keys);
    end = DListGetEnd(keys);

    runner = begin;

    while (!DListIsEqual(runner, end))
    {
        /* check if value of iterator is in the tree */
        void *key = DListGetData(runner);

        void *data = AVLFind(tree, key);

        if (NULL != data)
        {
            /* create node_t, put the data, push into output tree */
            AVLInsert(output_tree, data, key);
        }

        runner = DListNext(runner);
    }

    return output_tree;
}

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

/* ---------------- AVLMultiFind ---------------- */
void AVLMultiRemove(avl_t *tree, const dlist_t *keys)
{
    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    dlist_iter_t runner = NULL;

    assert(NULL != tree);
    assert(NULL != keys);

    begin = DListGetBegin(keys);
    end = DListGetEnd(keys);

    runner = begin;

    while (!DListIsEqual(runner, end))
    {
        /* check if value of iterator is in the tree */
        void *key = DListGetData(runner);

        AVLRemove(tree, key);

        runner = DListNext(runner);
    }
}











/* Helper Function : recursively find the data of a node */
static void *GetData(const avl_t *tree, avl_node_t *node, const void *key)
{
    int result = 0;
    child_pos_t position = NUM_OF_CHILDREN;

    if (NULL == node)
    {
        return NULL;
    }

    result = tree->cmp(key, node->info.key);

    if (0 == result)
    {
        return node->info.data;
    }

    position = (result < 0) ? LEFT : RIGHT;

    return GetData(tree, node->children[position], key);
}

/* Helper Function : count nodes in the tree */
static size_t CountNodes(avl_node_t *node)
{
    if (NULL == node)
    {
        return 0;
    }
    return 1 + CountNodes(node->children[LEFT]) + CountNodes(node->children[RIGHT]);
}

/* Helper Function : recursively find and remove a node */
static avl_node_t *FindAndRemove(avl_t *tree, avl_node_t *node, const void *key)
{
    child_pos_t position = NUM_OF_CHILDREN;
    avl_node_t *successor = NULL;
    int result = 0;
    int balance = 0;

    if (NULL == node)
    {
        return node;
    }

    result = tree->cmp(key, node->info.key);
    if (0 != result)
    {
        position = (result < 0) ? LEFT : RIGHT;
        node->children[position] = FindAndRemove(tree, node->children[position] , key);
    }

    else
    {
        if (!HasLeftChild(node) || !HasRightChild(node))
        {
            avl_node_t *temp = (HasLeftChild(node)) ? node->children[LEFT] : node->children[RIGHT];

            if (NULL == temp)
            {
                temp = node;
                node = NULL;
            } 
            else
            {
                *node = *temp;
            }

            free(temp);
            return node;
        }

        else
        {
            successor = GetLeftmostNode(node->children[RIGHT]);
            node->info.key = successor->info.key;
            node->info.data = successor->info.data;
            node->children[RIGHT] = FindAndRemove(tree, node->children[RIGHT], successor->info.key);
        }
    }
 
    UpdateHeight(node);
    balance = GetBalanceFactor(node);
    node = ApplyRotation(node, balance);

    return node;
}

/* Helper Function : search for location to insert the new data */
static avl_node_t *FindAndInsert(avl_t *tree, avl_node_t *node, avl_node_t *new_node)
{
    child_pos_t position = NUM_OF_CHILDREN; 
    int balance = 0;

    if (NULL == node)  
    {
        return new_node;
    }

    position = (tree->cmp(new_node->info.key, node->info.key) < 0) ? LEFT : RIGHT;
    node->children[position] = FindAndInsert(tree, node->children[position], new_node);
    
    UpdateHeight(node);
    balance = GetBalanceFactor(node);
    return ApplyRotation(node, balance);
}

/* Helper Function: decide which rotation should be done with respect to balance factor */
static avl_node_t *ApplyRotation(avl_node_t *node, int balance)
{
    if (balance > BALANCE_THRESHOLD)
    {
        if (GetBalanceFactor(node->children[LEFT]) < 0)
        {
            node->children[LEFT] = LeftRotate(node->children[LEFT]);
        }
        return RightRotate(node);
    }
    
    else if (balance < -(BALANCE_THRESHOLD))
    {
        if (GetBalanceFactor(node->children[RIGHT]) > 0)
        {
            node->children[RIGHT] = RightRotate(node->children[RIGHT]);
        }
        return LeftRotate(node);
    }

    return node;
}

/* Helper Function: recursivly eliminates all nodes in the tree */
static void KillNode(avl_node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    KillNode(node->children[LEFT]);
    KillNode(node->children[RIGHT]);
    
    free(node);
    node = NULL;
}

/* Helper Function: updates height of node */
static void UpdateHeight(avl_node_t *node)
{
    size_t left_child_height = 0;
    size_t right_child_height = 0;

    if (HasLeftChild(node))
    {
        left_child_height = node->children[LEFT]->height;
    }

    if (HasRightChild(node))
    {
        right_child_height = node->children[RIGHT]->height;
    }

    node->height = Max(left_child_height, right_child_height) + 1;
}

/* Helper Function: returns max between two functions */
static size_t Max(size_t x, size_t y)
{
    return (x > y) ? x : y;
}

/* Helper Function: returns true if node has a left child */
static int HasLeftChild(avl_node_t *node)
{
	assert(NULL != node);

	return (NULL != node->children[LEFT]);
}

/* Helper Function: returns true if node has a right child */
static int HasRightChild(avl_node_t *node)
{
	assert(NULL != node);

	return (NULL != node->children[RIGHT]);
}

/* Helper Function: get leftmost node of the subtree rooted in node */
static avl_node_t *GetLeftmostNode(avl_node_t *node)
{
    if (!HasLeftChild(node))
    {
        return node;
    }
    return GetLeftmostNode(node->children[LEFT]);
}

/* Helper Function: perform action on each node with pre-order traversal */
static int ForEachPreOrder(avl_node_t *node, int (*action_func)(void *data, void *param), void *param)
{    
    if (NULL == node)
    {
        return SUCCESS;
    }

    if (FAILURE == action_func(node->info.data, param))
    {
        return FAILURE;
    }
    if (FAILURE == ForEachPreOrder(node->children[LEFT], action_func, param))
    {
        return FAILURE;
    }
    if (FAILURE == ForEachPreOrder(node->children[RIGHT], action_func, param))
    {
        return FAILURE;
    }
  
    return SUCCESS;
}

/* Helper Function: perform action on each node with in-order traversal */
static int ForEachInOrder(avl_node_t *node, int (*action_func)(void *data, void *param), void *param)
{
    if (NULL == node)
    {
        return SUCCESS;
    }

    if (FAILURE == ForEachInOrder(node->children[LEFT], action_func, param))
    {
        return FAILURE;
    }
    if (FAILURE == action_func(node->info.data, param))
    {
        return FAILURE;
    }
    if (FAILURE == ForEachInOrder(node->children[RIGHT], action_func, param))
    {
        return FAILURE;
    }

    return SUCCESS;
}

/* Helper Function: perform action on each node with post-order traversal */
static int ForEachPostOrder(avl_node_t *node, int (*action_func)(void *data, void *param), void *param)
{
    if (NULL == node)
    {
        return SUCCESS;
    }

    if (FAILURE == ForEachPreOrder(node->children[LEFT], action_func, param))
    {
        return FAILURE;
    }
    if (FAILURE == ForEachPreOrder(node->children[RIGHT], action_func, param))
    {
        return FAILURE;
    }
    if (FAILURE == action_func(node->info.data, param))
    {
        return FAILURE;
    }

    return SUCCESS;
}

/* Helper Function: get balance factor of a node */
static int GetBalanceFactor(avl_node_t *node)
{
    int left_child_height = 0;
    int right_child_height = 0;

    if (HasLeftChild(node))
    {
        left_child_height = node->children[LEFT]->height;
    }

    if (HasRightChild(node))
    {
        right_child_height = node->children[RIGHT]->height;
    }

    return left_child_height - right_child_height;
}

/* Helper Function: perform left rotation */
static avl_node_t *LeftRotate(avl_node_t *x_node)
{
    avl_node_t *y_node = x_node->children[RIGHT];
    avl_node_t *root_of_subtree = y_node->children[LEFT];

    y_node->children[LEFT] = x_node;
    x_node->children[RIGHT] = root_of_subtree;

    UpdateHeight(x_node);
    UpdateHeight(y_node);

    return y_node;
}

/* Helper Function: perform right rotation */
static avl_node_t *RightRotate(avl_node_t *y_node)
{
    avl_node_t *x_node = y_node->children[LEFT];
    avl_node_t *root_of_subtree = x_node->children[RIGHT];

    x_node->children[RIGHT] = y_node;
    y_node->children[LEFT] = root_of_subtree;

    UpdateHeight(y_node);
    UpdateHeight(x_node);

    return x_node;
}

/* Helper Function: initializes a node */
static void CleanNode(avl_node_t *node)
{
    size_t i = 0;
    node->info.data = NULL;
    node->info.key = NULL;
    node->height = 1;
    for(i=0; i<NUM_OF_CHILDREN; ++i)
    {
        node->children[i] = NULL;
    }
}

/* Helper Function: prints a 2d version of avl */
static void print2DUtil(avl_node_t* root, int space)
{
    int i = 0;

    if (root == NULL)
        return;
 
    space += COUNT;
 
    print2DUtil(root->children[RIGHT], space);

    printf("\n");
    
    for (i = COUNT; i < space; i++)
    {
        printf(" ");
    }

    printf("%d (%lu)\n", *(int *)root->info.key, root->height);
 
    print2DUtil(root->children[LEFT], space);
    
    printf("\n");
}

/* Helper Function : prints a 2d version of the avl tree */
void print2D(avl_t* tree)
{
    print2DUtil(tree->root, 0);
}

