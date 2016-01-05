#include <X11/Xlib.h>

#include "sxbiff.h"
#include "globals.h"

int main(int argc, char **argv)
{
	bool ontop = false;

	if (argc >= 2) {
		if (STREQ(argv[1], "-v") || STREQ(argv[1], "--version")) {
			puts("sxbiff version 1.3 (c) William Woodruff 2016");
			return 1;
		}
		else if (STREQ(argv[1], "-o") || STREQ(argv[1], "--ontop")) {
			ontop = true;
		}
	}

	display = XOpenDisplay(NULL);

	if (!display) {
		FATAL_ERROR("Could not connect to the X server.", 1);
	}

	sxbiff(ontop);

	/* cleanup */
	XCloseDisplay(display);

	return EXIT_SUCCESS;
}
