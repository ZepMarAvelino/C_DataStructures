/*
	Author: Avelino Zepeda Martinez
	Date Created: March 21st, 2020
	Last Modified: March 23rd, 2020

	Description: Sequential Binary Tree implementation in C
*/

#include "binary_tree.h"

BinaryTree_t* binaryTree_init(unsigned int treeSize) {
	BinaryTree_t* tree = malloc(sizeof(BinaryTree_t));
	if (tree == NULL) {
		return NULL;
	}
	//Allocate the memory for the nodes, leaving the node at index 0 empty
	tree->nodeArray = malloc(sizeof(BinaryTreeNode_t) * (treeSize + 1));
	if (tree->nodeArray == NULL) {
		return NULL;
	}

	tree->tree_size = treeSize;
	tree->num_nodes = 0;

	//Initialize each node
	for (unsigned int i = 0; i <= treeSize; i++) {
		tree->nodeArray[i].data = NULL;
		tree->nodeArray[i].data_size = 0;
	}
	return tree;
}

size_t binaryTree_getDataSize(BinaryTree_t* tree, unsigned int index) {
	//Check if the index is out of bounds
	if ((index > tree->tree_size) || index == 0) {
		return 0;
	}
	return tree->nodeArray[index].data_size;
}

int binaryTree_getLeftChild(BinaryTree_t* tree, unsigned int index) {
	//Check if the index is out of bounds
	if ((index > tree->tree_size) || (index == 0)) {
		return -1;
	}
	unsigned int left_idx = (2 * index);
	//If the left child is out of bounds
	if (left_idx > tree->tree_size) {
		return -2;
	}
	return left_idx;
}

int binaryTree_getRightChild(BinaryTree_t* tree, unsigned int index) {
	//Check if the index is out of bounds
	if ((index > tree->tree_size) || (index == 0)) {
		return -1;
	}
	unsigned int right_idx = (2 * index) + 1;
	//if the Right child is out of bounds
	if (right_idx > tree->tree_size) {
		return -2;
	}
	return right_idx;
}

bool binaryTree_hasChildren(BinaryTree_t* tree, unsigned int index) {
	//Check if the index is out of bounds
	if ((index > tree->tree_size) || (index == 0)) {
		return false;
	}

	//Obtain indices of the children
	int left = binaryTree_getLeftChild(tree, index);
	int right = binaryTree_getRightChild(tree, index);
	//If the children are out of bounds
	if ((left < 1) && (right < 1)) {
		return false;
	}
	//If the children are empty
	if ((tree->nodeArray[left].data == NULL) && (tree->nodeArray[right].data == NULL)){
		return false;
	}
	return true;
}

int binaryTree_getParent(BinaryTree_t* tree, unsigned int index) {
	//Check if the index is out of bounds
	if ((index > tree->tree_size) || (index <= 1)) {
		return -1;
	}
	return index / 2;
}

int binaryTree_search(BinaryTree_t* tree, void* data, size_t searchSize){
	//If tree is empty (no root) return -1
	if (binaryTree_isEmpty(tree)) {
		return -1;
	}

	/*Iterate through all the nodes until the data is found or until we reach the end of the tree
	*
	*
	* NEED TO ADD LOGIC TO AVOID ITERATING PAST LEAVES.
	*/
	unsigned int index = 1;
	while (index <= tree->tree_size) {
		//If the node is empty, skip it
		if (tree->nodeArray[index].data == NULL) {
			++index;
			continue;
		}
		//If the data in the current node does not match the size of the data we are looking for, skip it
		if (tree->nodeArray[index].data_size != searchSize) {
			++index;
			continue;
		}
		else {
			bool equal = true;
			char* idx_data = (char*)tree->nodeArray[index].data;
			char* search_data = (char*)data;
			//Check if the data is the same (does not check if the data is of the same type, just if it is the same size)
			for (unsigned int i = 0; i < searchSize; ++i) {
				if (idx_data[i] != search_data[i]) {
					equal = false;
					++index;
					break;
				}
			}
			//If it is the same data, return the index.
			if (equal == true) {
				return index;
			}
		}
	}
	//If the data is not found, return -1
	return -1;
}

void* binaryTree_deleteNode(BinaryTree_t* tree, unsigned int index) {
	//Check for index out of bounds
	if ((index > tree->tree_size) || (index == 0)) {
		return NULL;
	}

	//Retrieve pointer to the value in the tree
	void* value = tree->nodeArray[index].data;

	//If the node does not have children
	if (!binaryTree_hasChildren(tree, index)) {
		tree->nodeArray[index].data = NULL;
		tree->nodeArray[index].data_size = 0;
	}
	//If it has children, then shift them up
	else {
		int current_idx = index;
		int previous_idx = index;
		//While the current node has children. This should then ensure that there are no nodes without a parent.
		while (binaryTree_hasChildren(tree, current_idx)) {
			previous_idx = current_idx;
			//If the current node has a right child. Shift that child up.
			if ((binaryTree_getRightChild(tree, current_idx) > 0) && (tree->nodeArray[binaryTree_getRightChild(tree, current_idx)].data != NULL)) {
				current_idx = binaryTree_getRightChild(tree, current_idx);
			}
			//Else the shift the left child.
			else {
				current_idx = binaryTree_getLeftChild(tree, current_idx);
			}
			tree->nodeArray[previous_idx].data = tree->nodeArray[current_idx].data;
			tree->nodeArray[previous_idx].data_size = tree->nodeArray[current_idx].data_size;
			tree->nodeArray[current_idx].data = NULL;
			tree->nodeArray[current_idx].data_size = 0;
		}
	}
	//Decrease the number of nodes in the tree
	tree->num_nodes--;
	return value;
}

void* binaryTree_deleteValue(BinaryTree_t* tree, void* value, size_t dataSize) {
	//Find the index of the value
	int index = binaryTree_search(tree, value, dataSize);
	//If the value does not exist in the tree, return NULL
	if (index < 1) {
		return NULL;
	}

	//Delete the value by index
	return binaryTree_deleteNode(tree, index);
}

int binaryTree_insert(BinaryTree_t* tree, void* srcValue, size_t dataSize) {
	//Make a copy of the data
	void* dstValue = malloc(dataSize);
	if (dstValue == NULL) {
		return -1;
	}
	memcpy(dstValue, srcValue, dataSize);

	//Search the for the leftmost highest level empty node and insert the value in it
	for (unsigned int index = 1; index <= tree->tree_size; ++index) {
		if (tree->nodeArray[index].data == NULL) {
			tree->nodeArray[index].data = dstValue;
			tree->nodeArray[index].data_size = dataSize;
			tree->num_nodes++;
			return 0;
		}
	}
	
	//Tree is full
	return -2;
}

int binaryTree_insertByIndex(BinaryTree_t* tree, void* srcValue, size_t dataSize, unsigned int index) {
	//Make a copy of the data
	void* dstValue = malloc(dataSize);
	if (dstValue == NULL) {
		return -1;
	}
	memcpy(dstValue, srcValue, dataSize);

	//Retrieve the children's indices
	int left = binaryTree_getLeftChild(tree, index);
	int right = binaryTree_getRightChild(tree, index);

	//If the left child index is not out of bounds
	if (left > 0) {
		//Check if the left child is empty and insert the node if it is
		if (tree->nodeArray[left].data == NULL) {
			tree->nodeArray[left].data = dstValue;
			tree->nodeArray[left].data_size = dataSize;
			tree->num_nodes++;
			return 0;
		}
		//If the right child is not out of bounds
		else if (right > 0) {
			//Check if the right child is empty
			if (tree->nodeArray[right].data == NULL) {
				tree->nodeArray[right].data = dstValue;
				tree->nodeArray[right].data_size = dataSize;
				tree->num_nodes++;
				return 0;
			}
			//The given index has both children already assigned
			else {
				return -3;
			}
		}
		//The children are out of bounds
		else {
			return -2;
		}
	}
	//If the left child is out of bounds, so will be the right child
	else {
		return -2;
	}
}

bool binaryTree_isEmpty(BinaryTree_t* tree) {
	if ((tree->nodeArray[1].data == NULL) && (tree->nodeArray[1].data_size == 0)) {
		return true;
	}
	return false;
}

static void binaryTree_printRecursion(BinaryTree_t* tree, unsigned int index, unsigned int levels) {
	if (index > tree->tree_size) {
		printf("Out of bounds\n");
		return;
	}
	else if (tree->nodeArray[index].data == NULL) {
		printf("Empty\n");
		return;
	}
	else {
		printf("Index = %d. %d Bytes. Pointing to %p\n", index,tree->nodeArray[index].data_size, tree->nodeArray[index].data);
		if (binaryTree_hasChildren(tree, index)) {
			for (unsigned int i = 1; i <= levels; ++i) {
				printf("--->");
			}
			printf("Left: ");
			binaryTree_printRecursion(tree, binaryTree_getLeftChild(tree, index), levels + 1);
			for (unsigned int i = 1; i <= levels; ++i) {
				printf("--->");
			}
			printf("Right: ");
			binaryTree_printRecursion(tree, binaryTree_getRightChild(tree, index), levels + 1);
		}
		return;
	}
}

void binaryTree_print(BinaryTree_t* tree) {
	unsigned int index = 1;
	unsigned int levels = 1;
	printf("Tree with %d nodes\n", tree->num_nodes);
	printf("Root: ");
	binaryTree_printRecursion(tree, index, levels);
}

void binaryTree_deleteTree(BinaryTree_t* tree) {
	//Iterate through each element in the array and free the memory
	printf("Deleting\n");
	for (unsigned int index = 0; index <= tree->tree_size; index++) {
		free(tree->nodeArray[index].data);
	}
	printf("Deleting Node Array\n");
	//Free the memory dedicated to the array
	free(tree->nodeArray);
	free(tree);
}
