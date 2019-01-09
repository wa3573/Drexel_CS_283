/*
 * main.c
 *
 *  Created on: Jan 6, 2019
 *      Author: Juniper
 */

#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
	list_t* list_1 = (list_t*) malloc(sizeof(list_t));
	list_t list_2;

	list_init(list_1);
	list_init(&list_2);

	assert(list_empty(list_1));
	assert(list_empty(&list_2));

	assert(list_size(list_1) == 0);
	assert(list_size(&list_2) == 0);

	static int static_item[10];
	for (int i = 0; i < 10; ++i) {
		static_item[i] = i;
		list_push_back(list_1, &static_item[i]);
		list_push_front(&list_2, &static_item[i]);
	}

	assert(!list_empty(list_1));
	assert(!list_empty(&list_2));

	assert(list_size(list_1) == 10);
	assert(list_size(&list_2) == 10);

	list_print_int(list_1);
	list_print_int(&list_2);

	for (int i = 0; i < 10; ++i) {
		static_item[i] = i;
		list_pop_back(list_1);
		list_pop_front(&list_2);
	}

	assert(list_empty(list_1));
	assert(list_empty(&list_2));

	assert(list_size(list_1) == 0);
	assert(list_size(&list_2) == 0);

	list_print_int(list_1);
	list_print_int(&list_2);

	for (int i = 0; i < 10; ++i) {
		static_item[i] = i;
		list_push_back(list_1, &static_item[i]);
		list_push_front(&list_2, &static_item[i]);
	}

	node_t* node_5_1 = list_locate(list_1, &static_item[5]);
	node_t* node_5_2 = list_locate(&list_2, &static_item[5]);
	node_t* node_2_2 = list_locate(&list_2, &static_item[2]);

	printf("\nRemoving node corresponding to static_item[5] from list_1...\n");
	list_remove_node(list_1, node_5_1);

	printf("\nRemoving nodes corresponding to static_item[5] and [2] from list_2...\n\n");
	list_remove_node(&list_2, node_5_2);
	list_remove_node(&list_2, node_2_2);

	assert(!list_empty(list_1));
	assert(!list_empty(&list_2));

	assert(list_size(list_1) == 9);
	assert(list_size(&list_2) == 8);

	list_print_int(list_1);
	list_print_int(&list_2);

	list_destroy(list_1);
}
