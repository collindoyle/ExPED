/* pedzone.c : implementaiton of the zone entity
 * written by CHU Yimin
 * University of Tokyo
 * pedzone : the entity between page and line, it matches a paragraph we see on the page.  This is the unit that will be classified.
 */

#include "pedzone.h"
#include <stdlib.h>

pedzone * initialize_zone (pedzone *zone) {
	initialize_list(zone->linelist);
	zone->length = 0;
        zone->zoneclass = PEDZONE_UNSET;
	zone->dir = PEDDIRECT_UNSET;
	initialize_box(&(zone->boundingbox));
	return zone;
}

void finalize_zone(pedzone *zone) {
	if (zone != NULL) {
		finalize_list(zone->linelist);
		free(zone);
	}
}

int add_line_to (pedzone * zone, pedline * line) {
	pedlistnode * node;
	if ( zone == NULL || line == NULL)
		return 0;
	node = (pedlistnode *)malloc(sizeof(pedlistnode));
	node = initialize_list_node(node, (void *)line);
	append_node_to_list(zone->linelist, node);
	if (zone->length == 0) {
		zone->dir = line->dir;
		initialize_box(&(zone->boundingbox), line->boundingbox.x0, line->boundingbox.y0, line->boundingbox.x1, line->boundingbox.y1);
	        zone->length = 1;
	}
	else {
		grow_box(&(zone->boundingbox),&(line->boundingbox));
		zone->length += 1;
	}
	return (zone->length);
}

