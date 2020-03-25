/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 23rd, 2020
	
	Description: Header file for Stack Data Structure.
		Takes in any data type as a void pointer. 
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.
		
		Consider for future implementations:
			- Linear memory allocation
			- Maximum Size
			- Stack size tracking
			- Data protection (Particularly with peek)
                · Considering making a copy of the data and return it when peeking

		  **** IMPORTANT ****
		FREE VARIABLES AFTER POP
*/


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _STACK_H_
#define _STACK_H_

typedef struct StackNode {
	void* data;
	size_t size;
	struct StackNode* nextNode;
}StackNode_t;

struct Stack {
	StackNode_t* top;
};

typedef struct Stack Stack_t;

/*
 * Initializes the Stack
 *
 * Takes in a Stack_t pointer. 
 * Initializes the pointer to the top node to NULL
 *
 * Returns the pointer to the stack
 */
Stack_t* stack_init(Stack_t*);

/*
 * Pops the top item from the stack.
 *
 * Takes in the stack. Removes the top of the stack and returns its data.
 *
 * Returns Null if the Stack is empty.
 * Otherwise it returns the data from the top of the stack.
 */
void* stack_pop(Stack_t*);

/*
 * Peeks the data from the top of the stack.
 *
 * Returns the data from the top of the stack
 */
void* stack_peek(Stack_t*);

/*
 * Peeks the data size of the data at the top of the stack.
 *
 * Returns the size in bytes of the data at the top.
 */
size_t stack_peek_dataSize(Stack_t*);

/*
 * Pushes some data into the the stack
 *
 * Takes in the stack, a void pointer to the data, and its size in bytes
 *
 * Returns -1 if the data failed to allocate/copy
 */
int stack_push(Stack_t*, void*, size_t);

/*
 * Checks if the stack is empty
 */
bool stack_isEmpty(Stack_t *);

/*
 * Deletes the stack
 */
void stack_deleteStack(Stack_t*);
#endif