/* pedlist.h : Interface of the linked list structure 
 * written by CHU Yimin
 * University of Tokyo
 * pedlistnode, pedlist : the node and the list of the structure
*/

#ifndef __PEDLIST
#define __PEDLIST

typedef struct _pedlistnode {
	void * content;
	struct _pedlistnode * next;
} pedlistnode;

typedef struct _pedlist {
	pedlistnode *head;
	pedlistnode *tail;
} pedlist;

pedlistnode * initialize_list_node (pedlistnode * node, void * content);
void finalize_node(pedlistnode *node);

pedlist * initialize_list (pedlist * list);

pedlist * append_node_to_list(pedlist * list, pedlistnode * tail_node);

void free_pedlist (pedlist * list);

#endif
