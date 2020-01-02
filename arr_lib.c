/* Saol interpreter library v1.3 02/01/2020 by Centrix */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arr_lib.h"
#include "unitok/unitok.h"

#define MAX 2048

int arr[MAX];
int pos = 0;

int arg_type = 0; // 0 - integer, 1 - character
int start = 0, end = MAX;
int len = 25;
int pred = 1;

void ini(char *arg) {
	if (!strcmp(arg, "il")) {
		arr[pos] = end - start - 1;
		return ;
	}
	else if (isint(arg))
		arr[pos] = atoi(arg);
	else
		arr[pos] = arg[0];
}

void addr(char *arg) {
	if (isint(arg) && atoi(arg) < MAX)
		pos = atoi(arg);
}

void shr(char *arg) {
	pos++;
}

void shl(char *arg) {
	pos--;
}

void show_elm(char *arg) {
	if (!strcmp(arg, "_!")) {
		if (!arg_type)
			printf("%d", arr[pos]);
		else
			putc(arr[pos], stdout);
	}
}

void show_arr(char *arg) {
	if (!strcmp(arg, "-!")) {
		for (int i = start; i < end; i++) {
			if (!arg_type)
				printf("%d", arr[i]);
			else
				putc(arr[i], stdout);
		}
	}
}

void comment(char *arg) {}

void filler(char *arg) {
	int i = 0;

	if (isint(arg)) arr[pos++] = atoi(arg);
	else {
		if (!strcmp(arg, "|")) return ;

		while (arg[i]) {
			arr[pos++] = arg[i++];
		}
	}
}

void int_mode(char *arg) {
	arg_type = 0;
}

void char_mode(char *arg) {
	arg_type = 1;
}

void sum(char *arg) {
	for (int i = start; i < end; i++)
		arr[MAX-1] += arr[i];
}

void subt(char *arg) {
	for (int i = start; i < end; i++)
		arr[MAX-1] -= arr[i];
}

void mult(char *arg) {
	for (int i = start; i < end; i++)
		arr[MAX-1] *= arr[i];
}

void idiv(char *arg) {
	for (int i = start; i < end; i++) {
		if (arr[i])
			arr[MAX-1] /= arr[i];
	}
}

void cla(char *arg) {
	if (!strcmp(arg, "#")) return ;

	for (int i = start; i < end; i++) {
		if (!arg_type)
			arr[i] = atoi(arg);
		else
			arr[i] = arg[0];
	}
}

void pstart(char *arg) {
	if (isint(arg)) start = atoi(arg);
}

void pend(char *arg) {
	if (isint(arg)) end = atoi(arg);
}

void assig(char *arg) {
	if (!strcmp(arg, ":-")) return ;

	if (isint(arg)) arr[atoi(arg)] = arr[pos];
}

void notassig(char *arg) {
	if (!strcmp(arg, "!-")) return ;

	if (isint(arg)) arr[atoi(arg)] = !arr[pos];
}

void andf(char *arg) {
	for (int i = start; i < end; i++) {
		arr[MAX-1] &= arr[i];
	}
}

void orf(char *arg) {
	for (int i = start; i < end; i++) {
		arr[MAX-1] |= arr[i];
	}
}

void predf(char *arg) {
	pred = arr[MAX-1];
}

void unpred(char *arg) {
	pred = !pred;
}

void iter(char *arg) {
	char *tok = NULL;
	int code = -1, indx = 0;

	if (!strcmp(arg, "|~")) return ;

	for (int i = start; i < end; i++) {
		pos = i;

		indx = 0;
		tok = get_token(arg, &indx);
		while (tok != NULL) {
			if (is_kw(arg) >= 0)
				code = is_kw(arg);
			if (!is_empty(arg))
				exec(code, arg);

			tok = get_token(arg, &indx);
		}
	}
}

void swap(char *arg) {
	int indx = 0;

	if (!strcmp(arg, "<->")) return ;

	if (isint(arg)) {
		indx = atoi(arg);

		arr[pos] ^= arr[indx];
		arr[indx] ^= arr[pos];
		arr[pos] ^= arr[indx];
	}
}

int need_exec(int code) {
	if ((code > 9 && code < 14) || code > 18) return 1;
	else if (pred) return 1;
	else return 0;
}

int is_empty(char *word) {
	int i = 0;
	while (word[i])
		if (!isspace(word[i++])) return 0;
	return 1;	
}

int is_kw(char *word) {
	char *kws[] = {":", "^", "<", ">", "_!", "~", "|", "-!", ";", "@", "+", "\'", "*", "/", "#", "[", "]", ":-", "!-", "&", "\\", "?~", "?!", "|~", "<->"};

	for (int i = 0; i < len; i++) {
		if (!strcmp(kws[i], word)) return i;
	}
	return -1;
}

void exec(int arr_index, char *arg) {
	void (*arr[])(char *) = {ini, addr, shl, shr, show_elm, comment, filler, show_arr, int_mode, char_mode, sum, subt, mult, idiv, cla, pstart, pend, assig, notassig, andf, orf, predf, unpred, iter, swap};

	if (arr_index >= 0 && arr_index < len && need_exec(arr_index)) (*arr[arr_index])(arg);
}
