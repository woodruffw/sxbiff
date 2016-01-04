#include <X11/Xlib.h>

#include "sxbiff.h"
#include "globals.h"

int main(int argc, char **argv)
{
	if (argc >= 2 && (STREQ(argv[1], "-v") || STREQ(argv[1], "--version"))) {
		puts("sxbiff version 1.2 (c) William Woodruff 2016");
		return 1;
	}

	display = XOpenDisplay(NULL);

	if (!display) {
		FATAL_ERROR("Could not connect to the X server.", 1);
	}

	sxbiff();

	/* cleanup */
	XCloseDisplay(display);

	return EXIT_SUCCESS;
}
