/************************************************ 
EXERCISE      : Binary Search Tree
Implmented by : Snir Holland
Reviewed by   : Amitai Bar
Date          : 4/6/23
File          : bst.c
*************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free*/

#include "bst.h"

/* Child Position */ 
typedef enum child_pos
{
	LEFT,
	RIGHT,
	NUM_OF_CHILDREN
} child_pos_t;

/* BST node */
typedef struct bst_node
{
	void *data;
	struct bst_node *children[NUM_OF_CHILDREN];
	struct bst_node *parent;
} bst_node_t;

/* Managerial struct */
struct bst
{
	bst_node_t root_stub;
	bst_cmp_func_t cmp;
};

/* action/match function status */
enum func_status 
{
	SUCCESS,
	FAILURE
};

/* static functions */
static bst_node_t *IterToNodePtr(bst_iter_t iter);
static bst_iter_t NodePtrToIter(bst_node_t *node);
static bst_node_t *ExtremeLeafInSubtree(bst_node_t *node, child_pos_t pos);
static void CleanUp(bst_node_t *node);
static bst_node_t *TraverseByOrder(bst_t *bst, void *data, child_pos_t *direction);
static child_pos_t GetChildPos(bst_node_t *node);
static int HasNoChildren(bst_node_t *node);
static int HasLeftChild(bst_node_t *node);
static int HasRightChild(bst_node_t *node);
static int HasTwoChildren(bst_node_t *node);
static bst_node_t *GetRoot(const bst_t *bst);
static bst_node_t *GetLeftChild(bst_node_t *node);
static bst_node_t *GetRightChild(bst_node_t *node);
static bst_node_t *GetParent(bst_node_t *node);
static int CountNodes(void *tree, void *counter);

/*-------------- BSTCreate --------------*/
bst_t *BSTCreate(bst_cmp_func_t cmp)
{
	bst_t *bst = NULL;

	assert(NULL != cmp);

	bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		return NULL;
	}
 
	CleanUp(&bst->root_stub);
	
	bst->cmp = cmp;
	
	return bst;
}

/*-------------- BSTNext --------------*/
bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_node_t *node = NULL;

	assert(NULL != iter);

	node = IterToNodePtr(iter);

	if (HasRightChild(node))    
	{
		bst_node_t *successor = NULL;

		/* go down from right son and find node with minimum value in the tree rooted in node */
		successor = ExtremeLeafInSubtree(GetRightChild(node), LEFT);
		
		return NodePtrToIter(successor);
	}

	/* node has a parent: go up and find the parent which is the left son of his parent */
	while ((NULL != GetParent(node))  &&  (LEFT != GetChildPos(node)))  
	{
		node = GetParent(node);
	}

	return NodePtrToIter(GetParent(node));
}

/*-------------- BSTPrev --------------*/
bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_node_t *node = NULL;

	assert(NULL != iter);

	node = IterToNodePtr(iter);

	if (HasLeftChild(node))    
	{
		bst_node_t *predecessor = NULL;

		/* go down from left son and find node with maximum value in the tree rooted in node */
		predecessor = ExtremeLeafInSubtree(GetLeftChild(node), RIGHT);
		
		return NodePtrToIter(predecessor);
	}

	/* node has a parent: go up and find the parent which is the right son of his parent */
	while ((NULL != GetParent(node))  &&  (RIGHT != GetChildPos(node)))
	{
		node = GetParent(node);
	}

	return NodePtrToIter(GetParent(node));
}

/*-------------- BSTGetBegin --------------*/
bst_iter_t BSTGetBegin(const bst_t *bst)
{
	bst_node_t *node = NULL;
	bst_node_t *begin = NULL;

	assert(NULL != bst);

	node = GetLeftChild(GetRoot(bst));

	begin = ExtremeLeafInSubtree(node, LEFT);
	
	return NodePtrToIter(begin);
}	

/*-------------- BSTGetEnd --------------*/
bst_iter_t BSTGetEnd(const bst_t *bst)
{
	assert(NULL != bst);

	return NodePtrToIter(GetRoot(bst));
}	

/*-------------- BSTDestroy --------------*/
void BSTDestroy(bst_t *bst)
{
	bst_node_t *runner = NULL;
	bst_node_t *temp = NULL;

	assert (NULL != bst);

	runner = GetLeftChild(GetRoot(bst));

	/* Destroy in post order traversal */
	while (!BSTIsEmpty(bst))
	{ 
		if (HasLeftChild(runner))
		{
			runner = GetLeftChild(runner);
			continue;
		}

		if (HasRightChild(runner))
		{
			runner = GetRightChild(runner);
			continue;
		}
		
		temp = runner;
		runner = GetParent(runner);
		BSTRemove(NodePtrToIter(temp));		
	}

	free(bst);
	bst = NULL;
}

/*-------------- BSTIsSameIter --------------*/
int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);

	return (IterToNodePtr(iter1) == IterToNodePtr(iter2));
}

/*-------------- BSTSize --------------*/
size_t BSTSize(const bst_t *bst)
{
	size_t counter = 0;
	
	assert(NULL != bst);

	if (!BSTIsEmpty(bst))
	{
		BSTForEach(BSTGetBegin(bst), BSTGetEnd(bst) , &CountNodes, &counter);
	}

	return counter;
}

/*-------------- BSTGetData --------------*/
void *BSTGetData(bst_iter_t iter)
{
	bst_node_t *node = NULL;

	assert(NULL != iter);

	node = IterToNodePtr(iter);

	return node->data;
}

/*-------------- BSTIsEmpty --------------*/
int BSTIsEmpty(const bst_t *bst)
{
	assert(NULL != bst);

	return (NULL == GetLeftChild(GetRoot(bst)));
}

/*-------------- BSTInsert --------------*/
bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_node_t *new_node = NULL;
	bst_node_t *parent_of_new = NULL;
	child_pos_t position_to_insert = LEFT;

	assert(NULL != bst);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return BSTGetEnd(bst);
	}
	
	/* initialization of new iter data and children */
	CleanUp(new_node);
	new_node->data = data;
	
	parent_of_new = TraverseByOrder(bst, data, &position_to_insert);
	
	parent_of_new->children[position_to_insert] = new_node;

	new_node->parent = parent_of_new;

	return NodePtrToIter(new_node);
}

/*-------------- BSTRemove --------------*/
void BSTRemove(bst_iter_t iter)
{
	bst_node_t *node = NULL;

	assert(NULL != iter);

	node = IterToNodePtr(iter);

	if (HasNoChildren(node))
	{
		node->parent->children[GetChildPos(node)] = NULL;
	}

	else if (HasTwoChildren(node))
	{
		bst_node_t *successor = IterToNodePtr(BSTNext(NodePtrToIter(node)));  
		node->data = successor->data;

		successor->parent->children[GetChildPos(successor)] = NULL;

		free(successor);
		successor = NULL;
		
		return;
	}

	else /* has only one child */
	{
		/* find position of node's child*/
		child_pos_t pos = (HasLeftChild(node)) ? LEFT : RIGHT;

		/* connect node's father with his grandson */
		node->parent->children[GetChildPos(node)] = node->children[pos];
		node->children[pos]->parent = node->parent;
	}
	
	/* all cases except two children */
	free(node);
	node = NULL;
}

/*-------------- BSTFind --------------*/
bst_iter_t BSTFind(const bst_t *bst, void *data)
{
	child_pos_t pos = LEFT;
	bst_node_t *result = NULL;

	assert(NULL != bst);

	result = TraverseByOrder((bst_t *)bst, data, &pos);

	return (0 == bst->cmp(data, result->data)) ? result : BSTGetEnd(bst);
}

/*-------------- BSTForEach --------------*/
int BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_func_t func, void *param)
{
	bst_iter_t runner = NULL;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != func);

	runner = from;
	while (!BSTIsSameIter(runner, to))
	{
		if (FAILURE == func(BSTGetData(runner) , param))
		{
			return FAILURE;
		}
		runner = BSTNext(runner);	
	}

	return SUCCESS;
}
/* -----------End of functions------------ */

/* Helper function: transforms iter to node pointer */
static bst_node_t *IterToNodePtr(bst_iter_t iter)
{
	return (bst_node_t *)iter;
}

/* Helper function: transforms node pointer to iter */
static bst_iter_t NodePtrToIter(bst_node_t *node)
{
	return (bst_iter_t)node;
}

/* Helper function: finds extreme (min/max) value in subtree rooted in node */
static bst_node_t *ExtremeLeafInSubtree(bst_node_t *node, child_pos_t pos)
{
	bst_node_t *runner = NULL;

	assert(NULL != node);
	assert(LEFT == pos || RIGHT == pos);

	runner = node;
	while (NULL != runner->children[pos])
	{
		runner = runner->children[pos];
	}

	return IterToNodePtr(runner); 		
}

/* Helper function: returns child's position (left/right) */
static child_pos_t GetChildPos(bst_node_t *node)
{
	assert(NULL != node);

	return (node == node->parent->children[LEFT]) ? LEFT : RIGHT;
}

/* Helper function: returns true if node has a left child */
static int HasLeftChild(bst_node_t *node)
{
	assert(NULL != node);

	return (NULL != node->children[LEFT]);
}

/* Helper function: returns true if node has a right child */
static int HasRightChild(bst_node_t *node)
{
	assert(NULL != node);

	return (NULL != node->children[RIGHT]);
}

/* Helper function: returns true if node has two children */
static int HasTwoChildren(bst_node_t *node)
{
	assert(NULL != node);

	return (HasLeftChild(node) && HasRightChild(node));
}

/* Helper function: returns true if node has no children */
static int HasNoChildren(bst_node_t *node)
{
	assert(NULL != node);

	return (!HasLeftChild(node) && !HasRightChild(node));	
}

/* Helper function: clean node */
static void CleanUp(bst_node_t *node)
{
	size_t i = 0;

	assert(NULL != node);

	node->data = NULL;
	for(i=0; i<NUM_OF_CHILDREN; ++i)
	{
		node->children[i] = NULL;
	}
	node->parent = NULL;
}

/* Helper function: Travels down the tree while comparing data */
static bst_node_t *TraverseByOrder(bst_t *bst, void *data, child_pos_t *direction)
{
	bst_node_t *runner = NULL;
	bst_node_t *runner_parent = NULL;
	int cmp_result = 0;

	assert(NULL != bst);
	assert(NULL != data);

	*direction = LEFT;

	runner = (bst_node_t *)(&bst->root_stub);
	if (!HasLeftChild(runner))
	{
		return runner;
	}

	runner = runner->children[LEFT];
	while(NULL != runner) 
	{
		runner_parent = runner;

		cmp_result = bst->cmp(data, runner->data); 
		
		if (0 == cmp_result)
		{
			return runner;
		}

		*direction = (cmp_result < 0)  ?  LEFT  :  RIGHT;

		runner = runner->children[*direction];
	}
	
	return runner_parent;
}

/* Helper function: Count nodes in the tree */
static int CountNodes(void *tree, void *counter)
{
	++(*(size_t *)counter);
	(void)tree;
	return SUCCESS;
}

/* Helper function: Returns the root of the tree */
static bst_node_t *GetRoot(const bst_t *bst)
{
	assert (NULL != bst);

	return (bst_node_t*)&bst->root_stub;
}

/* Helper function: Returns the left child of node */
static bst_node_t *GetLeftChild(bst_node_t *node)
{
	assert(NULL != node);

	return node->children[LEFT];
}

/* Helper function: Returns the right child of node */
static bst_node_t *GetRightChild(bst_node_t *node)
{
	assert(NULL != node);

	return node->children[RIGHT];
}

/* Helper function: Returns the parent of node */
static bst_node_t *GetParent(bst_node_t *node)
{
	assert(NULL != node);

	return node->parent;
}