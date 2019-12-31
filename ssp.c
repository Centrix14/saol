#include <stdio.h>
#include <string.h>
#include "unitok/unitok.h"

/*
 * ssp - standard saol preprocessor
 * v1.2
 * 31/12/2019
 * by Centrix
 */

char *ssp_tok(char *str, int *pos);
int is_kw(char* word);
void exec(int op_code, char* arg);
void macro(char *arg), link(char *arg), prog(char *arg), copy(char *arg);

char macro_names[1024][256], macro_codes[1024][256];
int len = 3, code = 3, pos = 0;
FILE *src, *dst;

int main(int argc, char *argv[]) {
	char line[1024], *tok = "";
	int pos = 0;

	if (argc < 2) {
		fprintf(stderr, "Usage: in_file out_file\n");
		return 1;
	}
	src = fopen(argv[1], "r");
	dst = fopen(argv[2], "w");

	while (fgets(line, 1024, src) != NULL) {
		pos = 0;
		tok = ssp_tok(line, &pos);

		while (tok != NULL) {
			if (is_kw(tok) >= 0)
				code = is_kw(tok);
			if (!isempty(tok))	
				exec(code, tok);

			tok = ssp_tok(line, &pos);
		}
	}

	fclose(src);
	fclose(dst);
	return 0;
}

char *ssp_tok(char *str, int *pos) {
	static char tok[256];
	char *tptr = tok, *sptr = &str[*pos];
	int sticking = 0;

	if (!(*sptr))
		return NULL;

	while (*sptr) {
		if (strchr("{}", *sptr) != NULL) {
			sticking = !sticking;
			sptr++;

			if (*(sptr-1) == '}') break;
			continue;
		}

		if (sticking || (strchr(" \n", *sptr) == NULL)) {
			*tptr = *sptr;
			tptr++; sptr++;
		}
		else
			break;
	}
	*tptr = '\0';
	*pos = (sptr - str) + 1;

	return tok;
}

int is_kw(char *word) {
	char *words[] = {".macro", ".link", ".prog"};

	for (int i = 0; i < len; i++) {
		if (!strcmp(words[i], word)) return i;
	}
	return -1;
}

void exec(int op_code, char *arg) {
	void (*funcs[])(char*) = {macro, link, prog, copy};
	(*funcs[op_code])(arg);
}

void macro(char *arg) {
	static int state = 0;

	if (!state) {
		state = 1;
		return ;
	}
	else if (state == 1) {
		sprintf(macro_names[pos], "%s", arg);
		state = 2;
	}
	else {
		sprintf(macro_codes[pos++], "%s", arg);
		state = 0;
	}
}

void link(char *arg) {
	FILE *from;
	int c = 0;

	if (!strcmp(arg, ".link")) return ;

	from = fopen(arg, "r");
	if (from == NULL) {
		fprintf(stderr, "no such file `%s`\n", arg);
		return ;
	}

	while (c != EOF) {
		if (c > 0)
			putc(c, dst);
		c = fgetc(from);
	}
	putc('\n', dst);

	fclose(from);
}

void prog(char *arg) {
	code = 3;
}

int is_macro(char *word) {
	for (int i = 0; i < pos; i++)
		if (!strcmp(macro_names[i], word)) return i;
	return -1;	
}

void copy(char *arg) {
	if (is_macro(arg) >= 0)
		fprintf(dst, "%s ", macro_codes[is_macro(arg)]);
	else
		fprintf(dst, "%s ", arg);
}
