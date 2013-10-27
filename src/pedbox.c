#include "pedbox.h"
#include <stdlib.h>

pedbox * 
newbox(float _x0, float _y0, float _x1, float _y1) {
	pedbox * nbox = NULL;
	nbox = (pedbox *)malloc(sizeof(pedbox));
	nbox->x0 = _x0;
	nbox->y0 = _y0;
	nbox->x1 = _x1;
	nbox->y1 = _y1;
	return nbox;
}

void
drop_box(pedbox *box) {
	if(box != NULL)
		free(box);
	box = NULL;
}
