/* pedpage.c : implementation of structure pedpage
 * written by CHU Yimin
 * University of Tokyo
 * pedpage : contains a list of zones, corresponds to a page of the
 *                  electronic document
 */

#include "pedpage.h"
#include <stdlib.h>

pedpage * init_page (pedpage * page, int pagenum) {
	pedpage * newpage;
	if (page == NULL)
		newpage = (pedpage *)malloc (sizeof (pedpage));
	else
		newpage = page;
	newpage->pageno = pagenum;
	newpage->zones = init_list(NULL);
	newpage->pagebox = init_box(NULL);
	newpage->length = 0;
	return newpage;
}

void finalize_page (pedpage *page) {
	pedzone * zone;
	pedlistnode * node;
	if (page == NULL)
		return;
	node = page->zones->head;
	while(node != NULL ) {
		zone = (pedzone *)(node->content);
		finalize_zone(zone);
		node->content = NULL;
		node = node->next;
	}
	finalize_list(page->zones);
	free(page->pagebox);
	free(page);
}

int add_zone_to (pedpage * page, pedzone *zone) {
	pedlistnode *node;
	if (page == NULL || zone == NULL)
		return 0;
	node = init_node(NULL, (void *)zone);
	page->zones = append_node_to_list(page->zones, node);
	if (page->length == 0) {
		page->pagebox = init_box_with_value(page->pagebox, zone->zonebox->x0, zone->zonebox->y0, zone->zonebox->x1, zone->zonebox->y1);
		page->length = 1;
	}
	else {
		page->pagebox = grow_box(page->pagebox, zone->zonebox);
		page->length += 1;
	}
	return (page->length);

}

int get_pageno(pedpage *page)
{
	if (page == NULL)
		return -1;
	else return page->pageno;
}

pedbox * get_page_box (pedpage *page) {
	if (page == NULL)
		return NULL;
	else
		return page->pagebox;
}
