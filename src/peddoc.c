/* peddoc.c : Implementation of the doc structure
 * written by CHU Yimin
 * University of Tokyo
 * peddoc : the entity presents a whole document, contains a page list, the filen mae, the page count and the pagebox
 */

#include "peddoc.h"
#include <stdlib.h>
#include <string.h>


peddoc * init_doc(peddoc * doc, char * docname) {
	peddoc * newdoc;
	int strl;
	if (doc == NULL)
		newdoc = (peddoc *)malloc(sizeof(peddoc));
	else
		newdoc = doc;
	newdoc->pages = init_list(NULL);
	newdoc->docbox = init_box(NULL);
	newdoc->fontcache = init_font_cache(NULL);
	strl = strlen (docname);
	newdoc->docname = (char *)malloc(strl+1);
	strcpy(newdoc->docname,docname);
	newdoc->pagecounts = 0;
	newdoc->length = 0;
	return newdoc;
}

void finalize_doc(peddoc *doc) {
	pedlistnode *pnode;
	pedpage * page;
	if (doc != NULL) {
		pnode = doc->pages->head;
		while (pnode != NULL) {
			page = (pedpage *)pnode->content;
			finalize_page(page);
			pnode->content = NULL;
			pnode = pnode->next;
		}
		finalize_list(doc->pages);
		finalize_font_cache(doc->fontcache);
		free(doc->docbox);
		free(doc);
	}
}

int add_page_to (peddoc *doc, pedpage *page) {
	pedlistnode *node;
	if (doc == NULL || page == NULL)
		return 0;
	node = init_node(NULL, (void *)page);
	doc->pages = append_node_to_list(doc->pages,node);
	if (doc->length == 0) {
		doc->docbox = init_box_with_value(doc->docbox, page->pagebox->x0, page->pagebox->y0, page->pagebox->x1, page->pagebox->y1);
		doc->length = 1;
	}
	else {
		doc->docbox = grow_box(doc->docbox, page->pagebox);
		doc->length += 1;
	}
	return (doc->length);
}

int get_page_count(peddoc *doc) {
	if (doc == NULL)
		return -1;
	else
		return doc->pagecounts;
}










