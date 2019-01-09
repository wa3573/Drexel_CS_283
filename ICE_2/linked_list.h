/*
 * linked_list.h
 *
 *  Created on: Jan 6, 2019
 *      Author: Juniper
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct node_t node_t;

/*
 * node_t holds a pointer to data. Memory allocation for the data is up to the
 * user */
struct node_t {
	void* data;
	node_t* next;
	node_t* previous;
};

typedef struct list_t {
	node_t* head;
	node_t* tail;
	size_t element_size;
	unsigned int logical_length;
} list_t;

void list_init(list_t* list);
void list_free_node(node_t* node);
void list_push_front(list_t* list, void* data);
void list_push_back(list_t* list, void* data);
void list_insert_at_node(list_t* list, void* data, node_t* node);
void* list_front(list_t* list);
void* list_back(list_t* list);
void* list_pop_front(list_t* list);
void* list_pop_back(list_t* list);
void list_remove_node(list_t* list, node_t* node);
void list_destroy(list_t* list);

int list_compare_elements(list_t* list, void* lhs, void* rhs);
unsigned int list_size(list_t* list);
bool list_contains(list_t* list, void* data);
bool list_empty(list_t* list);
node_t* list_locate(list_t* list, void* data);
void list_print_int(list_t* list);

#endif /* LINKED_LIST_H_ */
