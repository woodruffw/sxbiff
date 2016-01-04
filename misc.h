#ifndef SXBIFF_MISC_H
#define SXBIFF_MISC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FATAL_ERROR(str, code) \
	do { \
		fprintf(stderr, "Fatal (%s:%d): %s\n", __FILE__, __LINE__, str); \
		exit(code); \
	} while(0)

#define STREQ(str1, str2) (!strcmp(str1, str2))

#endif
