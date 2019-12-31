#include <stdio.h>
#include <string.h>
#include "unitok/unitok.h"

/*
 * ssp - standard saol preprocessor
 * v1.0
 * 31/12/2019
 * by Centrix
 */

int is_kw(char* word);
void exec(int op_code, char* arg);
void macro(char *arg), link(char *arg), prog(char *arg), copy(char *arg);

char macro_names[1024][256], macro_codes[1024][256];
int len = 3, code = 3, pos = 0;
FILE *src, *dst;

int main(int argc, char *argv[]) {
	char line[1024], *tok = "";

	if (argc < 2) {
		fprintf(stderr, "Usage: in_file out_file\n");
		return 1;
	}
	src = fopen(argv[1], "r");
	dst = fopen(argv[2], "w");

	while (fgets(line, 1024, src) != NULL) {
		tok = strtok(line, " \n");

		while (tok != NULL) {
			if (is_kw(tok) >= 0)
				code = is_kw(tok);
			if (!isempty(tok))	
				exec(code, tok);

			tok = strtok(NULL, " \n");
		}
	}

	fclose(src);
	fclose(dst);
	return 0;
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
		state = 1;
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
		fprintf(dst, "%s", macro_codes[is_macro(arg)]);
	else
		fprintf(dst, "%s ", arg);
}
