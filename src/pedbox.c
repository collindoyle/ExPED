/* pedbox.c : Implementaion of pedbox
 * written by CHU Yimin
 * University of Tokyo
 * pedbox: Container of a bounding box used in page, zone, line, phrase and character
*/

#include "pedbox.h"
#include <math.h>
#include <stdlib.h>

pedbox * init_box ( pedbox * box) {
	pedbox * newbox;
	if (box == NULL) {
		newbox = (pedbox *)malloc(sizeof(pedbox));
	}
	else {
		newbox = box;
	}
		newbox->x0 = 0.0f;
		newbox->y0 = 0.0f;
		newbox->x1 = 0.0f;
		newbox->y1 = 0.0f;
		return newbox;
      
}

pedbox * init_box_with_value (pedbox * box, float _x0, float _y0, float _x1, float _y1) {
	pedbox * newbox;
	if ( box == NULL) {
		newbox = (pedbox *)malloc(sizeof(pedbox));
	}
	else {
		newbox = box;
	}
	newbox->x0 = _x0;
	newbox->y0 = _y0;
        newbox->x1 = _x1;
	newbox->y1 = _y1;
	return newbox;
}

pedbox * init_box_with_rect(pedbox * box, fz_rect rect) {
	pedbox *newbox;
	if ( box == NULL) {
		newbox = (pedbox *)malloc(sizeof(pedbox));
	}
	else {
		newbox = box;
	}
	newbox->x0 = rect.x0;
	newbox->y0 = rect.y0;
	newbox->x1 = rect.x1;
	newbox->y1 = rect.y1;
	return newbox;
}

PED_BOOL is_in_box (pedbox * box, float x, float y) {
	if ( box == NULL ) {
		return PED_FALSE;
	}
	if ( x < box->x1 && x > box->x0 &&
	     y < box->y1 && y > box->y0 ) {
		return PED_TRUE;
	}
	else {
		return PED_FALSE;
	}
}

PED_BOOL is_intersect (pedbox * alpha, pedbox * beta) {
	if ( alpha == NULL || beta == NULL)
		return PED_FALSE;
	if ( beta->x0 > alpha->x1 ||
	     beta->x1 < alpha->x0 ||
	     beta->y0 > alpha->y1 ||
	     beta->y1 < alpha->y0 )
		return PED_FALSE;
	else
		return PED_TRUE;
}

pedbox * grow_box (pedbox * alpha, pedbox *beta) {
	if ( alpha == NULL || beta == NULL)
		return NULL;
	if(get_area(alpha) == 0) {
		alpha->x0 = beta->x0;
		alpha->y0 = beta->y0;
		alpha->x1 = beta->x1;
		alpha->y1 = beta->y1;
		return alpha; 
	}
	if (get_area(beta) == 0) {
		return alpha;
	}
	alpha->x0 = alpha->x0 < beta->x0 ? alpha->x0 : beta->x0;
	alpha->y0 = alpha->y0 < beta->y0 ? alpha->y0 : beta->y0;
	alpha->x1 = alpha->x1 > beta->x1 ? alpha->x1 : beta->x1;
	alpha->y1 = alpha->y1 > beta->y1 ? alpha->y1 : beta->y1;
	return alpha;
}

float get_area (pedbox *box) {
	float result;
	result = (box->x1-box->x0)*(box->y1-box->y0);
	return result;
}

float get_ratio (pedbox *box) {
	float result;
	result = (box->y1 - box->y0);
	if (result == 0)
		return -1;
	result = (box->x1-box->x0)/result;
	return result;
}

void distance (pedbox *from, pedbox *to, float *x, float *y) {
	if ( is_intersect (from, to)) {
		*x = 0.0f, *y = 0.0f;
		return;
	}
	if (from->x1 < to->x0)
		*x = (to->x0 - from->x1);
	else if (from->x0 > to->x1)
		*x = (from->x0 - to->x1);
	else
		*x = 0.0f;
	
	if (from->y1 < to->y0)
		*y = to->y0 - from->y1;
	else if ( from->y0 > to->y1)
		*y = from->y0 - to->y1;
	else
		*y = 0.0f;
}


fz_irect * bound_box_to_irect (fz_irect * irect, pedbox *box) {
	irect->x0 = floor(box->x0);
	irect->x1 = ceilf(box->x1);
	irect->y0 = floor(box->y0);
	irect->y1 = ceilf(box->y1);
	return irect;
}
