/* pedlist.c : Implementation of the linked list structure 
 * written by CHU Yimin
 * University of Tokyo
 * pedlistnode, pedlist : the node and the list of the structure
*/

#include "pedlist.h"
#include <stdlib.h>

pedlistnode * init_node (pedlistnode * node, void * content) {
	pedlistnode * newnode;
	if (node == NULL)
		newnode = (pedlistnode *) malloc(sizeof(pedlistnode));
	else {
		newnode = node;
	}
		newnode->content = content;
		newnode->next = NULL;
		return newnode;
}

void finalize_node(pedlistnode *node) {
	if (node->content != NULL) {
		node->content = NULL;
	}
	free(node);
}

pedlist * init_list (pedlist *list) {
	pedlist *newlist;
	if (list == NULL)
		newlist = (pedlist *)malloc(sizeof(pedlist));
	else {
		newlist = list;
	}
		newlist->head = NULL;
		newlist->tail = NULL;
		return newlist;
}

pedlist * append_node_to_list (pedlist * list, pedlistnode * tail_node) {
	pedlist * reslist;
	if (list == NULL)
		reslist = init_list(NULL);
	else
		reslist = list;
	if (reslist->head == NULL) {
		reslist->head = tail_node;
		reslist->tail = tail_node;
		return reslist;
	}
	else {
		reslist->tail->next = tail_node;
		reslist->tail = tail_node;
		return reslist;
	}
}

void finalize_list (pedlist *list) {
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
