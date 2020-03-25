/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 23rd, 2020

	Description: Queue implementation in C
*/

#include "queue.h"

Queue_t* queue_init(Queue_t* queue) {
	//Initializes queue to point to NULL locations
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

void* queue_peek(Queue_t* queue) {
	//If the queue is empty, return NULL
	if (queue_isEmpty(queue)) {
		return NULL;
	}
	//Return a pointer to the data
	return queue->head->data;
}

void* dequeue(Queue_t* queue) {
	//If the queue is empty, return NULL
	if (queue_isEmpty(queue)) {
		return NULL;
	}
	//Retrieve the data
	QueueNode_t* temp = queue->head;
	void* data = temp->data;

	//Point to new head node
	queue->head = temp->next_Node;
	//Free the node object
	free(temp);
	return data;
}

int enqueue(Queue_t* queue, void* srcData, size_t size) {
	//Copy Data
	void* queueData = malloc(size);
	if (queueData == NULL) {
		return -1;
	}
	memcpy(queueData, srcData, size);

	//Create Node
	QueueNode_t* newNode = (QueueNode_t*)malloc(sizeof(QueueNode_t));
	newNode->data = queueData;
	newNode->size = size;
	newNode->next_Node = NULL;

	//Insert Node
	if (queue_isEmpty(queue)) {
		queue->head = newNode;
		queue->tail = newNode;
	}
	else {
		queue->tail->next_Node = newNode;
		queue->tail = newNode;
	}
	return 0;
}

bool queue_isEmpty(Queue_t* queue) {
	//If the head of the queue is NULL
	if (queue->head == NULL) {
		return true;
	}
	return false;
}