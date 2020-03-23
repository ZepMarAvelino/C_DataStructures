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
	//Retrieve pointer of said address
	int half_size = (list->size / 2);
	DoublyLinked_Node_t* iter_ptr;

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
	if (list->size < 1) {
		return NULL;
	}
	void* data = list->head->data;
	list->head->next_node->prev_node = NULL;
	DoublyLinked_Node_t* temp = list->head->next_node;
	free(list->head);
	list->head = temp;
	list->size--;
	return data;
}

void* linkedlist_remove_tail(LinkedList_t* list) {
	if (list->size < 1) {
		return NULL;
	}
	void* data = list->tail->data;
	list->tail->prev_node->next_node = NULL;
	DoublyLinked_Node_t* temp = list->tail->prev_node;
	free(list->tail);
	list->tail = temp;
	list->size--;
	return data;
}

void* linkedlist_remove(LinkedList_t* list, int address) {
	if (list->size < 1) {
		return NULL;
	}

	DoublyLinked_Node_t* temp_ptr;

	//If address is greater than the size of the list
	if ((address >= (list->size - 1)) || (address == -1)) {
		temp_ptr = list->tail;
		list->tail = temp_ptr->prev_node;
		temp_ptr->prev_node->next_node = NULL;
	}
	//Using negative indexing and address is greater than size of the list OR address is equal to 0
	else if ((address <= (list->size) * -1) || (address == 0)) {
		temp_ptr = list->head;
		list->head = temp_ptr->next_node;
		temp_ptr->next_node->prev_node = NULL;
	}
	else {
		temp_ptr = linkedlist_retrieveAddr(list, address);	
		temp_ptr->prev_node->next_node = temp_ptr->next_node;
		temp_ptr->next_node->prev_node = temp_ptr->prev_node;
	}
	void* data = temp_ptr->data;
	
	free(temp_ptr);
	list->size--;
	return data;
}

void* linkedlist_peek(LinkedList_t* list, int address) {
	if (list->size < 1) {
		return NULL;
	}
	//Retrieve pointer of said address
	DoublyLinked_Node_t* iter_ptr;
	if ((address >= (list->size - 1)) || (address == -1)) {
		iter_ptr = list->tail;
	}
	else if ((address <= (list->size) * -1) || (address == 0)) {
		iter_ptr = list->head;
	}
	else {
		iter_ptr = linkedlist_retrieveAddr(list, address);
	}
	return iter_ptr->data;
}

size_t linkedlist_peek_dataSize(LinkedList_t* list, int address) {
	if (list->size < 1) {
		return 0;
	}
	//Retrieve pointer of said address
	DoublyLinked_Node_t* iter_ptr;
	if ((address >= (list->size - 1)) || (address == -1)) {
		iter_ptr = list->tail;
	}
	else if ((address <= (list->size) * -1) || (address == 0)) {
		iter_ptr = list->head;
	}
	else {
		iter_ptr = linkedlist_retrieveAddr(list, address);
	}

	return iter_ptr->size;
}