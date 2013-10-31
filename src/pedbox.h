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

pedbox * initialize_box (pedbox * init_box, float _x0, float _y0, float _x1, float _y1);

pedbox * initialize_box_with_rect (pedbox * init_box, fz_rect rect);

PED_BOOL is_in_box (pedbox * box, float x, float y);

PED_BOOL is_intersect (pedbox * alpha, pedbox *beta);

pedbox * grow_box (pedbox * alpha, pedbox * beta);

float area_of_box (pedbox box);

float ratio_of_box (pedbox box);





#endif
