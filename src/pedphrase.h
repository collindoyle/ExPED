/* Pedphrase.h : the interface of pedphrase
 * written by CHU Yimin
 * University of Tokyo
 * pedphrase : a set of neighbouring pedchars. contains the information of font, bounding box, and a list of characters
*/

#ifndef __PEDPHRASE
#define __PEDPHRASE

#include "common.h"
#include "pedchar.h"
#include "pedlist.h"

typedef struct _pedphrase {
	pedlist * chars;
	int length;
	pedbox * phrasebox;
	pedfont * font;
	peddirection dir;
} pedphrase;

pedphrase * init_phrase(pedphrase * phrase);

int add_character_to(pedphrase *phrase, pedchar * t);

int determine_phrase_direction(pedphrase * phrase);

PED_BOOL is_space_phrase (pedphrase * phrase);

void finalize_phrase(pedphrase * phrase);

#endif
