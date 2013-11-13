/* pedzone.c : implementaiton of the zone entity
 * written by CHU Yimin
 * University of Tokyo
 * pedzone : the entity between page and line, it matches a paragraph we see on the page.  This is the unit that will be classified.
 */

#include "pedzone.h"
#include <stdlib.h>

pedzone * init_zone (pedzone *zone) {
	pedzone * newzone;
	if (zone == NULL) {
		newzone = (pedzone *)malloc(sizeof(pedzone));
	}
	else {
		newzone = zone;
	}
	newzone->lines = init_list(NULL);
	newzone->zonebox = init_box(NULL);
	newzone->length = 0;
        newzone->zoneclass = PEDZONE_UNSET;
	newzone->dir = PEDDIRECT_UNSET;
	return newzone;
}

void finalize_zone(pedzone *zone) {
	pedlistnode * pnode;
	pedline * line;
	if (zone != NULL) {
		pnode = zone->lines->head;
		while (pnode != NULL) {
			line = (pedline *)pnode->content;
			finalize_line (line);
			pnode->content = NULL;
			pnode = pnode->next;
		}
		finalize_list(zone->lines);
		free(zone->zonebox);
		free(zone);
	}
}

int add_line_to (pedzone * zone, pedline * line) {
	pedlistnode * node;
	if ( zone == NULL || line == NULL)
		return 0;
	node = init_node(NULL, (void *)line);
	zone->lines = append_node_to_list(zone->lines, node);
	if (zone->length == 0) {
		zone->dir = line->dir;
		zone->zonebox = init_box_with_value(zone->zonebox, line->linebox->x0, line->linebox->y0, line->linebox->x1, line->linebox->y1);
	        zone->length = 1;
	}
	else {
		zone->zonebox = grow_box(zone->zonebox,line->linebox);
		zone->length += 1;
	}
	return (zone->length);
}

void extract_features (pedzone *zone) {
}
