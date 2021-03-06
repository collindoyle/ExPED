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

#define PED_LINETYPE_THRESHOLD 2

typedef unsigned int PED_BOOL;

typedef enum _pedfontstyle {
	PEDFONT_NONE = 0x0,
	PEDFONT_BOLD = 0x1,
	PEDFONT_ITALIC = 0x2,
	PEDFONT_BOLD_ITALIC = 0x3
} pedfontstyle;

typedef enum _peddirection {
	PEDDIRECT_UNSET = 0x0,
	PEDDIRECT_HOR = 0x1,
	PEDDIRECT_VER = 0x2
} peddirection;

typedef enum _pedlinetype {
	PEDLINE_UNKNOWN = 0x0,
	PEDLINE_START = 0x1,
	PEDLINE_END = 0x2,
	PEDLINE_MIDDLE = 0x3
} pedlinetype;

typedef enum _pedzoneclass {
	PEDZONE_UNSET,
	PEDZONE_BODY,
	PEDZONE_TITLE,
	PEDZONE_ABSTRACT,
	PEDZONE_AUTHOR,
	PEDZONE_AFFILATION,
	PEDZONE_KEYWORD,
	PEDZONE_CAPTION,
	PEDZONE_PAGENUM,
	PEDZONE_SUBTITLE,
	PEDZONE_REFERENCE,
	PEDZONE_START,
	PEDZONE_END
}pedzoneclass;
#endif
