/*
 * utils.c
 *
 *  Created on: 18/06/2016
 *      Author: xavier
 */

#include <string.h>
#include <stdio.h>

#include "utils.h"

int path2args (char *path, char ** argv) {
	int index = 1, argn = 0, length = strlen(path);

	/* Get index */
	do {
		argv[argn] = &(path[index]);

		while (index < length && path[index] != '/')
			index = index + 1;
		path[index] = 0;
		index = index + 1;

		printf("%d. '%s'\r\n", argn, argv[argn]);

		argn = argn + 1;
	} while (index < length);

	return argn;
}

u8 streq (u8 * str1, u8 * str2, size_t n) {
	int i = 0;
	for(i = 0; i < n; i ++) {
		if (str1[i] != str2[i])
			return FALSE;
	}
	return TRUE;
}
