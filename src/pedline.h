/* pedline.h : Interface of line element of a document
 * written by CHU Yimin
 * University of Tokyo
 * pedline : entity of one single line in a text zone.  The font information within a line can be different.
 *                the lines can be classified into the start, end and middle of a text zone
 */

#ifndef __PEDLINE
#define __PEDLINE

#include "common.h"
#include "pedphrase.h"
#include "pedlist.h"

typedef struct _pedline {
	pedlist * phrases;
	int length;
	pedbox * linebox;
	peddirection dir;
	pedlinetype linetype;
} pedline;

pedline * init_line (pedline * line) ;
void finalize_line (pedline * line);

int add_phrase_to (pedline * line, pedphrase * phrase);

pedlinetype determine_line_type(pedline *line, pedline * prev, pedline *next);

#endif








