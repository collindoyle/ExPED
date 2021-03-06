/* fontcache.h : the list of font descriptors 
 * written by CHU Yimin
 * University of Tokyo
 * fontcache : maintains the font descriptors, keep it singlar
*/

#ifndef __FONTCACHE
#define __FONTCACHE

#include "pedlist.h"
#include "pedfontdes.h"


typedef struct _pedfontcache {
	pedlist * font_list;
} pedfontcache;

pedfontcache* init_font_cache (pedfontcache * cache);

pedfont * find_font (pedfontcache *cache, pedfont * samplefont);

pedfontcache* add_font (pedfontcache *cache, pedfont * samplefont);
 
void finalize_font_cache (pedfontcache *cache);


#endif
