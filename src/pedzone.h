/* pedzone.h : interface of zone element of a document
 * written by CHU Yimin
 * University of Tokyo
 * pedzone : entity of a text paragraph in the document,
 *                 contains the boundingbox, the zone class label, a line list, and direction
 *                 need to extract the features from the zone
 */

#ifndf __PEDZONE
#define __PEDZONE

#include "common.h"
#include "pedbox.h"
#include "pedline.h"
#include "pedlist.h"

typedef struct _pedzone {
	pedlist * linelist;
	pedbox boundingbox;
	peddirection dir;
	int length;
	pedzoneclass zoneclass;
} pedzone;

pedzone * initialize_zone (pedzone * zone);

int add_line_to(pedzone * zone, pedline * line);

void finalize_zone(pedzone * zone);

#endif
