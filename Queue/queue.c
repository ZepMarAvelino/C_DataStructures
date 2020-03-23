#include "queue.h"

Queue_t* queue_init(Queue_t* queue) {
	queue->head = NULL;
	queue->tail = NULL;
	return queue;
}

void* queue_peek(Queue_t* queue) {
	if (queue_isEmpty(queue)) {
		return NULL;
	}
	return queue->head->data;
}

void* dequeue(Queue_t* queue) {
	if (queue_isEmpty(queue)) {
		return NULL;
	}
	QueueNode_t* temp = queue->head;
	void* data = temp->data;

	queue->head = temp->next_Node;
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
	if (queue->head == NULL) {
		return true;
	}
	return false;
}