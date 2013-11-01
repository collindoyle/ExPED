/* pedfontdes.h : Interface of the font descriptor used in the project
 * written by CHU Yimin
 * University of Tokyo
 * pedfont: the structure to contain the font information of charcaters and phrases
 *                     Contains the font name, font size and font style
*/

#ifndef __PEDFONTDESCRIPTOR
#define __PEDFONTDESCRIPTOR

#include "common.h"

typedef struct _pedfont {
	char name[30];
	float size;
	pedfontstyle style;
} pedfont;

pedfont * initialize_font (pedfont * pfont, char * name, float size, pedfontstyle style);

PED_BOOL is_equal (pedfont *fonta, pedfont *fontb);

PED_BOOL is_bold (pedfont * font);

PED_BOOL is_italic (pedfont * font);







#endif
