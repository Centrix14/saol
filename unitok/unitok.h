#ifndef __MAT_TOKENIZER_H_INCLUDED__
#define __MAT_TOKENIZER_H_INCLUDED__

/*
 * SAOL Tokenizer
 * v0.1
 * by Centrix 19.07.2019
 */

#define LETTER 0
#define DIGIT 1
#define CHARACTER 2
#define SPACE 3
#define CONTROL 4

#define WORD 0
#define INTEGER 1
#define CHARACTERS 2
#define SPACES 3
#define CONTROLS 4

int gettypec(int c);
int gettoktype(char *tok);
char *get_token(char *src, int *pos);
int istoktype(char *src, int type);
int isword(char *src);
int isint(char *src);
int ischaracter(char *src);
int isempty(char *src);
int iscontrol(char *src);

#endif
