#include "stack.h"

Stack_t* stack_init(Stack_t* stack) {
	stack->top = NULL;
	return stack;
}

void* stack_pop(Stack_t* stack) {
	if (stack_isEmpty(stack)) {
		return NULL;
	}

	void* data = stack->top->data;
	StackNode_t* ptr = stack->top->nextNode;
	free(stack->top);
	stack->top = ptr;
	return data;
}

void* stack_peek(Stack_t* stack) {
	if (stack_isEmpty(stack)) {
		return NULL;
	}
	return stack->top->data;
}

size_t stack_peek_dataSize(Stack_t* stack) {
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
	if (stack->top == NULL) {
		return true;
	}
	return false;
}