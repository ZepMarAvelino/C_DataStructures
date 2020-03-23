/*
	Author: Avelino Zepeda Martinez
	Date Created: March 21st, 2020
	Last Modified: March 23rd, 2020


	Description: Sequential Binary Tree Data Structure.
		Takes in any data type as a void pointer.
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.

		Consider for future implementations:
			- Data protection (Particularly with peek)
			- Garbage Collection

		  **** IMPORTANT ****
		FREE VARIABLES AFTER POP
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

typedef struct BinaryTreeNode {
	void* data;
	size_t data_size;
}BinaryTreeNode_t;

typedef struct BinaryTree {
	BinaryTreeNode_t* nodeArray;
	unsigned int tree_size;
}BinaryTree_t;

BinaryTree_t* binaryTree_init(BinaryTree_t*, unsigned int);

size_t binaryTree_getDataSize(BinaryTree_t*, unsigned int);

int binaryTree_getLeftChild(BinaryTree_t*, unsigned int);

int binaryTree_getRightChild(BinaryTree_t*, unsigned int);

int binaryTree_hasChildren(BinaryTree_t* tree, unsigned int);

int binaryTree_getParent(BinaryTree_t*, unsigned int);

int binaryTree_search(BinaryTree_t*, void*, size_t);

void* binaryTree_deleteNode(BinaryTree_t*, unsigned int);

void* binaryTree_deleteValue(BinaryTree_t*, void*, size_t);

int binaryTree_insert(BinaryTree_t*, void*, size_t);

int binaryTree_insertByIndex(BinaryTree_t*, void*, size_t, unsigned int);

bool binaryTree_isEmpty(BinaryTree_t*);

void binaryTree_printRecursion(BinaryTree_t*, unsigned int, unsigned int);

void binaryTree_print(BinaryTree_t*);
#endif