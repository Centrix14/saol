/*
 * Saol interactive interpreter file
 * v1.0
 * 31/12/2019
 * by Centrix
 */

#include <stdio.h>
#include <string.h>
#include "unitok/unitok.h"
#include "arr_lib.h"

int main(void) {
	char line[1024];
	char *tok;
	int code = -1, pos = 0;

	printf("-- Interactive SAOL Interpreter v1.0\n\n");

	while (strcmp(line, "q")) {
		printf("\n> ");
		gets(line);

		tok = get_token(line, &pos);
		while (tok != NULL) {
			if (is_kw(tok) >= 0)
				code = is_kw(tok);
			if (!is_empty(tok))
				exec(code, tok);

			tok = get_token(line, &pos);	
		}
	}
	return 0;
}
