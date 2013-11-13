/* Pedphrase.h : the interface of pedphrase
 * written by CHU Yimin
 * University of Tokyo
 * pedphrase : a set of neighbouring pedchars. contains the information of font, bounding box, and a list of characters
*/

#include "pedphrase.h"
#include <stdlib.h>

pedphrase * init_phrase(pedphrase * phrase) {
	pedphrase * newphrase;
	if (phrase == NULL)
	        newphrase = (pedphrase *)malloc (sizeof(pedphrase));
	else
		newphrase = phrase;
	newphrase->chars = init_list(NULL);
	newphrase->length = 0;
	newphrase->phrasebox = init_box(NULL);
	newphrase->font = NULL;
	newphrase->dir = PEDDIRECT_UNSET;
	return newphrase;
}

int add_character_to(pedphrase *phrase, pedchar *t) {
	pedlistnode * node;
	if (phrase == NULL || t == NULL)
		return 0;
	node = init_node(NULL, (void *)t);
	phrase->chars = append_node_to_list(phrase->chars, node);
	if (phrase->length == 0 ) {
		phrase->font = t->pfont;
		phrase->phrasebox = init_box_with_value(phrase->phrasebox, t->charbox->x0, t->charbox->y0, t->charbox->x1, t->charbox->y1);
		phrase->length = 1;
	}
	else {
		phrase->phrasebox = grow_box(phrase->phrasebox, t->charbox);
		phrase->length = phrase->length + 1;
	}
	determine_phrase_direction(phrase);
	return phrase->length;
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
	pedlistnode * node;
	pedchar * pchar;
	if(phrase != NULL) {
		node = phrase->chars->head;
		while(node != NULL) {
			pchar = (pedchar *) node->content;
			finalize_char(pchar);
			node->content = NULL;
			node = node->next;
		}
		finalize_list (phrase->chars);
		free(phrase->phrasebox);
		free(phrase);
	}
}

int determine_phrase_direction(pedphrase * phrase) {
	peddirection dir;
	float ratio;
	pedbox *box;
	if (phrase == NULL)
		return PEDDIRECT_UNSET;
	box = phrase->phrasebox;
	
	dir = PEDDIRECT_UNSET;
	ratio = get_ratio (box);
	if ( ratio > 2.0 ) {
		dir = PEDDIRECT_HOR;
	}
	else if ( ratio < 0.5) {
		dir = PEDDIRECT_VER;
	}
	phrase->dir = dir;
	return dir;
}
