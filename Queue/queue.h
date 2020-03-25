/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 23rd, 2020


	Description: Header file for Queue Data Structure.
		Takes in any data type as a void pointer.
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.

		Consider for future implementations:
			- Data protection (Particularly with peek)

		  **** IMPORTANT ****
		FREE VARIABLES AFTER DEQUEUEING
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct QueueNode {
	struct QueueNode* next_Node;
	void* data;
	size_t size;
}QueueNode_t;

typedef struct Queue {
	QueueNode_t* head;
	QueueNode_t* tail;
}Queue_t;

/*
 * Initializes the queue pointers to NULL
 *
 * Takes in a Queue_t pointer
 *
 * Returns a pointer to the initialized Queue
 */
Queue_t* queue_init(Queue_t*);

/*
 * Checks what is the data at the front of the queue
 *
 * Takes in the queue
 *
 * Modifying the return the value will change the data in the queue.
 * Further resources management needed
 *
 * Returns a void* to the data
 */
void* queue_peek(Queue_t*);

/*
 * Removes the element at the head/front of the queue
 *
 * Takes in the queue. 
 *
 * RETURN VALUE MUST BE FREED
 *
 * Returns a void* to the data
 */
void* dequeue(Queue_t*);

/*
 * Inserts a new value to the end of the queue
 *
 * Takes in the queue, a void* to the data, and the size of said data
 *
 * Returns -1 if it failed to copy/allocate the data
 */
int enqueue(Queue_t*, void*, size_t);

/*
 * Checks if the queue is empty.
 *
 * If the head node points to NULL it assumes the queue is empty
 *
 * Returns a boolean
 */
bool queue_isEmpty(Queue_t*);

#endif