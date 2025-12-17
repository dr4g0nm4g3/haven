/*
 * avl.h
 *	implementation of an AVL tree
 *
 *	An AVL tree is a self-balancing binary search tree. The
 *	heights of the two sub trees of any node always differs by 1.
 *
 *  Created on: Mar 15, 2009
 *      Author: dragon
 */

#ifndef AVL_H_
#define AVL_H_

/**
 * data structure that represents each node of an AVL tree
 */
typedef struct avl_node
{
	struct avl_node_t * child[2];		// left and right child nodes
	struct avl_node_t * parent;			// parent node
	unsigned char child_index;			// which of the parent's children nodes are we, left or right?
	signed char balance_factor;		// {-1, 0, 1}
	void * data;						// pointer to user-defined data
} avl_node_t;

/**
 * data structure that represents the AVL tree
 */
typedef struct avl_tree
{
	avl_node_t * root;								// root node of the AVL tree
	int (* compare)(const void *, const void *);	// compare function that must return either -1, 0, or 1
	void (* destroy)(void * data);					// function that deallocates the data stored in the avl nodes
	unsigned long num_nodes;						// number of nodes in the AVL tree
} avl_tree_t;

typedef int (* fn_compare)(const void *, const void *);
typedef void (* fn_destroy)(void * data);


#define AVL_RIGHT_HEAVY 	-1
#define AVL_BALANCED		0
#define AVL_LEFT_HEAVY		1
/*
 * Direction constants used for avl_find_nearest().
 */
#define AVL_BEFORE	(0)
#define AVL_AFTER	(1)

/**
 * define to test subtree balance
 */
#define IsBalanced(n) (n->balance_factor == 0)

/**
 * default_compare - default implementation of the compare_func predicate
 *
 * returns -1, 0, or 1
 */
//static int default_compare(const void * p1, const void * p2);

/**
 * create_avl - create an AVL tree
 *
 * param[in/out] tree pointer to an avl_tree_t struct
 * param[in] compare_func function pointer that will be called when comparing nodes
 * param[in] cmp_data function pointer used when searching for user-defined data in AVL nodes
 */
void create_avl(avl_tree_t * tree,
					int(* compare)(const void *, const void *));

/**
 * avl_insert - insert a node into the avl tree
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] data pointer to user-defined data to insert into the AVL tree
 */
void avl_insert(avl_tree_t * tree, void * data);

/**
 * avl_insert_after - insert the node after the avl node supplied
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] data pointer to user-defined data to insert into the AVL tree
 * param[in] after_node pointer to avl_node_t where 'node' should be inserted after
 */
void avl_insert_after(avl_tree_t * tree, void * data, avl_node_t * after_node);

/**
 * avl_insert_before - insert the node before the avl node supplied
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] data pointer to user-defined data to insert into the AVL tree
 * param[in] before_node pointer to avl_node_t where 'node' should be inserted before
 */
void avl_insert_before(avl_tree_t * tree, void * data, avl_node_t * before_node);

/**
 * avl_find - find an AVL node with the given data
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] data pointer to user defined data to search for in the AVL tree
 * return NULL if the node containing the data could not be found
 * return a pointer to an avl_node_t struct pointing to the node with the data
 */
avl_node_t * avl_find(avl_tree_t * tree, void * data);

/**
 * avl_find_nearest - find an AVL node closest to the given data
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] data pointer to user defined data to search for in the AVL tree
 * param[in] direction search for nearest left (AVL_BEFORE), or right (AVL_AFTER)
 * return NULL if no node was found
 * return pointer to avl_node_t struct if a node was found
 */
avl_node_t * avl_find_nearest(avl_tree_t * tree, void * data, int direction);

/**
 * avl_next - return the next node, given a starting node
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] node pointer to starting node
 * return NULL if there are no more nodes
 * return a pointer to an avl_node_t struct pointing to the next node in the AVL tree
 */
avl_node_t * avl_next(avl_tree_t * tree, avl_node_t * node);

/**
 * avl_prev - return the previous node, given a starting node
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] node pointer to starting node
 * return NULL if there are no more nodes
 * return a pointer to an avl_node_t struct pointing to the previous node in the AVL tree
 */
avl_node_t * avl_prev(avl_tree_t * tree, avl_node_t * node);

/**
 * avl_remove - remove the node
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * param[in] data pointer to user-defined data to remove from the AVL tree
 */
void avl_remove(avl_tree_t * tree, void * data);

/**
 * avl_num_nodes - return the number of nodes in the tree
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * return the number of nodes in the AVL tree
 */
unsigned long avl_num_nodes(avl_tree_t * tree);

/**
 * avl_first - returns the lowest valued node of the AVL tree
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * return NULL if there are no more nodes
 * return a pointer to an avl_node_t struct
 */
avl_node_t * avl_first(avl_tree_t * tree);

/**
 * avl_last - returns the highest valued node of the AVL tree
 *
 * param[in] tree pointer to an avl_tree_t data structure
 * return NULL if there are no more nodes
 * return a pointer to an avl_node_t struct
 */
avl_node_t * avl_last(avl_tree_t * tree);

/**
 * avl_destroy - destroy the AVL tree
 *
 * param[in] tree pointer to an avl_tree_t data structure
 */
void avl_destroy(avl_tree_t * tree);


#endif /* AVL_H_ */
