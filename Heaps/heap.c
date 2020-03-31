/*
	Author: Avelino Zepeda Martinez
	Date Created: March 25th, 2020
	Last Modified: March 25rd, 2020

	Description: Heap implementation in C
*/

#include "heap.h"

/*Pointer to store the function used to compare each node
 *
 * The comparison will dictate if it is a Min-Heap or a Max-Heap:
 * Min-Heap = Argument1 <= Argument2
 * Max-Heap = Argument1 >= Argument2
 *
 * The function must return a boolean type
 */
static bool (*heap_compare)(void*, void*) = NULL;

Heap_t* heap_init(unsigned int heap_size, bool (*callback_compareFunc)(void*, void*)) {
	//Initialize tree for the heap
	Heap_t* heap;
	heap = binaryTree_init(heap_size);

	//Store the compare function
	heap_compare = callback_compareFunc;
	return heap;
}

Heap_t* heap_heapifyArray(void** array, unsigned int arrayLength, size_t dataSize, unsigned int heap_size, bool (*callback_compareFunc)(void*, void*)) {
	//Initialize the heap
	Heap_t* heap;

	//If the given heap size is less than the array length, make the heap at minimum the array length
	if (arrayLength > heap_size) {
		heap_size = arrayLength;
	}
	heap = heap_init(heap_size, callback_compareFunc);

	for (unsigned int i = 1; i <= arrayLength; i++) {
		heap_insert(heap, &array[i], dataSize);
	}
	return heap;
}

static void heap_swapNodes(Heap_t* heap, unsigned int node1, unsigned int node2) {
	//Use the empty node at index 0 as a temporary node to hold data from node1
	heap->nodeArray[0].data = heap->nodeArray[node1].data;
	heap->nodeArray[0].data_size = heap->nodeArray[node1].data_size;

	//Move data from node2 to node1
	heap->nodeArray[node1].data = heap->nodeArray[node2].data;
	heap->nodeArray[node1].data_size = heap->nodeArray[node2].data_size;

	//Move data from temporary node to node2
	heap->nodeArray[node2].data = heap->nodeArray[0].data;
	heap->nodeArray[node2].data_size = heap->nodeArray[0].data_size;

	//Empty temporary node
	heap->nodeArray[0].data = NULL;
	heap->nodeArray[0].data_size = 0;
}

static void heap_balance(Heap_t* heap, unsigned int operationType) {
	unsigned int node_idx;
	//If heapifying up (after inserting element)
	if (operationType == 1) {
		//Initialize indices
		node_idx = heap->num_nodes;
		int parent_idx = binaryTree_getParent(heap, node_idx);
		//While the parent is still within the boundaries and the comparison between nodes is true
		while ((parent_idx > 0) && (heap_compare(heap->nodeArray[node_idx].data, heap->nodeArray[parent_idx].data))) {
			heap_swapNodes(heap, node_idx, parent_idx);
			node_idx = parent_idx;
			parent_idx = binaryTree_getParent(heap, node_idx);
		}
	}
	//Heapifying down (after removing element)
	else {
		//Initialize indices
		node_idx = 1;
		int left_idx = binaryTree_getLeftChild(heap, node_idx);
		int right_idx = binaryTree_getRightChild(heap, node_idx);
		//While the node has children
		while (binaryTree_hasChildren(heap, node_idx)) {
			//Check if the right child is empty
			if (heap->nodeArray[right_idx].data == NULL) {
				//If the left child is offending
				if (heap_compare(heap->nodeArray[left_idx].data, heap->nodeArray[node_idx].data)) {
					heap_swapNodes(heap, node_idx, left_idx);
					node_idx = left_idx;
					left_idx = binaryTree_getLeftChild(heap, node_idx);
					right_idx = binaryTree_getRightChild(heap, node_idx);
				}
				//Otherwise we have achieved "balance"
				else {
					break;
				}
			}
			else {
				//First compare the children to see which one will be more suitable to be swapped up
				if (heap_compare(heap->nodeArray[left_idx].data, heap->nodeArray[right_idx].data)) {
					//If the left child is offending
					if (heap_compare(heap->nodeArray[left_idx].data, heap->nodeArray[node_idx].data)) {
						heap_swapNodes(heap, node_idx, left_idx);
						node_idx = left_idx;
						left_idx = binaryTree_getLeftChild(heap, node_idx);
						right_idx = binaryTree_getRightChild(heap, node_idx);
					}
					//Otherwise we have achieved "balance"
					else {
						break;
					}
				}
				else {
					//If the right child is offending
					if (heap_compare(heap->nodeArray[right_idx].data, heap->nodeArray[node_idx].data)) {
						heap_swapNodes(heap, node_idx, right_idx);
						node_idx = right_idx;
						left_idx = binaryTree_getLeftChild(heap, node_idx);
						right_idx = binaryTree_getRightChild(heap, node_idx);
					}
					//Otherwise we have achieved "balance"
					else {
						break;
					}
				}
			}
		}
	}
}

int heap_insert(Heap_t* heap, void* srcData, size_t dataSize) {
	//Insert data to tree
	int result = binaryTree_insert(heap, srcData, dataSize);

	//If the data was inserted to the tree successfully, then heapify up (balance)
	if (result >= 0) {
		heap_balance(heap, HEAPIFY_UP);
	}
	return result;
}

void* heap_remove(Heap_t* heap) {
	//Retrieve the data from the root
	void* data = heap->nodeArray[1].data;

	//Move last node into the position of the root
	heap->nodeArray[1].data = heap->nodeArray[heap->num_nodes].data;
	heap->nodeArray[1].data_size = heap->nodeArray[heap->num_nodes].data_size;

	//Empty the index of the last node
	heap->nodeArray[heap->num_nodes].data = NULL;
	heap->nodeArray[heap->num_nodes].data_size = 0;
	//Decrease the number of nodes in the heap
	heap->num_nodes--;

	//Heapify Down
	heap_balance(heap, HEAPIFY_DOWN);
	//Return the data
	return data;
}

void* heap_peek(Heap_t* heap) {
	//If heap is empty
	//Redundant??
	if (heap_isEmpty(heap)) {
		return NULL;
	}
	return heap->nodeArray[1].data;
}

void heap_delete(Heap_t* heap) {
	binaryTree_deleteTree(heap);
}

bool heap_isEmpty(Heap_t* heap) {
	return binaryTree_isEmpty(heap);
}
