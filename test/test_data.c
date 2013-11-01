/* test_data.c : test the functions and correcness of the data structures in the project
 * written by CHU Yimin
 * University of Tokyo
 * contains the functions to test the correctness of pedbox, pedfont, pedchar, pedphrase, pedline, pedzone, peddoc
 * as well as the data structure list and fontcache
 *
*/

#include "test_data.h"
#include <stdio.h>
#include <stdlib.h>

static void test_print_box(pedbox * box, char * box_name) {
	if (box != NULL) {
		printf ( "%s : x0 = %.2f, y0 = %.2f, x1 = %.2f, y1 = %.2f\n", box_name, box->x0, box->y0, box->x1, box->y1);
	}
	else 
		printf ( "Error: the pointer to %s is NULL\n", box_name);
}

static void test_print_bool(PED_BOOL res) {
	if (res == PED_FALSE)
		printf ("false \n");
	else 
		printf ("true \n");
}

void test_data_box() {
	pedbox * box1, *box2, *box3;
	PED_BOOL result;
	float x,y;
	float area, ratio;
	printf("Testing the correctness of pedbox : ...\n");
	x = 0.5f;
	y = 0.5f;
	box1 = (pedbox *)malloc(sizeof(pedbox));
	box1->x0 = 0.0f;
	box1->x1 = 1.0f;
	box1->y0 = 0.0f;
	box1->y1 = 1.0f;
	test_print_box(box1,"box1");
       
	box2 = (pedbox *)malloc(sizeof(pedbox));
	box2 = initialize_box(box2, 0.0f, 0.0f, 1.0f, 1.0f);
	test_print_box(box2, "box2");
	
	box3 = (pedbox *)malloc(sizeof(pedbox));
	box3->x0 = 1.0f;
	box3->x1 = 2.0f;
	box3->y0 = 0.0f;
	box3->y1 = 1.0f;
	test_print_box(box3, "box3");

	result = is_in_box (box1, x, y);
	printf ("Test 1: whether point (%.2f, %.2f) in the %s : ", x, y, "box1");
	test_print_bool (result);

	result = is_in_box (box3, x, y);
	printf ("Test 2: whether point (%.2f, %.2f) in the %s : ", x, y, "box3");
	test_print_bool (result);
	
	result = is_intersect(box1, box3);
	printf ("Test 3: whether %s and %s intersect : ","box1", "box3");
	test_print_bool(result);

	box1 = grow_box(box1,box3);
	printf ("Test 4: After combining two boxes, now the %s is : \n", "box1");
	test_print_box(box1, "box1");
	
	area = area_of_box(box1);
	printf ("Test 5: The area of %s is %.2f \n", "box1", area);
	
	ratio = ratio_of_box (box1);
	printf ("Test 6: The ratio of %s (width/height) is %.2f \n", "box1", ratio);

	box2->x0 = 3.0f;
	box2->y0 = 2.0f;
	box2->x1 = 4.0f;
	box2->y1 = 3.0f;
	
	printf ("Test 7: The distance between two boxes: \n");
	test_print_box(box1, "box1");
	test_print_box(box2, "box2");
	distance_to(box1, box2, &x, &y);
	printf("The distance between %s and %s is x: %.2f, y:%.2f \n", "box1", "box2", x, y);
	printf("\n\n");
	free(box1);
	free(box2);
	free(box3);
}

static void test_print_fontstyle (pedfontstyle style) {
	switch (style) {
	case PEDFONT_NONE:
		printf ("normal \n");
		break;
	case PEDFONT_BOLD:
		printf ("bold \n");
		break;
	case PEDFONT_ITALIC:
		printf ("italic \n");
		break;
	case PEDFONT_BOLD_ITALIC:
		printf ("bold and italic \n");
		break;
	}
	return;
}

static void test_print_font (pedfont * font, char * identifier) {
	if (font == NULL) {
		printf ("Error: the pointer to %s is NULL. \n", identifier);
		return;
	}
	printf ("The information of font %s : \n", identifier);
	printf ("Font name : %s, font size : %.2f, font style : ", font->name, font->size);
	test_print_fontstyle(font->style);
}

void test_data_font() {
	pedfont * pfont, *pfont2;
	PED_BOOL res;
	printf ("Testing font structure \n");
	pfont = (pedfont *)malloc(sizeof(pedfont));
	pfont2 = (pedfont *)malloc(sizeof(pedfont));
	strcpy(pfont->name, "DUMMY FONT NAME");
	pfont->size = 10.0f;
	pfont->style = PEDFONT_NONE;

	test_print_font (pfont, "font1");

	pfont2 = initialize_font(pfont2, "DUMMY FONT NAME", 10.0f, PEDFONT_NONE);
	test_print_font (pfont2, "font2");
	
	printf ("Test 1: compare the two fonts. Does %s equal to  %s ? :  ", "font1", "font2");
	res = is_equal(pfont, pfont2);
	test_print_bool (res);

	pfont2->style = PEDFONT_BOLD_ITALIC;
	res = is_equal(pfont, pfont2);
	test_print_font(pfont2, "font2");
	printf ("Now compare again: Does %s equal to %s? : ", "font1", "font2");
	test_print_bool (res);

	printf ("Test 2: whether the styles are identified : \n");
	res = is_bold (pfont);
	printf ("Is %s bold ? :", "font1");
	test_print_bool(res);

	printf ("Is %s italic ? :", "font1");
	res = is_italic (pfont);
	test_print_bool(res);

	res = is_bold (pfont2);
	printf ("Is %s bold ? :", "font2");
	test_print_bool(res);

	printf ("Is %s italic ? :", "font2");
	res = is_italic (pfont2);
	test_print_bool(res);

	free(pfont);
	free(pfont2);
}
