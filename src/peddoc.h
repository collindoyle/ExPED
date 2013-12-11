/* peddoc.h : the interface for doc entity for the electronic documents
 * written by CHU Yimin
 * University of Tokyo
 * peddoc : the entity presents a whole document, contains a page list, the file name, the page count, and the page box.
 */

#ifndef __PEDDOC
#define __PEDDOC

#include "common.h"
#include "pedlist.h"
#include "pedpage.h"
#include "pedbox.h"
#include "pedfontcache.h"

typedef struct _peddoc {
	pedlist * pages;
	pedbox *docbox;
	char * docname;
	pedfontcache * fontcache;
	int pagecounts;
	int length;
} peddoc;

peddoc * init_doc(peddoc * doc, char * docname);
void finalize_doc(peddoc *doc);

int add_page_to (peddoc *doc, pedpage *page);

int get_page_count(peddoc *doc);

#endif
