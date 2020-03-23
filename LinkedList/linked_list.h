/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 18th, 2020

	Description: Doubly Linked List Data Structure.
		Takes in any data type as a void pointer.
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.

		Consider for future implementations:
			- Linear memory allocation.
			- Data protection (Particularly with peek)
			- Garbage Collection

		  **** IMPORTANT ****
		FREE VARIABLES AFTER REMOVING
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

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

DoublyLinked_Node_t* linkedlist_initNode(void*, size_t);

DoublyLinked_Node_t* linkedlist_retrieveAddr(LinkedList_t*, int);

void* linkedlist_init(LinkedList_t*);

int linkedlist_add_head(LinkedList_t*, void*, size_t);

int linkedlist_add_tail(LinkedList_t*, void*, size_t);

int linkedlist_add(LinkedList_t*, void*, size_t, int);

void* linkedlist_remove_head(LinkedList_t*);

void* linkedlist_remove_tail(LinkedList_t*);

void* linkedlist_remove(LinkedList_t*, int);

void* linkedlist_peek(LinkedList_t*, int);

size_t linkedlist_peek_dataSize(LinkedList_t*, int);

#endif