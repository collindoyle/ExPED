/* peddoc.h : the interface for doc entity for the electronic documents
 * written by CHU Yimin
 * University of Tokyo
 * peddoc : the entity presents a whole document, contains a page list, the file name, the page count, and the page box.
 */

#include "common.h"
#include "pedlist.h"
#include "pedpage.h"
#include "pedbox.h"
#include "mupdf/fitz.h"


typedef struct _peddoc {
	pedlist * pages;
	pedbox pagebox;
	char * docname;
	int pagecounts;
	fz_doc * doc;
} peddoc;

