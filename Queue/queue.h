/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 18th, 2020

	Description: Queue Data Structure.
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

#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct QueueNode {
	struct QueueNode* next_Node;
	void* data;
	size_t size;
}QueueNode_t;

typedef struct Queue {
	QueueNode_t* head;
	QueueNode_t* tail;
}Queue_t;

Queue_t* queue_init(Queue_t*);

void* queue_peek(Queue_t*);

void* dequeue(Queue_t*);

int enqueue(Queue_t*, void*, size_t);

bool queue_isEmpty(Queue_t*);

#endif