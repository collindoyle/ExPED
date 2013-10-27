/*#include "mupdf/fitz.h"*/

typedef struct _pedbox {
	float x0;
	float y0;
	float x1;
	float y1;
} pedbox;

pedbox * newbox(float _x0, float _y0, float _x1, float _y1);

void drop_box(pedbox * box);

