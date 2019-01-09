/*
 * linked_list.c
 *
 *  Created on: Jan 6, 2019
 *      Author: Juniper
 */

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


void list_init(list_t* list) {
	list->head = (node_t*) malloc(sizeof(node_t));
	list->tail = (node_t*) malloc(sizeof(node_t));

	if (list->head == NULL || list->tail == NULL) {
		fprintf(stderr, "list_init(): failed to allocate memory\n");
	}

	list->logical_length = 0;
	list->head->next = list->tail;
	list->head->previous = NULL;
	list->tail->next = NULL;
	list->tail->previous = list->head;
}

void list_free_node(node_t* node) {
	free(node);
}

void list_push_front(list_t* list, void* data) {
	node_t* new_node = (node_t*) malloc(sizeof(node_t));
	new_node->data = data;
	new_node->previous = list->head;

	node_t* old_node = list->head->next;

	list->head->next = new_node;
	new_node->previous = list->head;
	new_node->next = old_node;
	old_node->previous = new_node;
	list->logical_length++;
}

void list_push_back(list_t* list, void* data) {
	node_t* new_node = (node_t*) malloc(sizeof(node_t));
	new_node->data = data;
	new_node->next = list->tail;

	node_t* old_node = list->tail->previous;

	old_node->next = new_node;
	new_node->previous = old_node;
	new_node->next = list->tail;
	list->tail->previous = new_node;
	list->logical_length++;
}

void list_insert_at_node(list_t* list, void* data, node_t* node) {
	node_t* new_node = (node_t*) malloc(sizeof(node_t));
	new_node->data = data;
	new_node->previous = list->head;

	node_t* temp = node->next;

	node->next = new_node;
	new_node->previous = node;
	new_node->next = temp;

	if (temp != NULL) {
		temp->previous = new_node;
	}

	list->logical_length++;
}

void* list_front(list_t* list) {
	return list->head->data;
}

void* list_back(list_t* list) {
	return list->tail->data;
}

void* list_pop_front(list_t* list) {
	if (list_empty(list)) {
		return NULL;
	}

	node_t* temp = list->head->next;
	void* result = temp->data;
	node_t* next = temp->next;

	list->head->next = next;
	next->previous = list->head;

	list_free_node(temp);
	list->logical_length--;

	return result;
}

void* list_pop_back(list_t* list) {
	if (list->tail == list->head) {
		return NULL;
	}

	node_t* temp = list->tail->previous;
	void* result = temp->data;
	node_t* previous = temp->previous;

	list->tail->previous = previous;
	previous->next = list->tail;

	list_free_node(temp);
	list->logical_length--;

	return result;

}

void list_remove_node(list_t* list, node_t* node) {
	if (node == list->head) {
		return;
	} else if (node == list->tail) {
		return;
	} else {
		node_t* temp = node;
		node_t* previous = temp->previous;
		node_t* next = temp->next;

		previous->next = next;
		next->previous = previous;

		list_free_node(temp);
		list->logical_length--;
	}
}

void list_destroy(list_t* list) {
	node_t* p = list->head->next;
	node_t* temp;

	while (p != NULL) {
		temp = p;
		p = p->next;
		list_free_node(temp);
	}

	list_free_node(list->head);
	free(list);
}

int list_compare_elements(list_t* list, void* lhs, void* rhs) {
	/* Simply compares memory locations since type is unknown */

	if (lhs < rhs) {
		return -1;
	} else if (lhs > rhs) {
		return 1;
	}

	return 0;
}

unsigned int list_size(list_t* list) {
	return list->logical_length;
}

bool list_contains(list_t* list, void* data) {
	bool result = false;

	node_t* current_node = list->head->next;

	while (current_node->next != NULL)
	{
		if (list_compare_elements(list, current_node->data, data) == 0) {
			result = true;
			break;
		}

		current_node = current_node->next;
	}

	return result;
}

bool list_empty(list_t* list) {
	if (list->head->next == list->tail) {
		return true;
	}

	return false;
}

node_t* list_locate(list_t* list, void* data) {
	node_t* result = NULL;

	node_t* current_node = list->head->next;

	while (current_node->next != NULL)
	{
		if (list_compare_elements(list, current_node->data, data) == 0) {
			result = current_node;
			break;
		}

		current_node = current_node->next;
	}

	return result;
}

void list_print_int(list_t* list) {
	node_t* current_node = list->head->next;

	printf("NULL<-[head]->");
	while (current_node != list->tail) {
		printf("<-[%d]->", *((int*)current_node->data));
		current_node = current_node->next;
	}

	printf("<-[tail]->NULL\n");
}


