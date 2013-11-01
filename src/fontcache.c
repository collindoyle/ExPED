/* fontcache.h : the list of font descriptors 
 * written by CHU Yimin
 * University of Tokyo
 * fontcache : maintains the font descriptors, keep it singlar
*/

#include "fontcache.h"
#include <stdlib.h>

pedfontcache * initialize_font_cache (pedfontcache * cache) {
	if (cache == NULL)
		return NULL;
	else {
		cache->font_list = (pedlist *)malloc(sizeof(pedlist));
		cache->font_list = initialize_list (cache->font_list);
		return cache;
	}
}

pedfont * find_font_from_cache(pedfontcache * cache, pedfont * samplefont) {
	pedlistnode * node;
	pedfont * nodefont;
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
	if (cache == NULL)
		return NULL;
	if (samplefont == NULL)
		return NULL;
	fontnode = (pedlistnode *)malloc (sizeof(pedlistnode));
	fontnode = initialize_list_node (fontnode, (void *)samplefont);
	fontlist = append_node_to_list(cache->font_list, fontnode);
	return cache;
}

void finalize_cache (pedfontcache * cache) {
	if (cache == NULL)
		return;
	free_pedlist(cache->font_list);
	free(cache->font_list);
	cache->font_list = NULL;
}
