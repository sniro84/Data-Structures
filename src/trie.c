/************************************************ 
EXERCISE      : Trie
Implmented by : Snir Holland
Reviewed by   : 
Date          : 22/6/23
File          : trie.c
*************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "trie.h"

typedef enum children
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN
} children_t;

enum boolean_status
{
    FALSE,
    TRUE
};

typedef struct trie_node
{
    struct trie_node *children[NUM_OF_CHILDREN];
    struct trie_node *parent;
    int is_full;
} trie_node_t;

struct trie
{
    size_t height;
    trie_node_t *root;
};

/* Helper function: initializes trie node */
static void CleanUpNode(trie_node_t *node);

/* Helper function: returns true if both children of node are full, false otherwise */
static int AreAllChildrenFull(trie_node_t *root);

/* Helper function: returns true if a node is a leaf, false otherwise */
static int IsLeaf(trie_node_t *root);

/* Helper function: returns true if a node is a full, false otherwise */
static int IsFull(trie_node_t *root);

/* Helper function: returns true if a node is a child with specified direction, false otherwise */
static int HasChild(trie_node_t *root, unsigned char dir);

/* Helper function: initializes next free path string to zeros */
static void InitNextPath(unsigned char *path_str, size_t height);

/* Helper function: returns the closest free path in subtrie of root */
static int FindClosestFreePath(trie_node_t *root, unsigned char *path_str, size_t height);

/* Helper function: locate spot and insert trie node recursively */
static int InsertRec(trie_node_t *root, size_t height, unsigned char *path_str, unsigned char *result);

/* Helper function: locate trie node and remove it recursively */
static int RemoveRec(trie_node_t *root, size_t height, unsigned char *path_str);

/* Helper function: destroys trie nodes recursively */
static void DestroyRec(trie_node_t *root);

/* Helper function: counts trie nodes (only full) recursively */
static size_t CountRec(trie_node_t *root);


/* -------------- TrieCreate -------------- */
trie_t *TrieCreate(size_t height)
{
    trie_t *trie = (trie_t *)malloc(sizeof(trie_t));
    if (NULL == trie)
    {
        return NULL;
    }

    trie->root = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (NULL == trie->root)
    {
        free(trie);
        trie = NULL;

        return NULL;
    }

    CleanUpNode(trie->root);
    trie->height = height;

    return trie;
}

/* -------------- TrieDestroy -------------- */
void TrieDestroy(trie_t *trie)
{
    assert(NULL != trie);

    DestroyRec(trie->root);

    free(trie);
    trie = NULL;
}

/* -------------- TrieInsert -------------- */
int TrieInsert(trie_t *trie, unsigned char *path_str, unsigned char *result)
{
    assert(NULL != trie);
    assert(NULL != path_str);
    assert(NULL != result);

    return InsertRec(trie->root, trie->height, path_str, result);
}

/* -------------- TrieRemove -------------- */
int TrieRemove(trie_t *trie, unsigned char *path_str)
{
    assert(NULL != trie);
    assert(NULL != path_str);

    return RemoveRec(trie->root, trie->height, path_str);
}

/* -------------- TrieCount -------------- */
size_t TrieCount(trie_t *trie)
{
    assert(NULL != trie);

    return CountRec(trie->root);
}

/* -------------- Static Functions ----------------- */

static void CleanUpNode(trie_node_t *node)
{
    size_t i = 0;

    for(i=0; i<NUM_OF_CHILDREN; ++i)
    {
        node->children[i] = NULL;
    }
    node->parent = NULL;
    node->is_full = FALSE;
}

static void DestroyRec(trie_node_t *root)
{
    size_t i = 0;

    if (NULL == root)
    {
        return;
    }

    for(i=0; i<NUM_OF_CHILDREN; ++i)
    {
        DestroyRec(root->children[i]);
    }

    free(root);
    root = NULL;
}

static int AreAllChildrenFull(trie_node_t *root)
{
    size_t i = 0;

    for(i=0; i<NUM_OF_CHILDREN; ++i)
    {
        if (!HasChild(root, i) || !IsFull(root->children[i]))
        {
            return FALSE;
        }    
    }

    return TRUE;
}

static void InitNextPath(unsigned char *path_str, size_t height)
{
    size_t i = 0;

    for (i=0; i<height; ++i)
    {
        *(path_str + i) = '0';
    }
}

static int FindClosestFreePath(trie_node_t *root, unsigned char *path_str, size_t height)
{
    unsigned char dir = RIGHT;
    InitNextPath(path_str, height);

    /* if right child doesn't exist, create it */
    if (!HasChild(root, dir))
    {
        root->children[dir] = (trie_node_t *)malloc(sizeof(trie_node_t));
        if (NULL == root->children[dir])
        {
            return TRIE_MEMORY_ERROR;
        }

        CleanUpNode(root->children[dir]);
        root->children[dir]->parent = root;
    }

    return dir;
}

static int InsertRec(trie_node_t *root, size_t height, unsigned char *path_str, unsigned char *result)
{
    int status = 0;
    unsigned char dir = 0;

    if (IsFull(root))
    {
        return TRIE_NO_FREE_PATH;
    }

    if (0 == height)
    {
        root->is_full = TRUE;
        return TRIE_SUCCESS;
    }

    dir = *path_str - '0';

    /* keep creating trie nodes until end of string */
    if (!HasChild(root, dir))
    {
        root->children[dir] = (trie_node_t *)malloc(sizeof(trie_node_t));
        if (NULL == root->children[dir])
        {
            return TRIE_MEMORY_ERROR;
        }

        CleanUpNode(root->children[dir]);
        root->children[dir]->parent = root;
    }

    status = InsertRec(root->children[dir], height - 1, path_str + 1, result + 1);

    /* no free path, search for closest available path */
    if (TRIE_NO_FREE_PATH == status && LEFT == dir)
    {
        dir = FindClosestFreePath(root, path_str, height);
        status = InsertRec(root->children[dir], height - 1, path_str + 1, result + 1);
    }

    if (TRIE_SUCCESS == status)
    {
        root->is_full = AreAllChildrenFull(root);
        *result = dir + '0';
    }

    return status;
}

static size_t CountRec(trie_node_t *root)
{
    if (NULL == root)
    {
        return 0;
    }

    if (IsLeaf(root) && IsFull(root))
    {
        return 1;
    }

    return CountRec(root->children[LEFT]) + CountRec(root->children[RIGHT]);
}

static int RemoveRec(trie_node_t *root, size_t height, unsigned char *path_str)
{
    unsigned char dir = *path_str - '0';

    if (NULL == root)
    {
        return TRIE_NOT_FOUND;
    }

    if (0 == height)
    {
        if (!IsFull(root))
        {
            return TRIE_NOT_FOUND;
        }

        /* found path for removal */
        root->is_full = FALSE;
        return TRIE_SUCCESS;
    }

    root->is_full = FALSE;

    return RemoveRec(root->children[dir], height - 1, path_str + 1);
}

static int IsLeaf(trie_node_t *root)
{
    size_t i = 0;

    assert(NULL != root);

    for(i=0; i<NUM_OF_CHILDREN; ++i)
    {
        if (HasChild(root, i))
        {
            return FALSE;
        }
    }

    return TRUE;
}

static int IsFull(trie_node_t *root)
{
    assert(NULL != root);

    return (TRUE == root->is_full);
}

static int HasChild(trie_node_t *root, unsigned char dir)
{
    assert(NULL != root);

    return (NULL != root->children[dir]);
}