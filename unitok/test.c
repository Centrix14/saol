#include <stdio.h>
#include <stdlib.h>
#include "unitok.h"

int main(void) {
	char str[] = ".|(-2) 3 4_!";
	char *tok = get_token(str, 1);

	while (tok != NULL) {
		puts(tok);
		tok = get_token(str, 0);
	}
	return 0;
}
