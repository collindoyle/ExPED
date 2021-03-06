/* pedpdfextract.h : api for extracting contents from pdf files
 * written by CHU Yimin
 * University of Tokyo
 *
 * This is a group of functions using the mupdf library to extract the contents from pdf documents.  Will assemble the contents into the structure of peddoc.
 */

#ifndef __PEDPDFEXTRACT
#define __PEDPDFEXTRACT

#include "common.h"
#include "peddoc.h"
#include "mupdf/fitz.h"

peddoc* loadfile(const char * filename);

pedpage* convert_page(fz_text_page *tpage, peddoc *pdoc);

pedfontstyle  convert_font_style(fz_font * pfont);

#endif
