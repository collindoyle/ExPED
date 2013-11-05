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
	initialize_box(&(phrase->boundingbox), 0, 0, 0,0);
	phrase->font = NULL;
	phrase->dir = PEDDIRECT_UNSET;
	return phrase;
}

int add_character_to(pedphrase *phrase, pedchar *t) {
	pedlistnode * node;
	if (phrase == NULL)
		return 0;
	node = (pedlistnode *)malloc(sizeof(pedlistnode));
	node = initialize_list_node(node, (void *)t);
	append_node_to_list(phrase->chars, node);
	if (phrase->length == 0 ) {
		phrase->font = t->pfont;
		initialize_box(&(phrase->boundingbox), t->boundingbox.x0, t->boundingbox.y0, t->boundingbox.x1, t->boundingbox.y1);
		phrase->length = 1;
		return phrase->length;
	}
	else {
		grow_box(&(phrase->boundingbox), &(t->boundingbox));
		phrase->length = phrase->length + 1;
		return phrase->length;
	}
}

PED_BOOL is_space_phrase (pedphrase * phrase) {
	PED_BOOL tag;
	pedlistnode * node;
	pedchar * pchar;
	tag = PED_TRUE;
	node = phrase->chars->head;
	while (node != NULL) {
		pchar = (pedchar *) node->content;
		if (pchar->content != 0x20 )
			tag = PED_FALSE;
		node = node->next;
	}
	return tag;
}

void finalize_phrase(pedphrase * phrase) {
	if(phrase != NULL) {
		finalize_list (phrase->chars);
		free(phrase);
	}
}

int determine_phrase_direction(pedphrase * phrase) {
	peddirection dir;
	float ratio;
	pedbox box = phrase->boundingbox;
	dir = PEDDIRECT_UNSET;
	ratio = ratio_of_box (&box);
	if ( ratio > 2.0 ) {
		dir = PEDDIRECT_HOR;
	}
	else if ( ratio < 0.5) {
		dir = PEDDIRECT_VER;
	}
	phrase->dir = dir;
	return dir;
}
