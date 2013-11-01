/* Pedphrase.h : the interface of pedphrase
 * written by CHU Yimin
 * University of Tokyo
 * pedphrase : a set of neighbouring pedchars. contains the information of font, bounding box, and a list of characters
*/

#include "pedphrase.h"
#include <stdlib.h>

pedphrase * initialize_phrase(pedphrase * phrase) {
	if (phrase == NULL)
		return NULL;
	phrase->chars = (pedlist *)malloc(sizeof(pedlist));
	initialize_list(phrase->chars);
	phrase->length = 0;
	initialize_box(&(phrase->boundingbox));
	phrase->font = NULL;
	phrase->dir = PEDDIRECT_UNSET;
	return phrase;
}

int add_character_to(pedphrase *phrase, pedchar *t) {
	pedlistnode * node;
	if (phrase == NULL)
		return NULL;
	node = (pedlistnode *)malloc(sizeof(pedlistnode));
	node = initialize_list_node(node, (void *)t);
	append_node_to_list(phrase->chars, node);
	if (phrase->len == 0 ) {
		phrase->font = t->font;
		initialize_box(&(phrase->boundingbox), t->boundingbox.x0, t->boundingbox.y0, t->boundingbox.x1, t->boundingbox.y1);
		phrase->len = 1;
		return phrase->len;
	}
	else {
		grow_box(&(phrase->boundingbox), &(t->boundingbox));
		phrase->len = phrase->len + 1;
		return phrase->len;
	}
}

PED_BOOL is_space_phrase (pedphrase * phrase) {
	PED_BOOL tag;
	pedlistnode * node;
	
	tag = PED_FALSE;

	
}
