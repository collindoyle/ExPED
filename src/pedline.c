/* pedline.c : Implementation of the pedline structure
 * written by CHU Yimin
 * University of Tokyo
 * pedline : the entity presents for a pedline, between the pedzone and pedphrase. Inside a pedline the font can vary.
 */

#include "common.h"
#include "pedline.h"
#include <stdlib.h>

pedline * init_line(pedline *line) {
	pedline * newline;
	if(line == NULL)
		newline = (pedline *) malloc (sizeof (pedline));
	else
		newline = line;
	newline->phrases = init_list (NULL);
	newline->linebox = init_box(NULL);
	newline->length = 0;
	newline->dir = PEDDIRECT_UNSET;
	newline->linetype = PEDLINE_UNKNOWN;
	
	return newline;
}

void finalize_line (pedline * line) {
	pedlistnode * pnode;
	pedphrase * phrase;
	if ( line != NULL) {
		pnode = line->phrases->head;
		while (pnode != NULL) {
			phrase = (pedphrase *)pnode->content;
			finalize_phrase(phrase);
			pnode->content = NULL;
			pnode = pnode->next;
		}
		finalize_list (line->phrases);
		free (line->linebox);
		free(line);
	}
}

int add_phrase_to (pedline *line, pedphrase *phrase) {
	pedlistnode * node;
	if (line == NULL || phrase == NULL)
		return 0;
	node = init_node(NULL, (void *)phrase);
	line->phrases = append_node_to_list(line->phrases, node);
	if (line->length == 0) {
		line->linebox = init_box_with_value(line->linebox, phrase->phrasebox->x0, phrase->phrasebox->y0,phrase->phrasebox->x1, phrase->phrasebox->y1);
		line->length = 1;
		line->dir = phrase->dir;
	}
	else {
		line->linebox = grow_box (line->linebox, phrase->phrasebox);
		line->length = line->length + 1;
	}
	return line->length;
}

pedlinetype determine_line_type(pedline *line, pedline * prev, pedline *next) {
	float x_prev, x_next, y_prev, y_next;
	float height, width;
	float _distprev, _distnext;
	if (line == NULL)
		return PEDLINE_UNKNOWN;
	if (prev == NULL)
		return PEDLINE_START;
	if (next == NULL)
		return PEDLINE_END;
	if (prev->dir != line->dir)
		return PEDLINE_START;
	if (next->dir != line->dir)
		return PEDLINE_END;
	height = line->linebox->y1 - line->linebox->y0;
	width = line->linebox->x1 - line->linebox->x0;
	distance(prev->linebox, line->linebox, &x_prev, &y_prev);
	distance(line->linebox, next->linebox, &x_next, &y_next);
	if (line->dir == PEDDIRECT_HOR) {
		_distprev = y_prev/height;
		_distnext = y_next/height;
		if (_distprev / _distnext > PED_LINETYPE_THRESHOLD)
			return PEDLINE_START;
		if (_distnext / _distprev > PED_LINETYPE_THRESHOLD)
			return PEDLINE_END;
		return PEDLINE_MIDDLE;
	}
	if (line->dir == PEDDIRECT_VER) {
		_distprev = x_prev/width;
		_distnext = x_next/width;
		if (_distprev/_distnext > PED_LINETYPE_THRESHOLD)
			return PEDLINE_START;
		if (_distnext/_distprev > PED_LINETYPE_THRESHOLD)
			return PEDLINE_END;
		return PEDLINE_MIDDLE;
	}
	return PEDLINE_MIDDLE;
}








