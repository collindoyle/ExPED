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
