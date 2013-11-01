/* pedlist.c : Implementation of the linked list structure 
 * written by CHU Yimin
 * University of Tokyo
 * pedlistnode, pedlist : the node and the list of the structure
*/

#include "pedlist.h"
#include <stdlib.h>

pedlistnode * initialize_list_node (pedlistnode * node, void * content) {
	if (node == NULL)
		return NULL;
	else {
		node->content = content;
		node->next = NULL;
		return node;
	}
}

void finalize_node(pedlistnode *node) {
	if (node->content != NULL) {
		free(node->content);
		node->content = NULL;
	}
	free(node);
}

pedlist * initialize_list (pedlist *list) {
	if (list == NULL)
		return NULL;
	else {
		list->head = NULL;
		list->tail = NULL;
		return list;
	}
}

pedlist * append_node_to_list (pedlist * list, pedlistnode * tail_node) {
	if (list == NULL)
		return NULL;
	if (list->head == NULL) {
		list->head = tail_node;
		list->tail = tail_node;
		return list;
	}
	else {
		list->tail->next = tail_node;
		list->tail = tail_node;
		return list;
	}
}

void free_pedlist (pedlist *list) {
	pedlistnode * pointer, *tbdel;
	if (list == NULL)
		return;
	else {
		while(list->head != NULL) {
			pointer = list->head;
			list->head = pointer->next;
			finalize_node (pointer);
			free (pointer);
		}
		list->tail = NULL;
		return;
	}
}

