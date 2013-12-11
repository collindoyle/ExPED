/* pedpage.h : interface for the pedpage structure
 * written by CHU Yimin
 * University of Tokyo
 * pedpage : contains a list of zones, corresponds to a page of the
 *                  electronic document
 */

#ifndef __PEDPAGE
#define __PEDPAGE

#include "common.h"
#include "pedzone.h"
#include "pedlist.h"
#include "pedbox.h"

typedef struct _pedpage {
	pedlist * zones;
	int pageno;
	pedbox *pagebox;
	int length;
} pedpage;

pedpage * init_page (pedpage * page, int pagenum);

void finalize_page (pedpage *page);

int add_zone_to (pedpage * page, pedzone *zone);

int get_pageno(pedpage *page);

pedbox * get_page_box (pedpage *page);

#endif
