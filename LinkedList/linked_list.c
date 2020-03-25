/*
	Author: Avelino Zepeda Martinez
	Date Created: March 18th, 2020
	Last Modified: March 23rd, 2020

	Description: Doubly Linked List implementation in C
*/

#include "linked_list.h"

DoublyLinked_Node_t* linkedlist_initNode(void* srcData, size_t size) {
	//Copy Data
	void* nodeData = malloc(size);
	if (nodeData == NULL) {
		return NULL;
	}
	memcpy(nodeData, srcData, size);

	//Initialize Node
	DoublyLinked_Node_t* linkedNode = (DoublyLinked_Node_t*)malloc(sizeof(DoublyLinked_Node_t));
	linkedNode->data = nodeData;
	linkedNode->size = size;

	return linkedNode;
}

DoublyLinked_Node_t* linkedlist_retrieveAddr(LinkedList_t* list, int address) {
	int half_size = (list->size / 2);
	DoublyLinked_Node_t* iter_ptr;

	//Retrieve pointer of said address
	//First the determine the shortest way to retrieve it
	//If using positive indexing
	if (address >= 0) {
		//Decide if traverse from head or tail 
		if (address <= half_size) {
			iter_ptr = list->head;
			for (int i = 0; i < address; ++i) {
				iter_ptr = iter_ptr->next_node;
			}
		}
		else {
			iter_ptr = list->tail;
			for (int i = (list->size - 1); i > address; --i) {
				iter_ptr = iter_ptr->prev_node;
			}
		}
	}
	//If using negative indexing
	else {
		//Decide if traverse from head or tail 
		if ((address * -1) <= half_size) {
			iter_ptr = list->tail;
			for (int i = -1; i > address; --i) {
				iter_ptr = iter_ptr->prev_node;
			}
		}
		else {
			iter_ptr = list->head;
			for (int i = (-1) * list->size; i < address; ++i) {
				iter_ptr = iter_ptr->next_node;
			}
		}
	}
	return iter_ptr;
}

void* linkedlist_init(LinkedList_t* list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}

int linkedlist_add_head(LinkedList_t* list, void* srcData, size_t size) {
	
	DoublyLinked_Node_t* linkedNode = linkedlist_initNode(srcData, size);
	if (linkedNode == NULL) {
		return -1;
	}
	
	//Insert into the list
	if (list->size == 0) {
		linkedNode->next_node = NULL;
		linkedNode->prev_node = NULL;
		list->head = linkedNode;
		list->tail = linkedNode;
	}
	else {
		linkedNode->next_node = list->head;
		linkedNode->prev_node = NULL;
		list->head->prev_node = linkedNode;
		list->head = linkedNode;
	}

	list->size++;
	return 0;
}

int linkedlist_add_tail(LinkedList_t* list, void* srcData, size_t size) {

	DoublyLinked_Node_t* linkedNode = linkedlist_initNode(srcData, size);
	if (linkedNode == NULL) {
		return -1;
	}

	//Insert into the list
	if (list->size == 0) {
		linkedNode->next_node = NULL;
		linkedNode->prev_node = NULL;
		list->head = linkedNode;
		list->tail = linkedNode;
	}
	else {
		linkedNode->next_node = NULL;
		linkedNode->prev_node = list->tail;
		list->tail->next_node = linkedNode;
		list->tail = linkedNode;
	}

	list->size++;
	return 0;

}

int linkedlist_add(LinkedList_t* list, void* srcData, size_t size, int address) {

	DoublyLinked_Node_t* linkedNode = linkedlist_initNode(srcData, size);
	if (linkedNode == NULL) {
		return -1;
	}

	//Insert into the list
	//If list is empty
	if (list->size == 0) {
		linkedNode->next_node = NULL;
		linkedNode->prev_node = NULL;
		list->head = linkedNode;
		list->tail = linkedNode;
	}
	//If address is greater than the size of the list
	else if((address >= (list->size - 1)) || (address == -1)){
		linkedNode->next_node = NULL;
		linkedNode->prev_node = list->tail;
		list->tail->next_node = linkedNode;
		list->tail = linkedNode;
	}
	//Using negative indexing and address is greater than size of the list OR address is equal to 0
	else if((address <= (list->size)*-1) || (address == 0)){
		linkedNode->next_node = list->head;
		linkedNode->prev_node = NULL;
		list->head->prev_node = linkedNode;
		list->head = linkedNode;
	}
	//Retrieve the node currently sitting at the address
	else {
		DoublyLinked_Node_t* iter_ptr = linkedlist_retrieveAddr(list, address);
		//Insert the Node
		linkedNode->next_node = iter_ptr;
		linkedNode->prev_node = iter_ptr->prev_node;
		iter_ptr->prev_node->next_node = linkedNode;
		iter_ptr->prev_node = linkedNode;
	}
	list->size++;
	return 0;
}

void* linkedlist_remove_head(LinkedList_t* list) {
	//If the list is empty
	if (list->size < 1) {
		return NULL;
	}
	//Retrieve the data
	void* data = list->head->data;
	//Remove pointer of old head from the list
	list->head->next_node->prev_node = NULL;
	//Retrieve pointer of new head
	DoublyLinked_Node_t* temp = list->head->next_node;
	//Free node of the old head
	free(list->head);
	//Point head of list to new head
	list->head = temp;
	//Decrease size
	list->size--;
	return data;
}

void* linkedlist_remove_tail(LinkedList_t* list) {
	//If list is empty
	if (list->size < 1) {
		return NULL;
	}
	//Retrieve the data
	void* data = list->tail->data;
	//Remove pointer of old tail from the list
	list->tail->prev_node->next_node = NULL;
	//Retrieve pointer of new tail
	DoublyLinked_Node_t* temp = list->tail->prev_node;
	//Free node of the old tail
	free(list->tail);
	//Point tail of list to new tail
	list->tail = temp;
	//Decrease list size
	list->size--;
	return data;
}

void* linkedlist_remove(LinkedList_t* list, int address) {
	//If the list is empty
	if (list->size < 1) {
		return NULL;
	}

	DoublyLinked_Node_t* temp_ptr;

	//If address is greater than the size of the list when using positive indexing, or address is -1 remove the tail
	if ((address >= (list->size - 1)) || (address == -1)) {
		temp_ptr = list->tail;
		list->tail = temp_ptr->prev_node;
		temp_ptr->prev_node->next_node = NULL;
	}
	//Using negative indexing and address is greater than size of the list OR address is equal to 0 remove the head
	else if ((address <= (list->size) * -1) || (address == 0)) {
		temp_ptr = list->head;
		list->head = temp_ptr->next_node;
		temp_ptr->next_node->prev_node = NULL;
	}
	//Otherwise retrieve the pointer to the list, and remove the node
	else {
		temp_ptr = linkedlist_retrieveAddr(list, address);	
		temp_ptr->prev_node->next_node = temp_ptr->next_node;
		temp_ptr->next_node->prev_node = temp_ptr->prev_node;
	}

	//Retrieve the data
	void* data = temp_ptr->data;
	//Free node
	free(temp_ptr);
	//Decrease size of list
	list->size--;
	return data;
}

void* linkedlist_peek(LinkedList_t* list, int address) {
	//If the list is empty
	if (list->size < 1) {
		return NULL;
	}
	//Retrieve pointer of said address
	DoublyLinked_Node_t* iter_ptr;
	//If the address is the tail
	if ((address >= (list->size - 1)) || (address == -1)) {
		iter_ptr = list->tail;
	}
	//If the address is the head
	else if ((address <= (list->size) * -1) || (address == 0)) {
		iter_ptr = list->head;
	}
	//Retrieve the pointer
	else {
		iter_ptr = linkedlist_retrieveAddr(list, address);
	}
	return iter_ptr->data;
}

size_t linkedlist_peek_dataSize(LinkedList_t* list, int address) {
	//If the list is empty
	if (list->size < 1) {
		return 0;
	}
	//Retrieve pointer of said address
	DoublyLinked_Node_t* iter_ptr;
	//If the address is the tail
	if ((address >= (list->size - 1)) || (address == -1)) {
		iter_ptr = list->tail;
	}
	//If the address is the head
	else if ((address <= (list->size) * -1) || (address == 0)) {
		iter_ptr = list->head;
	}
	//Otherwise retrieve the pointer
	else {
		iter_ptr = linkedlist_retrieveAddr(list, address);
	}
	return iter_ptr->size;
}