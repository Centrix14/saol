#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "arr_lib.h"
#include "../unitok/unitok.h"

int main(int argc, char *argv[]) {
	FILE *src = fopen(argv[1], "r");
	char *tok, line[512];
	int code = 0;

	if (src == NULL) {
		fprintf(stderr, "no such file `%s`\n", argv[1]);
		return 1;
	}

	while (fgets(line, 512, src) != NULL) {
		tok = get_token(line, 1);
		while (tok != NULL) {
			if (is_kw(tok) >= 0)
				code = is_kw(tok);
			if (!is_empty(tok))
				exec(code, tok);

			tok = get_token(line, 0);
		}
	}

	fclose(src);
	return 0;
}
