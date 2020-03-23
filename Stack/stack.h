/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 18th, 2020
	
	Description: Stack Data Structure.
		Takes in any data type as a void pointer. 
		It is the developers responsibility to keep track of the data type used.
		Modifying the data referenced to by the pointers WILL modify the data in the stack. Some resource management needs to be implemented.
		
		Consider for future implementations:
			- Linear memory allocation.
			- Data protection (Particularly with peek)
			- Garbage Collection

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

Stack_t* stack_init(Stack_t*);

void* stack_pop(Stack_t*);

void* stack_peek(Stack_t*);

size_t stack_peek_dataSize(Stack_t*);

int stack_push(Stack_t*, void*, size_t);

bool stack_isEmpty(Stack_t *);

#endif