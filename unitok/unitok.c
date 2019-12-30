#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "unitok.h"

/*
 * SAOL Tokenizer
 * This file contains my tokenizer for an interpreter Mat
 * v0.1
 * by Centrix 19.07.2019
 */

char __tok[256];

int isnum(int c) {
	if (strchr("0123456789-.", c) == NULL) return 0;
	return 1;
}

int gettypec(int c) {
	int (*func[]) (int) = {isalpha, isnum, ispunct, isspace, iscntrl};

	for (int i = 0; i < 5; i++) 
		if ( (*func[i])(c) )
			return i;
	
	return -1;
}

int is_stopc(char c) {
	if (strchr("<>+\'*/@;|:~#&", c) == NULL) return 0;
	return 1;
}

char *get_token(char *src, int *pos) {
	char *sptr = src+(*pos);
	int i = 0, sticking = 0;
	
	if ( !(*sptr) ) return NULL;

	while (*sptr) {
		if (strchr("()", *sptr) != NULL) {
			sticking = !sticking;
			sptr++;

			if (*(sptr-1) == ')') break;
			continue;
		}
		else if ( (gettypec(*sptr) == gettypec(*(sptr+1)) || sticking) ) {
			if (is_stopc(*sptr) && !sticking) {
				__tok[i++] = *sptr;
				sptr++;
				break;
			}
			else __tok[i++] = *sptr;
			sptr++;
		}
		else {
			__tok[i++] = *sptr;
			sptr++;
			break;
		}
	}		
	__tok[i] = '\0';
	*pos = sptr-src;

	return __tok;
}

int gettoktype(char *tok) {
	int (*funcs[]) (char *) = {isword, isint, ischaracter, isempty, iscontrol};

	for (int i = 0; i < 5; i++) {
		if ( (*funcs[i])(tok) ) return i;
	}
	return -1;
}

int istoktype(char *src, int type) {
	int i = 0;

	while (src[i])
		if (gettypec(src[i++]) != type) return 0;
	return 1;
}

int isword(char *src) {
	return istoktype(src, LETTER); 
}

int isint(char *src) {
	return istoktype(src, DIGIT);
}

int ischaracter(char *src) {
	return istoktype(src, CHARACTER);
}

int isempty(char *src) {
	return istoktype(src, SPACE);
}

int iscontrol(char *src) {
	return istoktype(src, CONTROL);
}
