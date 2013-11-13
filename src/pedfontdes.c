/* pedfontdes.c : Implementation of the font descriptor
 * written by CHU Yimin
 * University of Tokyo
 * pedfont : the structure to contain the font information of characters and phrases
 *                Contains the font name, font size and font style
 * The needed functions are the comparasion and style check 
*/

#include "pedfontdes.h"
#include <string.h>
#include <stdlib.h>

pedfont * init_font (pedfont * pfont, char * name, float size, pedfontstyle style) {
	pedfont * newfont;
	if (pfont == NULL) {
		newfont  = (pedfont *)malloc(sizeof(pedfont));
	}
	else {
		newfont = pfont;
	}
	strcpy(newfont->name,name);
	newfont->size = size;
	newfont->style = style;
	return newfont;
}

PED_BOOL is_equal (pedfont *fonta, pedfont *fontb) {
	if ( fonta == NULL || fontb == NULL )
		return PED_FALSE;
	if ( strcmp(fonta->name, fontb->name) != 0)
		return PED_FALSE;
	if ( fonta->size != fontb->size)
		return PED_FALSE;
	if ( fonta->style != fontb->style)
		return PED_FALSE;
	return PED_TRUE;
}

PED_BOOL is_bold (pedfont *font) {
	if (font->style == PEDFONT_BOLD ||
	    font->style == PEDFONT_BOLD_ITALIC)
		return PED_TRUE;
	else
		return PED_FALSE;
}

PED_BOOL is_italic (pedfont *font) {
	if (font->style == PEDFONT_ITALIC ||
	    font->style == PEDFONT_BOLD_ITALIC )
		return PED_TRUE;
	else
		return PED_FALSE;
}
