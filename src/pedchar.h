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
	pedbox  * charbox;
	pedfont * pfont;
} pedchar;

pedchar * init_pedchar (pedchar * pchar, char *content, pedbox * box, pedfont * font);
void finalize_char (pedchar *pchar);
pedbox * get_char_box (pedchar *pchar);
pedfont * get_char_font (pedchar *pchar);
char * get_char_content (pedchar *pchar);
void set_char_content (pedchar *pchar, char *chars);

int convert_ucs_to_str (char *str, unsigned int ucs);

int convert_str_to_ucs (unsigned int *ucs, char *str);

#endif
