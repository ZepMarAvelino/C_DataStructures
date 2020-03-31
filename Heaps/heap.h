/*
	Author: Avelino Zepeda Martinez
	Date Created: March 25th, 2020
	Last Modified: March 25rd, 2020

	Description: Header file for Heap Data Structure.

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../BinaryTree/binary_tree.h"

#define HEAPIFY_UP 1
#define HEAPIFY_DOWN 0

#ifndef __HEAP_H__
#define __HEAP_H__

typedef BinaryTree_t Heap_t;

/*
 * Initializes the heap
 *
 * Takes in the maximum size of the heap, and function pointer.
 * The function expected is a comparison function. 
 * The comparison will dictate if it is a Min-Heap or a Max-Heap:
 * Min-Heap = Argument1 <= Argument2
 * Max-Heap = Argument1 >= Argument2
 *
 * This initializer allocates the array of tree nodes and returns the pointer to the heap.
 *
 */
Heap_t* heap_init(unsigned int, bool (*)(void*, void*));

/*
 * Creates a heap using the data from an array
 *
 * Takes in the pointer to the array, the length of the array, the size of the data in the array,
    the maximum size of the heap, and function pointer.
 * The function expected is a comparison function.
 * The comparison will dictate if it is a Min-Heap or a Max-Heap:
 * Min-Heap = Argument1 <= Argument2
 * Max-Heap = Argument1 >= Argument2
 * 
 * Returns a pointed to a new heap with the data. This heap will have to be freed
 */
Heap_t* heap_heapifyArray(void**, unsigned int, size_t, unsigned int, bool (*)(void*, void*));

/*
 * Takes the indices of two nodes in the heap and swaps them
 *
 * Takes in the heap, and the two indices of the nodes to be swaped
 *
 */
static void heap_swapNodes(Heap_t*, unsigned int, unsigned int);

/*
 * Balances the heap
 *
 * The balance function assumes that the only unbalanced nodes will be the root and the last leaf (rightmost)
 * This assumption is made becuase this heap should be balanced after each insertion and deletion
 * When creating the heap, the heap will insert each element and balance them one by one
 *
 */
static void heap_balance(Heap_t*, unsigned int);

/*
 * Inserts a new node into the heap
 *
 * Takes in the heap, the pointer to the data to add, and its size
 * The function inserts the data to the heap and then rebalances the heap
 * 
 * Returns -1 if the data failed to be allocated/copied
 * Returns -2 if the heap is full
 */
int heap_insert(Heap_t*, void*, size_t);

/*
 * Removes the root from the heap (Max or Min value depending on the comparison)
 *
 * Removes the root from the heap, then rebalances the heap.
 *
 * Returns a pointer to the data that the root contained
 */
void* heap_remove(Heap_t*);

/*
 * Retrieves the root of the heap (Max or Min value depending on the comparison)
 *
 * Returns a pointer to the data. If this pointer is modified it will modify the data in the heap.
 */
void* heap_peek(Heap_t*);

/*
 * Deletes the heap
 *
 * Frees the memory in the heap
 *
 */
void heap_delete(Heap_t*);

/*
 * Checks if the heap is empty
 *
 * Checks if the root is empty
 *
 * Returns a boolean
 */
bool heap_isEmpty(Heap_t*);

#endif