/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 23rd, 2020

	Description: Stack implementation in C
*/

#include "stack.h"

Stack_t* stack_init(Stack_t* stack) {
	//Initialize the top of the stack to NULL
	stack->top = NULL;
	return stack;
}

void* stack_pop(Stack_t* stack) {
	//If the stack is empty return NULL
	if (stack_isEmpty(stack)) {
		return NULL;
	}

	////Retrieve the data
	void* data = stack->top->data;
	//Retrieve pointer of the new top
	StackNode_t* ptr = stack->top->nextNode;
	//Free old top stack node
	free(stack->top);
	//Point to the new top of the stack
	stack->top = ptr;
	return data;
}

void* stack_peek(Stack_t* stack) {
	//If the stack is empty return NULL
	if (stack_isEmpty(stack)) {
		return NULL;
	}
	return stack->top->data;
}

size_t stack_peek_dataSize(Stack_t* stack) {
	//Returns the data size of the data at the top of the stack
	return stack->top->size;
}

int stack_push(Stack_t* stack, void* srcData, size_t size) {
	//Copy Data
	void* stackData = malloc(size);
	if (stackData == NULL) {
		return -1;
	}
	memcpy(stackData, srcData, size);

	//Create Node
	StackNode_t* newNode = (StackNode_t*) malloc(sizeof(StackNode_t));
	newNode->data = stackData;
	newNode->size = size;

	//Insert Node
	newNode->nextNode = stack->top;
	stack->top = newNode;

	return 0;
}

bool stack_isEmpty(Stack_t* stack) {
	//If the top of the stack points to NULL
	if (stack->top == NULL) {
		return true;
	}
	return false;
}

void stack_deleteStack(Stack_t* stack) {
	//While the stack has values, free the stack node at the top
	while (!stack_isEmpty(stack)) {
		free(stack_pop(stack));
	}
	free(stack);
}