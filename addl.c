/*
 * addl -- adds third-party files
 * v1.0
 * 03.01.2020
 * by Centrix
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char base[] = "out", cmd[256];
	int i = 0, j = 1, ret = 1;

	sprintf(cmd, "./ssp %s %s%d", argv[1], base, i);
	system(cmd);

	while (ret) {
		sprintf(cmd, "./ssp %s%d %s%d", base, i, base, j);
		ret = system(cmd);
		i++; j++;
	}

	sprintf(cmd, "%s%d", base, i);
	puts(cmd);
	return 0;
}
