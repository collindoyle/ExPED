/* pedzone.h : interface of zone element of a document
 * written by CHU Yimin
 * University of Tokyo
 * pedzone : entity of a text paragraph in the document,
 *                 contains the boundingbox, the zone class label, a line list, and direction
 *                 need to extract the features from the zone
 */

#ifndef __PEDZONE
#define __PEDZONE

#include "common.h"
#include "pedbox.h"
#include "pedline.h"
#include "pedlist.h"

typedef struct _pedzone {
	pedlist * lines;
	pedbox * zonebox;
	peddirection dir;
	int length;
	pedzoneclass zoneclass;
} pedzone;

pedzone * init_zone (pedzone * zone);

int add_line_to(pedzone * zone, pedline * line);

void finalize_zone(pedzone * zone);

void extract_features(pedzone *zone);

#endif
