/* common.h
 * written by CHU Yimin
 * University of Tokyo
 * Contains the common values and enums used by 
 * the whole project source files
 */


#ifndef __COMMON_HEADER
#define __COMMON_HEADER

#define PED_TRUE 1
#define PED_FALSE 0

typedef unsigned int PED_BOOL;

typedef enum _pedfontstyle {
	PEDFONT_NONE = 0x0,
	PEDFONT_BOLD = 0x1,
	PEDFONT_ITALIC = 0x2,
	PEDFONT_BOLD_ITALIC = 0x3
} pedfontstyle;

#endif
