#ifndef SXBIFF_H
#define SXBIFF_H

#include <stdio.h>

#include "window_utils.h"
#include "flagup.xbm"
#include "flagdown.xbm"

#define SXBIFF_WIDTH 48
#define SXBIFF_HEIGHT 48

#define FATAL_ERROR(str, code) \
	do { \
		fprintf(stderr, "Fatal (%s:%d): %s\n", __FILE__, __LINE__, str); \
		exit(code); \
	} while(0)

void sxbiff(Display *disp);

#endif
