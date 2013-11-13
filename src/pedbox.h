/*   pedbox.h : Interface of pedbox 
 *   written by CHU Yimin
 *   University of Tokyo
 *   pedbox: Container of a bounding box used in page, zone, line, phrase and character
*/

#ifndef __PEDBOX
#define __PEDBOX

#include "mupdf/fitz.h"
#include "common.h"

typedef struct _pedbox {
	float x0;
	float y0;
	float x1;
	float y1;
} pedbox;

pedbox * init_box (pedbox * box);

pedbox * init_box_with_value (pedbox * box, float _x0, float _y0, float _x1, float _y1);

pedbox * init_box_with_rect (pedbox * box, fz_rect rect);

PED_BOOL is_in_box (pedbox * box, float x, float y);

PED_BOOL is_intersect (pedbox * alpha, pedbox *beta);

pedbox * grow_box (pedbox * alpha, pedbox * beta);

float get_area (pedbox *box);

float get_ratio (pedbox *box);

void distance(pedbox *from, pedbox *to, float *x, float *y);

fz_irect * bound_box_to_irect (fz_irect * irect, pedbox *box);

#endif
