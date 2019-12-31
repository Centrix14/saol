/*
 * SAOL interpreter file
 * v1.0
 * 31/12/2019
 * by Centrix
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arr_lib.h"
#include "unitok/unitok.h"

int main(int argc, char *argv[]) {
	FILE *src = fopen(argv[1], "r");
	char *tok, line[512];
	int code = 0, pos = 0;

	if (src == NULL) {
		fprintf(stderr, "no such file `%s`\n", argv[1]);
		return 1;
	}

	while (fgets(line, 512, src) != NULL) {
		pos = 0;
		tok = get_token(line, &pos);
		while (tok != NULL) {
			if (is_kw(tok) >= 0)
				code = is_kw(tok);
			if (!is_empty(tok))
				exec(code, tok);

			tok = get_token(line, &pos);
		}
	}

	fclose(src);
	return 0;
}
