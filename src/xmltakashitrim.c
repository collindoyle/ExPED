/* xmltakshitrim.c
 * written by CHU Yimin
 * Preprocessing the xml data from Prof. Takasu.
 * Goal:
 * 1. Trim the <block> and </block> 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

int filtblocktag(FILE *destination, FILE *source);

char * generatefilename (char * sourcefilename);

char * generatefilename (char * sourcefilename) {
	char * result = NULL;
	char * exten;
	int len = strlen(sourcefilename);
	result = (char *)malloc(len+4+1);
	memset(result, 0, len+4+1);
	exten = strrchr(sourcefilename,'.');
	strncpy(result, sourcefilename, exten-sourcefilename);
	strcat(result, ".new");
	strcat(result, exten);
	return result;
}

int main ( int argc, char *argv[]) {
	char * newfilename = NULL;
	FILE *sourcefp = NULL;
	FILE *destfp = NULL;
	int charcount = 0;
	if ( argc < 2) {
		printf ("Please specify the name of the source file.\n");
		return 0;
	}
	newfilename = generatefilename(argv[1]);
	if (newfilename != NULL)
	{
		destfp = fopen(newfilename, "w+");
	}
	else {
		printf ("Fail to open the destination file. \n");
		return 0;
	}
	sourcefp = fopen(argv[1],"r+");
	if ( sourcefp != NULL && destfp != NULL) {
		charcount = filtblocktag(destfp,sourcefp);
		fclose(destfp);
		fclose(sourcefp);
		if (newfilename != NULL) {
			free(newfilename);
		}
		newfilename = NULL;
		return charcount;
	}

	else {
		printf ("Fail to open the file. \n");
		return 0;
	}
}

int filtblocktag(FILE *destination, FILE * source) {
	char curchar;
	char inputbuf[2];
	char outputbuf[256];
	int buflocation = 0;
	int charcount = 0;
	int intag = 0;
	int endtag = 0;
	int copytag = 1;
	int prevtag = 0;

	memset(inputbuf,0,2);
	memset(outputbuf,0,256);

	curchar = fgetc(source);
	while (curchar != EOF) {
		inputbuf[0] = curchar;
	        switch (inputbuf[0]) {
		case '<':
			intag = 1;
			prevtag = 1;
			if ( buflocation != 0) {
				fputs(outputbuf, destination);
				buflocation = 0;
				memset(outputbuf, 0, 256);
			}
			strcat(outputbuf, inputbuf);
			buflocation++;
			break;
		case '>':
		        strcat(outputbuf, inputbuf);
			if ( copytag == 1)
				fputs(outputbuf, destination);
			memset(outputbuf, 0, 256);
			buflocation = 0;
			intag = 0;
			copytag =1 ;
			endtag = 0;
			prevtag = 0;
			break;
		case '/':
			if ( intag == 1 && prevtag == 1) {
				endtag = 1;
			}
		        strcat(outputbuf, inputbuf);
			buflocation++;
			break;
		case 'b':
			if ( prevtag == 1)
				copytag = 0;
			strcat(outputbuf, inputbuf);
			buflocation++;
			break;
		default:
			strcat(outputbuf, inputbuf);
			prevtag = 0;
			buflocation++;
			break;
		}
		curchar = fgetc(source);
		charcount++;
	}
	return charcount;
}






