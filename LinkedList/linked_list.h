/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 23rd, 2020

	Description: Header file for Doubly Linked List Data Structure.
		Takes in any data type as a void pointer.
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.

		Consider for future implementations:
			- Linear memory allocation.
			- Data protection (Particularly with peek)
			- Compare function
			- Circular Doubly Linked List
			- Maximum size

		  **** IMPORTANT ****
		FREE VARIABLES AFTER REMOVING
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct DoublyLinked_Node {
	struct DoublyLinked_Node* prev_node;
	struct DoublyLinked_Node* next_node;
	void* data;
	size_t size;
}DoublyLinked_Node_t;

typedef struct Linked_List {
	DoublyLinked_Node_t* head;
	DoublyLinked_Node_t* tail;
	int size;
}LinkedList_t;

/*
 * Initializes the list node
 *
 * Takes in the data and its datasize
 *
 * Returns a pointer to the initialized Node
 */
DoublyLinked_Node_t* linkedlist_initNode(void*, size_t);

/*
 * Looks for the node at said index and returns it
 *
 * Accepts possitive and negative indices. Retrieves the node at said index.
 *
 * If the index is out of bounds it will return the head or the tail (depending on the polarity of the index)
 */
DoublyLinked_Node_t* linkedlist_retrieveNode(LinkedList_t*, int);

/*
 * Initializes the list
 *
 * Points the head and tail to Null and sets the size to 0
 *
 * returns a pointer to the list
 */
void* linkedlist_init(LinkedList_t*);

/*
 * Adds the data to a node at the head of the list
 *
 * Takes in the list, a pointer to the data, and the size to the data
 *
 * Returns -1 if the node fails to be initialized
 */
int linkedlist_add_head(LinkedList_t*, void*, size_t);

/*
 * Adds the data to a node at the tail of the list
 *
 * Takes in the list, a pointer to the data, and the size to the data
 *
 * Returns -1 if the node fails to be initialized
 */
int linkedlist_add_tail(LinkedList_t*, void*, size_t);

/*
 * Adds the data to a node at the head of the list
 *
 * Takes in the list, a pointer to the data, the size to the data,
 *  and the index where the node is to be inserted
 * Accepts possitive and negative index
 *
 * Returns -1 if the node fails to be initialized
 */
int linkedlist_add(LinkedList_t*, void*, size_t, int);

/*
 * Removes the head of the list
 *
 * Takes in the List.
 *
 * Returns NUll if the list is empty, otherwise it returns a pointer to the data
 * Data needs to be freed after using it
 */
void* linkedlist_remove_head(LinkedList_t*);

/*
 * Removes the tail of the list
 *
 * Takes in the List.
 *
 * Returns NUll if the list is empty, otherwise it returns a pointer to the data
 * Data needs to be freed after using it
 */
void* linkedlist_remove_tail(LinkedList_t*);

/*
 * Removes the head of the list
 *
 * Takes in the List and the index of the node to be removed
 * Accepts positive and negative indexing
 *
 * Returns NUll if the list is empty, otherwise it returns a pointer to the data
 * Data needs to be freed after using it
 */
void* linkedlist_remove(LinkedList_t*, int);

/*
 * Retrieves the value of the node without deleting it
 *
 * Takes in the list and the index to observe
 * Accepts postive and negative indexing
 * Modifying the data from the pointer will affect the data in the list
 *  Resource management needed
 *
 * Returns a pointer to the data in the list
 */
void* linkedlist_peek(LinkedList_t*, int);

/*
 * Retrieves the data size of the data stored in the node at a given index
 *
 * Takes in the list and the index to observe
 * Accepts postive and negative indexing
 *
 * Returns the size in bytes of the data stored at said node
 */
size_t linkedlist_peek_dataSize(LinkedList_t*, int);

#endif