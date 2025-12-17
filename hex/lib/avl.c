/*
 * avl.c
 * AVL tree implementation
 *
 *  Created on: Mar 17, 2009
 *      Author: dragon
 */

#include "avl.h"
#include "kmm.h"

/**
 * avl_rotate - rotate the AVL tree to balance it
 *
 * param[in] tree AVL tree to rotate
 * param[in] node the AVL node at which to start balancing
 * param[in] balance balance factor at 'node'
 * return 0 if the subtree did not change height
 * return -1 if the left side was reduced in height
 * return 1 if the right side was reduced in height
 */
static int avl_rotate(avl_tree_t * tree, avl_node_t * node, int balance)
{
	return 0;
}

static int default_compare(const void * p1, const void * p2)
{
	if(p1 == p2)
		return 0;
	else if(p1 < p2)
		return -1;
	else
		return 1;
}

void create_avl(avl_tree_t * tree,
					int(* compare)(const void *, const void *))
{
	if(tree == 0)
		return;

	tree->root = 0;
	tree->compare = compare;
	tree->num_nodes = 0;

	// if no function pointers were passed in, use default comparison functions
	if(tree->compare == 0)
		tree->compare = (fn_compare)default_compare;

}

unsigned long avl_num_nodes(avl_tree_t * tree)
{
	if(tree == 0)
		return 0;

	return tree->num_nodes;
}

void avl_destroy(avl_tree_t * tree)
{
	if(tree != 0)
	{
		tree->num_nodes = 0;
		tree->root = 0;
		tree = 0;
	}
}

avl_node_t * avl_find(avl_tree_t * tree, void * data)
{
	if(tree == 0)
		return (avl_node_t *)0;

	avl_node_t * node = tree->root;
	while(node && node->data != data)
	{
		int direction = tree->compare(data, node->data);
		if(direction == 0)
			return node;

		int index = (direction == -1)?0:1;
		node = (avl_node_t *)node->child[index];
	}

	return node;
}

void avl_insert(avl_tree_t * tree, void * data)
{
	if(tree == 0)
		return;

	avl_node_t * node = kmalloc(sizeof(avl_node_t));

	//TODO: zero memory

	node->data = data;

	// handle empty tree case
	if(tree->root == 0)
	{
		tree->root = node;
		tree->num_nodes++;
		return;
	}

	avl_node_t * parent = tree->root;
	if(parent->child[0] != 0)
	{	// we have found a left child node
		for(parent = (avl_node_t *)parent->child[0];
			parent->child[0] != 0;
			parent = (avl_node_t *)parent->child[0])
		{	// traverse down the left until there are no more nodes
			;
		}
		// insert node at end of traversal
		int balance = tree->compare(data, parent->data);
		int index = (balance == -1)?0:1;
		parent->child[index] = (struct avl_node_t *)node;
		node->parent = (struct avl_node_t *)parent;
		node->child_index = index;
		tree->num_nodes++;
	}

	avl_rotate(tree, node, 0);
}

void avl_remove(avl_tree_t * tree, void * data)
{

}
