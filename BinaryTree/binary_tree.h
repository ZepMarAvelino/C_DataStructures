/*
	Author: Avelino Zepeda Martinez
	Date Created: March 21st, 2020
	Last Modified: March 23rd, 2020


	Description: Header file for Sequential Binary Tree Data Structure.
		Sequential Binary Tree (Array of void* pointing to Tree Nodes)
		Takes in any data type as a void pointer.
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.

		Consider for future implementations:
			- Compare Functions (Currently comparing byte by byte when the size_t are equal)
			- Tracking of the number of nodes in the tree

		  **** IMPORTANT ****
		FREE VARIABLES AFTER POP
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef struct BinaryTreeNode {
	void* data;
	size_t data_size;
}BinaryTreeNode_t;

typedef struct BinaryTree {
	BinaryTreeNode_t* nodeArray;
	unsigned int tree_size; // Max size of the tree
    unsigned int num_nodes; // Current number of nodes in the tree
}BinaryTree_t;

/*
 * Initializes a Binary Tree.
 *
 * Takes in the size of the desired tree.
 * Allocates the memory for it, and initializes each node in the tree to a NULL pointer.
 *
 * Returns a pointer to the same tree.
 */
BinaryTree_t* binaryTree_init(unsigned int);

/*
 * Used to retrieve the data size of the node at a given index.
 *
 * Takes in a pointer to a tree and the index of the node we want to look at.
 * If the index is out of bounds it will return a size 0.
 *
 * Returns the size of the data at which the node is pointing to.
 */
size_t binaryTree_getDataSize(BinaryTree_t*, unsigned int);

/*
 * Used to calculate the array index of the left child of a given node
 *
 * Takes in the tree and an index.
 * If the index is out of bounds it will return a negative number.
 *
 * Returns the index of the left child given an index.
 * Returns -1 if the input index is out bounds
 * Returns -2 if the resulting index is out of bounds
 */
int binaryTree_getLeftChild(BinaryTree_t*, unsigned int);

/*
 * Used to calculate the array index of the right child of a given node.
 *
 * Takes in the tree and an index.
 * If the index is out of bounds it will return a negative number.
 *
 * Returns the index of the right child given an index.
 * Returns -1 if the input index is out bounds
 * Returns -2 if the resulting index is out of bounds
 */
int binaryTree_getRightChild(BinaryTree_t*, unsigned int);

/*
 * Used to see if a given node has children associated to it.
 *
 * Takes in the tree and an index.
 * If the index is out of bounds it returns false.
 * If the index of both its children are out of bounds it returns false
 * If any of the children has data it returns true.
 *
 * Returns boolean
 */
bool binaryTree_hasChildren(BinaryTree_t* tree, unsigned int);

/*
 * Used to calculate the array index of the parent of a given node.
 *
 * Takes in the tree and an index.
 * If the index is out of bounds it will return a negative number.
 *
 * Returns the index of the parent given an index.
 */
int binaryTree_getParent(BinaryTree_t*, unsigned int);

/*
 * Used to search for a value in the tree
 *
 * If the tree is empty, it returns a negative number.
 * Iterates through each node, looking for the value.
 * If the value in the node is of a different datatype size it ignores it.
 * If the node is empty, it skips it.
 * Comparison is done byte by byte.
 *
 * Returns the index of the node in which the value is found. Otherwise it returns a negative number.
 */
int binaryTree_search(BinaryTree_t*, void*, size_t);

/*
 * Used to delete a node given an index.
 *
 * If the index is out of bounds it returns NULL.
 * If the node has both left and right children it shift the right child up, otherwise it shifts the left child.
 * This is repeated for all nodes under the deleted node. This is to avoid any parentless nodes.
 *
 * Returns the pointer to the data originally stored in the node.
 * THIS NEEDS TO BE FREED AFTER USING IT.
 */
void* binaryTree_deleteNode(BinaryTree_t*, unsigned int);

/*
 * Used to delete a node given a value.
 *
 * Uses the search function to find the index, and then uses the deleteNode function to delete teh node.
 *
 * Returns the pointer to the data originally stored in the node.
 * THIS NEEDS TO BE FREED AFTER USING IT.
 */
void* binaryTree_deleteValue(BinaryTree_t*, void*, size_t);

/*
 * Inserts a node in the topmost/leftmost open spot of the tree.
 *
 * Takes in the tree, a pointer to the data to insert, and the size of it.
 *
 * Returns -1 if the data fails to be allocated/copied
 * Returs -2 if the tree is full.
 */
int binaryTree_insert(BinaryTree_t*, void*, size_t);

/*
 * Inserts a node as a child to the given node
 *
 * If the node has both children, it does not allocate the data.
 * Allocates the data to the left child if both children are empty.
 *
 * Returns -1 if the data fails to be allocated/copied
 * Returns -2 if the children are out of bounds
 * Returns -3 if both children are already assigned
 */
int binaryTree_insertByIndex(BinaryTree_t*, void*, size_t, unsigned int);

/*
 * Checks if the tree is empty
 *
 * Checks if the root is empty, if so the tree is empty
 *
 * Returns a boolean
 */
bool binaryTree_isEmpty(BinaryTree_t*);

/*
 * Used by print to iterate through each branch
 */
static void binaryTree_printRecursion(BinaryTree_t*, unsigned int, unsigned int);

/*
 * Prints the tree.
 *
 * Prints the index of the node, the number of bytes the data uses, and the address.
 */
void binaryTree_print(BinaryTree_t*);

/*
 * Deletes the tree.
 *
 * Frees all the memory in the tree.
 */
void binaryTree_deleteTree(BinaryTree_t*);
#endif