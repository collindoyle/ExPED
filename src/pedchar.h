/* pedchar.h : Interface for the character in the document
 * written by CHU Yimin
 * University of Tokyo
 * pedchar : entity of one single character in the document, 
 *                 contains the bounding box, font descriptor, 
 *                 and the content (as integer) of the character
*/

#ifndef __PEDCHAR
#define __PEDCHAR

#include "common.h"
#include "pedbox.h"
#include "pedfontdes.h"

typedef struct _pedchar {
	unsigned int content;
	pedbox boundingbox;
	pedfont * pfont;
} pedchar;

pedchar * initialize_pedchar (pedchar * pchar, unsigned int content, pedbox * box, pedfont * font);
pedbox * get_char_box (pedchar *pchar);
pedfont * get_char_font (pedchar *pchar);
char * get_char_content (pedchar *pchar);
void set_char_content (pedchar *pchar, char *chars);



#endif
