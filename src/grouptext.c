/* grouptext.c : implementation for the functions to determine when and how to group the characters and other elements to higher level.
 * written by CHU Yimin
 * University of Tokyo
 * Here are a group of functions which are used to determine whether  the elements can be grouped into higher level, or whether they can be included in an existed higher level element
 */

#include "grouptext.h"

#define PHRASE_THRESHOLD  0.2
#define LINE_THRESHOLD 0.4

PED_BOOL is_groupable_to_phrase ( pedphrase * phrase, pedchar *achar)
{
	float x, float y;
	pedbox *from = NULL;
	pedbox *to = NULL;
	if (is_equal(phrase->pfont, achar->pfont) == PED_FALSE)
		return PED_FALSE;
	from = phrase->phrasebox;
	to = achar->charbox;
	distance(from, to, &x, &y);
	if (phrase->dir == PEDDIRECT_HOR && x < PHRASE_THRESHOLD)
		return PED_TRUE;
	else if (phrase->dir == PEDDIRECT_VER && y < PHRASE_THRESHOLD)
		return PED_TRUE;
	else if (phrase->dir == PEDDIRECT_UNSET && (x < PHRASE_THRESHOLD || y < PHRASE_THRESHOLD))
		return PED_TRUE;
	return PED_FALSE;
}

PED_BOOL is_groupable_to_line ( pedline *line, pedphrase *phrase)
{
	float x, float y;
	if (line->dir != phrase->dir)
		return PED_FALSE;
	distance(line->linebox, phrase->phrasebox, &x, &y);
	if (line->dir == PEDDIRECT_HOR && )
	return PED_FALSE;
}

PED_BOOL is_groupable_to_zone ( pedzone * zone, pedline *line)
{
	return PED_TRUE;
}
