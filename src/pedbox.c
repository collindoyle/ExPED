/* pedbox.c : Implementaion of pedbox
 * written by CHU Yimin
 * University of Tokyo
 * pedbox: Container of a bounding box used in page, zone, line, phrase and character
*/

#include "pedbox.h"

pedbox * initialize_box (pedbox * init_box, float _x0, float _y0, float _x1, float _y1) {
	if ( init_box == NULL) {
		return NULL;
	}
	init_box->x0 = _x0;
	init_box->y0 = _y0;
	init_box->x1 = _x1;
	init_box->y1 = _y1;
	return init_box;
}

pedbox * initialize_box_with_rect(pedbox * init_box, fz_rect rect) {
	if ( init_box == NULL) {
		return NULL;
	}
	init_box->x0 = rect.x0;
	init_box->y0 = rect.y0;
	init_box->x1 = rect.x1;
	init_box->y1 = rect.y1;
	return init_box;
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
	if(area_of_box(*alpha) == 0) {
		alpha->x0 = beta->x0;
		alpha->y0 = beta->y0;
		alpha->x1 = beta->x1;
		alpha->y1 = beta->y1;
		return alpha; 
	}
	if (area_of_box(*beta) == 0) {
		return alpha;
	}
	alpha->x0 = alpha->x0 < beta->x0 ? alpha->x0 : beta->x0;
	alpha->y0 = alpha->y0 < beta->y0 ? alpha->y0 : beta->y0;
	alpha->x1 = alpha->x1 > beta->x1 ? alpha->x1 : beta->x1;
	alpha->y1 = alpha->y1 > beta->y1 ? alpha->y1 : beta->y1;
	return alpha;
}

float area_of_box (pedbox box) {
	float result;
	result = (box.x1-box.x0)*(box.y1-box.y0);
	return result;
}

float ratio_of_box (pedbox box) {
	float result;
	result = (box.y1 - box.y0);
	if (result == 0)
		return -1;
	result = (box.x1-box.x0)/result;
	return result;
}
