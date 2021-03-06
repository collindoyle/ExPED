/* pedchar.c : Implementation for the character in the document
 * written by CHU Yimin
 * University of Tokyo
 * pedchar : entity of one single character in the document, 
 *                 contains the bounding box, font descriptor, 
 *                 and the content (as integer) of the character
*/

#include "pedchar.h"
#include <stdlib.h>

enum
{
	UTFmax = 4, /* maximum bytes per rune */
	Runesync = 0x80, /* cannot represent part of a UTF sequence (<) */
	Runeself = 0x80, /* rune and UTF sequences are the same (<) */
	Runeerror = 0xFFFD, /* decoding error in UTF */
	Runemax = 0x10FFFF, /* maximum rune value */
};

enum
{
	Bit1 = 7,
	Bitx = 6,
	Bit2 = 5,
	Bit3 = 4,
	Bit4 = 3,
	Bit5 = 2,
    
	T1 = ((1<<(Bit1+1))-1) ^ 0xFF, /* 0000 0000 */
	Tx = ((1<<(Bitx+1))-1) ^ 0xFF, /* 1000 0000 */
	T2 = ((1<<(Bit2+1))-1) ^ 0xFF, /* 1100 0000 */
	T3 = ((1<<(Bit3+1))-1) ^ 0xFF, /* 1110 0000 */
	T4 = ((1<<(Bit4+1))-1) ^ 0xFF, /* 1111 0000 */
	T5 = ((1<<(Bit5+1))-1) ^ 0xFF, /* 1111 1000 */
    
	Rune1 = (1<<(Bit1+0*Bitx))-1, /* 0000 0000 0111 1111 */
	Rune2 = (1<<(Bit2+1*Bitx))-1, /* 0000 0111 1111 1111 */
	Rune3 = (1<<(Bit3+2*Bitx))-1, /* 1111 1111 1111 1111 */
	Rune4 = (1<<(Bit4+3*Bitx))-1, /* 0001 1111 1111 1111 1111 1111 */
    
	Maskx = (1<<Bitx)-1,	/* 0011 1111 */
	Testx = Maskx ^ 0xFF,	/* 1100 0000 */
    
	Bad = Runeerror,
};

int convert_str_to_ucs(unsigned int *ucs, char *str)
{
	int c, c1, c2, c3;
	long l;
    
	/*
	 * one character sequence
	 *	00000-0007F => T1
	 */
	c = *(unsigned char*)str;
	if(c < Tx) {
		*ucs = c;
		return 1;
	}
    
	/*
	 * two character sequence
	 *	0080-07FF => T2 Tx
	 */
	c1 = *(unsigned char*)(str+1) ^ Tx;
	if(c1 & Testx)
		goto bad;
	if(c < T3) {
		if(c < T2)
			goto bad;
		l = ((c << Bitx) | c1) & Rune2;
		if(l <= Rune1)
			goto bad;
	        *ucs = l;
		return 2;
	}
    
	/*
	 * three character sequence
	 *	0800-FFFF => T3 Tx Tx
	 */
	c2 = *(unsigned char*)(str+2) ^ Tx;
	if(c2 & Testx)
		goto bad;
	if(c < T4) {
		l = ((((c << Bitx) | c1) << Bitx) | c2) & Rune3;
		if(l <= Rune2)
			goto bad;
		*ucs = l;
		return 3;
	}
    
	/*
	 * four character sequence (21-bit value)
	 *	10000-1FFFFF => T4 Tx Tx Tx
	 */
	c3 = *(unsigned char*)(str+3) ^ Tx;
	if (c3 & Testx)
		goto bad;
	if (c < T5) {
		l = ((((((c << Bitx) | c1) << Bitx) | c2) << Bitx) | c3) & Rune4;
		if (l <= Rune3)
			goto bad;
		*ucs = l;
		return 4;
	}
	/*
	 * Support for 5-byte or longer UTF-8 would go here, but
	 * since we don't have that, we'll just fall through to bad.
	 */
    
	/*
	 * bad decoding
	 */
bad:
	*ucs = Bad;
	return 1;
}

int convert_ucs_to_str(char *str, unsigned int ucs)
{
	/* Runes are signed, so convert to unsigned for range check. */
	unsigned long c = (unsigned long)ucs;
    
	/*
	 * one character sequence
	 *	00000-0007F => 00-7F
	 */
	if(c <= Rune1) {
		str[0] = c;
		return 1;
	}
    
	/*
	 * two character sequence
	 *	0080-07FF => T2 Tx
	 */
	if(c <= Rune2) {
		str[0] = T2 | (c >> 1*Bitx);
		str[1] = Tx | (c & Maskx);
		return 2;
	}
    
	/*
	 * If the Rune is out of range, convert it to the error rune.
	 * Do this test here because the error rune encodes to three bytes.
	 * Doing it earlier would duplicate work, since an out of range
	 * Rune wouldn't have fit in one or two bytes.
	 */
	if (c > Runemax)
		c = Runeerror;
    
	/*
	 * three character sequence
	 *	0800-FFFF => T3 Tx Tx
	 */
	if (c <= Rune3) {
		str[0] = T3 | (c >> 2*Bitx);
		str[1] = Tx | ((c >> 1*Bitx) & Maskx);
		str[2] = Tx | (c & Maskx);
		return 3;
	}
    
	/*
	 * four character sequence (21-bit value)
	 *	10000-1FFFFF => T4 Tx Tx Tx
	 */
	str[0] = T4 | (c >> 3*Bitx);
	str[1] = Tx | ((c >> 2*Bitx) & Maskx);
	str[2] = Tx | ((c >> 1*Bitx) & Maskx);
	str[3] = Tx | (c & Maskx);
	return 4;
}

pedchar * init_pedchar_with_content (pedchar *pchar, int c, pedbox *box, pedfont *font) {
	pedchar *newchar;
	if (pchar == NULL) {
		newchar = (pedchar *)malloc(sizeof(pedchar));
		newchar->charbox = NULL;
		newchar->pfont = NULL;
	}
	else newchar = pchar;
	newchar->content = c;
	if (newchar->charbox != NULL) {
		free(newchar->charbox);
		newchar->charbox = NULL;
	}
	newchar->charbox = init_box_with_value(NULL, box->x0, box->y0, box->x1, box->y1);
	newchar->pfont = font;
	return newchar;
}

pedchar * init_pedchar_with_str (pedchar *pchar, char * content, pedbox *box, pedfont *font) {
	pedchar * newchar;
	int c;
	int len;
	len = convert_str_to_ucs (&c, content);
	newchar = init_pedchar_with_content(pchar, c, box, font);
	return newchar;
}

pedbox * get_char_box (pedchar *pchar) {
	if (pchar == NULL)
		return NULL;
	return pchar->charbox;
}

pedfont * get_char_font (pedchar *pchar) {
	if (pchar == NULL)
		return NULL;
	return pchar->pfont;
}

char * get_char_content (pedchar *pchar) {
	
	char *c;
	int i;
	if (pchar == NULL)
		return NULL;
	c = (char *)malloc(4*sizeof(char));
	i = convert_ucs_to_str(c, pchar->content);
	return c;
}

void set_char_content (pedchar *pchar, char *chars) {
	unsigned int res;
	unsigned int len;
	if (pchar == NULL)
		return;
	len = convert_str_to_ucs(&res, chars);
	if (res == Bad)
		pchar->content = 0x20;
	else
		pchar->content = res; 
}

void finalize_char (pedchar *pchar) {
	if (pchar == NULL)
		return;
        if (pchar->charbox != NULL)
		free(pchar->charbox);
	free (pchar);
	return;
}

