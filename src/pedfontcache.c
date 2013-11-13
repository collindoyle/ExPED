/* fontcache.h : the list of font descriptors 
 * written by CHU Yimin
 * University of Tokyo
 * fontcache : maintains the font descriptors, keep it singlar
*/

#include "pedfontcache.h"
#include <stdlib.h>

pedfontcache * init_font_cache (pedfontcache * cache) {
	pedfontcache * newcache;
	if (cache == NULL)
		newcache = (pedfontcache *)malloc(sizeof(pedfontcache));
	else {
		newcache = cache;
	}
	newcache->font_list = init_list(NULL);
	return newcache;
}

pedfont * find_font_from_cache(pedfontcache * cache, pedfont * samplefont) {
	pedlistnode * node;
	pedfont * nodefont;
	if (cache == NULL)
		return NULL;
	nodefont = NULL;
	node = cache->font_list->head;
	while (node != NULL) {
		if (is_equal ((pedfont *)(node->content), samplefont) == PED_TRUE) {
			nodefont = (pedfont *)(node->content);
			return nodefont;
		}
		node = node->next;
	}
	return nodefont;
}

pedfontcache * append_font_to_cache (pedfontcache *cache, pedfont * samplefont) {
	pedlistnode * fontnode;
	pedlist * fontlist;
	pedfontcache *rescache;
	if (cache == NULL)
		rescache = init_font_cache(NULL);
	else
		rescache = cache;
	if (samplefont == NULL)
		return rescache;
	fontnode = init_node(NULL,(void *)samplefont);
	fontlist = append_node_to_list(rescache->font_list, fontnode);
	return rescache;
}

void finalize_cache (pedfontcache * cache) {
	pedlistnode * pnode;
	if (cache == NULL)
		return;
	pnode = cache->font_list->head;
	while (pnode != NULL) {
		free(pnode->content);
		pnode->content = NULL;
		pnode = pnode->next;
	}
	finalize_list(cache->font_list);
	free(cache->font_list);
	cache->font_list = NULL;
	free(cache);
}
